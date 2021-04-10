/**
 * Copyright (C) 2019 UNISOC Communications Inc.
 */

#include <hwfeature.h>

#ifdef CONFIG_UBOOT_HWFEATURE
static struct hwfeature hwf;
extern int fdt_chosen_bootargs_append(void *fdt, char *append_args, int force);

static void *hwfeature_fix_value(struct hwfeature *phwf, char *value, char *value_fixed)
{
    int auto_map = 0;
    long auto_value = -1;

#define HWFEATURE_FIX_VALUE_MODE(mode) \
    if (phwf->get_##mode && !auto_map) { \
        if (strncmp("auto."#mode",", value, sizeof("auto."#mode",")-1) == 0) { \
            value += sizeof("auto."#mode",")-1; \
            auto_value = phwf->get_##mode(phwf); \
            auto_map = 1; \
        } \
    }

    HWFEATURE_FIX_VALUE_MODE(efuse)
    HWFEATURE_FIX_VALUE_MODE(chipid)
    HWFEATURE_FIX_VALUE_MODE(adc)
    HWFEATURE_FIX_VALUE_MODE(gpio)

    if (auto_map) {
        char *map_str, *map_key, *map_value = NULL;
        long map_key_mode;

        while (value) {
            map_str = strsep(&value, ",");
            map_key = strsep(&map_str, ":");
            map_value = map_str;
            map_key_mode = (long)strtoul(map_key, NULL, 0);
            if (auto_value == map_key_mode)
                break;
        }

        // if the auto_value wouldn't match the corresponding value,The last
        // one in map_table would be matched as defalut
        // strlcpy(value_fixed, map_value, HWFEATURE_VALUE_MAX);
        // return value_fixed;
        value = map_value;
    }

    return value;
}

static int hwfeature_pick_element(struct hwfeature *phwf, const char *token)
{
    /* return 1 stands for unfinished data, return 0 stands for all data finished */
    phwf->param_curr = (char *)strsep(&phwf->param_start, token);
    return phwf->param_curr != NULL;
}

static int hwfeature_process_element(struct hwfeature *phwf)
{
    phwf->trim(phwf, &phwf->param_curr, phwf->param_start);
    if (phwf->param_curr[0] == '\0')
        return 0;

    phwf->count++;
    if (strncmp("androidboot/", phwf->param_curr, 12) == 0) {
        phwf->param_curr += 12;
        phwf->append_to_cmdline = 1;
    } else
        phwf->append_to_cmdline = 0;

    /* Process the phwf->param_curr, ef:key=value or key=auto,e1:m1,e2:m2 */
    phwf->key = strsep(&phwf->param_curr, "=");
    phwf->trim(phwf, &phwf->key, NULL);
    phwf->value = phwf->param_curr;
    if (phwf->value) {
        phwf->trim(phwf, &phwf->value, NULL);
        phwf->value = phwf->fix_value(phwf, phwf->value, phwf->value_fixed);
    }

    // Append to bootargs
    if (phwf->append_to_cmdline) {
        phwf->format(phwf, NULL); /* Init buf cache */
        phwf->format(phwf, "androidboot/%s=", phwf->key);
        phwf->replace(phwf, phwf->format_buf, '/', '.');
        phwf->format(phwf, "%s", phwf->value);
        fdt_chosen_bootargs_append(phwf->fdt, phwf->format_buf, 1);
    }

    // Append to dts file
    if (phwf->fdt_generate(phwf))
        debug("hwfeature: Unable to add node to DT");

    return 1;
}

static int hwfeature_fdt_header(struct hwfeature *phwf)
{
    int root_off, hwf_off;

    root_off = fdt_path_offset(phwf->fdt, "/");
    if (root_off < 0) {
        debug("hwfeature: No / node in DT\n");
        return -1;
    }

    phwf->root_off = root_off;

    hwf_off = fdt_subnode_offset(phwf->fdt, root_off, "hwfeature");
    if (hwf_off < 0)
        hwf_off = fdt_add_subnode(phwf->fdt, root_off, "hwfeature");

    return hwf_off;
}

static int hwfeature_fdt_mknodes(struct hwfeature *phwf, char *path, int *dt_node_off)
{
    int node_off;
    char *node_name;

    while (path) {
        node_name = strsep(&path, "/");
        node_off = fdt_subnode_offset(phwf->fdt, *dt_node_off, node_name);
        if (node_off < 0) {
            node_off = fdt_add_subnode(phwf->fdt, *dt_node_off, node_name);
            if (node_off < 0) {
                debug("hwfeature: Unable to set node to upper: %d\n", node_off);
                return -1;
            }
        }
        *dt_node_off = node_off;
    }

    return 0;
}

static int hwfeature_fdt_mkprop(struct hwfeature *phwf, char *prop, char *value, int dt_node_off)
{
    int ret;

    if (value) {
        char *vop = value;
        /* /idle-states/core_pd/entry-latency-us=1000@u32 */
        strsep(&vop, "@"); /* strsep will replace @ to \0 */
        if (vop) {
            union {
                uint32_t v32;
                uint64_t v64;
            } val;
            if (strcmp("u32", vop) == 0) {
                val.v32 = (uint32_t)simple_strtoul(value, NULL, 0);
                ret = fdt_setprop_u32(phwf->fdt, dt_node_off, prop, val.v32);
            } else if (strcmp("u64", vop) == 0) {
                val.v64 = (uint64_t)simple_strtoull(value, NULL, 0);
                ret = fdt_setprop_u64(phwf->fdt, dt_node_off, prop, val.v64);
            } else
                ret = -1;
        } else
            ret = fdt_setprop_string(phwf->fdt, dt_node_off, prop, value);
    } else
        ret = fdt_setprop_empty(phwf->fdt, dt_node_off, prop);

    return ret;
}

static int hwfeature_fdt_generate(struct hwfeature *phwf)
{
    int next_off;
    char *prop_key_prefix, *prop_key, *prop_value;

    if (phwf->key[0] != '/') {
        next_off = phwf->hwf_off;
    } else {
        next_off = phwf->root_off;
        phwf->key++; /* skip the leading slash /, assume only 1 / */
    }
    prop_key = strrchr(phwf->key, '/');
    if (prop_key) {
        *prop_key++ = '\0';
        prop_key_prefix = phwf->key;
    } else {
        prop_key = phwf->key;
        prop_key_prefix = NULL;
    }
    prop_value = phwf->value;

    if ((phwf->fdt_mknodes(phwf, prop_key_prefix, &next_off) == 0) &&
        (phwf->fdt_mkprop(phwf, prop_key, prop_value, next_off) == 0))
        return 0;

    debug("Unable to set prop node: %s,%s\n", prop_key, prop_value);
    return -1;
}

static int hwfeature_format(struct hwfeature *phwf, const char *fmt, ...)
{
    va_list args;
    int i;

    if (fmt == NULL) {
        phwf->result_last_pos = phwf->format_buf;
        phwf->result_max_pos = phwf->format_buf + sizeof(phwf->format_buf);
        phwf->result_last_pos[0] = '\0';
        return 0;
    }

    va_start(args, fmt);
    i = vsprintf(phwf->result_last_pos, fmt, args);
    phwf->result_last_pos += i;
    va_end(args);

    return i;
}

static void hwfeature_replace(struct hwfeature *phwf, char *value, char from, char to)
{
    char *v;

    for (v = value; *v != '\0'; ++v) {
        if (*v == from)
            *v = to;
    }
}

static void hwfeature_trim(struct hwfeature *phwf, char **start, char *end)
{
    char *lstart = *start;
    char *lend;

    if (end == NULL)
        end = lstart + strlen(lstart);
    lend = end - 1;

    while (*lstart == ' ' || *lstart == '\t' || *lstart == '\r' || *lstart == '\n')
        lstart++;
    *start = lstart;

    while (*lend == ' ' || *lend == '\t' || *lstart == '\r' || *lstart == '\n')
        *lend-- = '\0';
}

static void hwfeature_parse_auto(struct hwfeature *phwf)
{
    char buf[512];
    char *p = buf;

    if (phwf == NULL)
        phwf = &hwf;
    *p = '\0';

#define HWFEATURE_AUTO_MODE(mode) \
    if (phwf->get_##mode) { \
        p += sprintf(p, "auto/"#mode"_raw=%ld", phwf->get_##mode(phwf)); \
    }

    HWFEATURE_AUTO_MODE(efuse)
    HWFEATURE_AUTO_MODE(chipid)
    HWFEATURE_AUTO_MODE(adc)
    HWFEATURE_AUTO_MODE(gpio)

    phwf->param = buf;
    phwf->parse(phwf);
}

static void hwfeature_init(struct hwfeature *phwf, void *fdt)
{
    phwf->fdt = fdt;
    phwf->count = 0;
    phwf->hwf_off = phwf->fdt_header(phwf);
    if (phwf->hwf_off < 0) {
        debug("hwfeature: fdt: Unable to add header to DT: %d\n", phwf->hwf_off);
    }
}

static void hwfeature_parse(struct hwfeature *phwf)
{
    if (phwf == NULL)
        phwf = &hwf;
    phwf->param_start = (char*)phwf->param;

    while (phwf->pick_element(phwf, ";")) {
        phwf->process_element(phwf);
    }
}

static struct hwfeature hwf = {
    .param = CONFIG_UBOOT_HWFEATURE,
    .parse = hwfeature_parse,
    .init = hwfeature_init,
    .parse_auto = hwfeature_parse_auto,
    .pick_element = hwfeature_pick_element,
    .fdt_header = hwfeature_fdt_header,
    .fdt_generate = hwfeature_fdt_generate,
    .fdt_mknodes = hwfeature_fdt_mknodes,
    .fdt_mkprop = hwfeature_fdt_mkprop,
    .process_element = hwfeature_process_element,
    .trim = hwfeature_trim,
    .fix_value = hwfeature_fix_value,
    .replace = hwfeature_replace,
    .format = hwfeature_format,
    .late_initcall = NULL,
#undef HW_GET_MODE
#define HW_GET_MODE(mode) \
    .get_##mode = NULL,
    HW_GET_MODE(efuse)
    HW_GET_MODE(chipid)
    HW_GET_MODE(adc)
    HW_GET_MODE(gpio)
};

void hwfeature_hook_late_initcall(void (*late_initcall)(struct hwfeature *phwf, void *fdt))
{
    hwf.late_initcall = late_initcall;
};

#undef HW_GET_HOOK_MODE
#define HW_GET_HOOK_MODE(mode) \
    void hwfeature_hook_get_##mode(long (*get)(struct hwfeature *phwf)) \
    { \
        hwf.get_##mode = get; \
    }

HW_GET_HOOK_MODE(efuse)
HW_GET_HOOK_MODE(chipid)
HW_GET_HOOK_MODE(adc)
HW_GET_HOOK_MODE(gpio)

int fdt_fixup_hwfeature(void *fdt)
{
    hwf.init(&hwf, fdt);
    hwf.parse(NULL);
    hwf.parse_auto(NULL);
    if (hwf.late_initcall)
        hwf.late_initcall(&hwf, fdt);
    return 0;
}
#else
int fdt_fixup_hwfeature(void *fdt) { return 0; }
void hwfeature_hook_late_initcall(void (*late_initcall)(struct hwfeature *phwf, void *fdt)) { };
#undef HW_GET_HOOK_MODE
#define HW_GET_HOOK_MODE(mode) \
    void hwfeature_hook_get_##mode(long (*get)(struct hwfeature *phwf)) { }
HW_GET_HOOK_MODE(efuse)
HW_GET_HOOK_MODE(chipid)
HW_GET_HOOK_MODE(adc)
HW_GET_HOOK_MODE(gpio)
#endif

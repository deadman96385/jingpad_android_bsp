#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x44894f3e, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xe92851a1, __VMLINUX_SYMBOL_STR(kobject_put) },
	{ 0x2d731fd0, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xd2b09ce5, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x1fdc7df2, __VMLINUX_SYMBOL_STR(_mcount) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0x80d68d3e, __VMLINUX_SYMBOL_STR(fb_register_client) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0x27bbf221, __VMLINUX_SYMBOL_STR(disable_irq_nosync) },
	{ 0x31ae622a, __VMLINUX_SYMBOL_STR(irq_to_desc) },
	{ 0x47229b5c, __VMLINUX_SYMBOL_STR(gpio_request) },
	{ 0x84bc974b, __VMLINUX_SYMBOL_STR(__arch_copy_from_user) },
	{ 0x4881334f, __VMLINUX_SYMBOL_STR(gpio_to_desc) },
	{ 0x88bfa7e, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0xce1a8bac, __VMLINUX_SYMBOL_STR(filp_close) },
	{ 0x9c71c2a8, __VMLINUX_SYMBOL_STR(__spi_register_driver) },
	{ 0xeae3dfd6, __VMLINUX_SYMBOL_STR(__const_udelay) },
	{ 0x4aacd53e, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x35772caa, __VMLINUX_SYMBOL_STR(sysfs_remove_group) },
	{ 0x6ffd0f2e, __VMLINUX_SYMBOL_STR(kobject_create_and_add) },
	{ 0x7695a5ce, __VMLINUX_SYMBOL_STR(proc_remove) },
	{ 0x8173138c, __VMLINUX_SYMBOL_STR(input_set_abs_params) },
	{ 0xce2840e7, __VMLINUX_SYMBOL_STR(irq_set_irq_wake) },
	{ 0x248182a0, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0xf9c0b663, __VMLINUX_SYMBOL_STR(strlcat) },
	{ 0xbc1491c7, __VMLINUX_SYMBOL_STR(vfs_read) },
	{ 0xdcb764ad, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x97fdbab9, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0xe2eb0ddf, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x985558a1, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0xcdac2b7b, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0x449ad0a7, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xb6a48287, __VMLINUX_SYMBOL_STR(of_find_property) },
	{ 0xecf52c49, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0x5a921311, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0x5792f848, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xea4da3ab, __VMLINUX_SYMBOL_STR(input_set_capability) },
	{ 0x5e38de65, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x7d638cc6, __VMLINUX_SYMBOL_STR(gpiod_direction_input) },
	{ 0x3aa6dcad, __VMLINUX_SYMBOL_STR(input_mt_init_slots) },
	{ 0x93653d7a, __VMLINUX_SYMBOL_STR(gpiod_direction_output_raw) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x68f31cbd, __VMLINUX_SYMBOL_STR(__list_add_valid) },
	{ 0xa4a3ed84, __VMLINUX_SYMBOL_STR(spi_sync) },
	{ 0xf7c7c183, __VMLINUX_SYMBOL_STR(sysfs_create_link) },
	{ 0xa63a2f1e, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0xb35dea8f, __VMLINUX_SYMBOL_STR(__arch_copy_to_user) },
	{ 0xf0fdf6cb, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x5c1cad5d, __VMLINUX_SYMBOL_STR(input_register_device) },
	{ 0x349800f, __VMLINUX_SYMBOL_STR(input_free_device) },
	{ 0xe148f626, __VMLINUX_SYMBOL_STR(of_get_named_gpio_flags) },
	{ 0xd7052cfa, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x96220280, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xacbcde49, __VMLINUX_SYMBOL_STR(__module_get) },
	{ 0xfe990052, __VMLINUX_SYMBOL_STR(gpio_free) },
	{ 0xfcec0987, __VMLINUX_SYMBOL_STR(enable_irq) },
	{ 0x2388ae85, __VMLINUX_SYMBOL_STR(kobject_get_path) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xa46f2f1b, __VMLINUX_SYMBOL_STR(kstrtouint) },
	{ 0x4829a47e, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xd6a4ca42, __VMLINUX_SYMBOL_STR(input_unregister_device) },
	{ 0x633bdda3, __VMLINUX_SYMBOL_STR(gpiod_to_irq) },
	{ 0xae8c4d0c, __VMLINUX_SYMBOL_STR(set_bit) },
	{ 0x2f2f5170, __VMLINUX_SYMBOL_STR(input_mt_report_slot_state) },
	{ 0x8127904f, __VMLINUX_SYMBOL_STR(request_firmware) },
	{ 0xb12cbacb, __VMLINUX_SYMBOL_STR(fb_unregister_client) },
	{ 0x8f678b07, __VMLINUX_SYMBOL_STR(__stack_chk_guard) },
	{ 0x2e0d2f7f, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x28318305, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x7d6849af, __VMLINUX_SYMBOL_STR(proc_create) },
	{ 0x2c9e28ce, __VMLINUX_SYMBOL_STR(of_property_read_variable_u32_array) },
	{ 0x24b20821, __VMLINUX_SYMBOL_STR(release_firmware) },
	{ 0x88db9f48, __VMLINUX_SYMBOL_STR(__check_object_size) },
	{ 0xc1514a3b, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0xf1181dd5, __VMLINUX_SYMBOL_STR(filp_open) },
	{ 0xd3a43a06, __VMLINUX_SYMBOL_STR(input_allocate_device) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("of:N*T*Cfocaltech,fts");
MODULE_ALIAS("of:N*T*Cfocaltech,ftsC*");

#include <common.h>
#include <asm/cpu.h>
#include <asm/post.h>

int print_cpuinfo(void)
{
	return default_print_cpuinfo();
}

int arch_cpu_init(void)
{
	post_code(POST_CPU_INIT);
#ifdef CONFIG_SYS_X86_TSC_TIMER
	timer_set_base(rdtsc());
#endif
	return x86_cpu_init_f();
}

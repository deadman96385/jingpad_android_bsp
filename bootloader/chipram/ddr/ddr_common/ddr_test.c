#include <config.h>
#ifdef CONFIG_FDL1
#ifdef FDL1_DDR_SCAN
int ddr_test(int start, int end)
{
	return ddr_scan_fdl1_test(start, end);
}
int ddr_sr_test(unsigned int timeout)
{
	return ddr_selfrefresh_test(timeout);
}
#else
int ddr_test(int start, int end)
{
	return 0;
}
int ddr_sr_test(unsigned int timeout)
{
	return 0;
}
#endif
#endif

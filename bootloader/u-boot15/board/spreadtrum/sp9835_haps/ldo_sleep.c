#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
#include <adi_hal_internal.h>

/***************************************************************************************************************************/
/*     VDD18 VDD28 VDD25 RF0 RF1 RF2 EMMCIO EMMCCORE DCDCARM DCDCWRF DCDCWPA DCDCGEN DCDCOTP AVDD18 SD SIM0 SIM1 SIM2 CAMA */
/* AP    x     x    v     v   v   v     v      v        v       v       v       x       v      v    v    v   v     v    v  */
/* CP0   x     x    v     v   v   x     x      x        x       v       x       x       x      x    x    x   x     x    x  */
/* CP1   x     x    v     x   x   x     x      x        x       x       x       x       x      x    x    x   x     x    x  */
/* CP2   x     x    v     v   x   v     x      x        x       v       x       x       x      x    x    x   x     x    x  */
/* EX0   x     x    x     v   x   x     x      x        x       x       x       x       x      x    x    x   x     x    x  */
/* EX1   x     x    x     x   v   x     x      x        x       x       x       x       x      x    x    x   x     x    x  */
/* EX2   x     x    x     v   x   x     x      x        x       x       x       x       x      x    x    x   x     x    x  */
/***************************************************************************************************************************/

/***************************************************************************************************************************/
/*     CAMD CMAIO CAMMOT USB CLSG LPREF LPRF0 LPRF1 LPRF2 LPEMMCIO LPEMMCCORE LPWPA  LPGEN   LPARM LPMEM LPCORE LPBG  BG   */
/* AP    v     v    v     v   v   v     v      v     v       v       v          x       v      v     v     v     v     v   */
/* CP0   x     x    x     x   x   x     x      x     x       x       x          x       x      x     x     x     x     x   */
/* CP1   x     x    x     x   x   x     x      x     x       x       x          x       x      x     x     x     x     x   */
/* CP2   x     x    x     x   x   x     v      v     x       x       x          x       x      x     x     x     x     x   */
/* EX0   x     x    x     x   x   x     x      x     v       x       x          x       x      x     x     x     x     x   */
/* EX1   x     x    x     x   x   x     x      x     x       x       x          x       x      x     x     x     x     x   */
/* EX2   x     x    x     x   x   x     x      x     x       x       x          x       x      x     x     x     x     x   */
/***************************************************************************************************************************/
void DCDC_ldo_power_on()
{
}

void pmic_lowpower_config(uint32_t gen_para)
{
}

void sprd_pmu_lowpower_init(void)
{
}

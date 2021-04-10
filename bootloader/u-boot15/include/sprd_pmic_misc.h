
#ifndef _SPRD_PMIC_MISC_H_
#define _SPRD_PMIC_MISC_H_

void pmic_misc_init(void);
int is_smpl_bootup(void);
int is_7s_reset_for_systemdump(void);
int is_7s_reset(void);
int regulator_pmic_init(void);
#endif

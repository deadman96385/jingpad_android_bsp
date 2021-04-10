#ifndef _DDRC_R2P0_POWER_CONSUMPTION_H__
#define _DDRC_R2P0_POWER_CONSUMPTION_H__

#define USER_DATA_1 0x0
#define USER_DATA_2 0xffffffff
#define USER_DATA_3 0x0f0f0f0f
#define USER_DATA_4 0xff00ff00

#define RF_PHY_IO_AC_ADDR_DRV_OFFSET 0x4 /*CA DRV*/
#define RF_PHY_IO_DQ_ADDR_DRV_OFFSET 0xf4 /*DQ DRV*/

#define PWR_CONS_MEAS_LOG_EN
#define PWR_CONS_MEAS_UART_EN

#define	BIST_PORT0_CPU_EN					0    //CHN0, Priority high
#define	BIST_PORT1_GPU_EN					1    //CHN0, Priority low
#define	BIST_PORT2_DPU_DCAM_EN					1	//CHN1, Priority high
#define	BIST_PORT3_ISP_EN					1	//CHN2, Priority high
#define	BIST_PORT4_AP_VSP_AON_EN				0	//CHN1, Priority low
#define	BIST_PORT5_WTLCP_EN					0	//CHN2, Priority middle
#define	BIST_PORT6_PUBCP_AUDCP_EN				0	//CHN2, Priority low


typedef struct
{
	u32 bist_chn_num;/*current channel*/
	u32 bist_mode; /*read 、write、R&W*/
	u32 data_pattern_mode;/*SIPI\LFSR\USER DATA*/
	u32 bist_size;/*bist size */
	u32 *bist_src;/*bist address */
	u32 bist_bw_test_mode;/*0:ONE Triger once bist 1:LOOP triger bist*/
	u32 user_pattern_data;/*user data_pattern_mode choose*/
	u32 bist_data_mode_size;/*FOUR_WORDS,TWO_WORDS,TWO_WORDS*/
}BIST_PARA;


static u32 user_mode_pattern_test [4][1];


static u32 sipi_mode_pattern[]=
{
	BIST_SIPI_DATA_00,
	BIST_SIPI_DATA_01,
	BIST_SIPI_DATA_02,
	BIST_SIPI_DATA_03,
	BIST_SIPI_DATA_04,
	BIST_SIPI_DATA_05,
	BIST_SIPI_BIT_PATTERN_0,
	BIST_SIPI_BIT_PATTERN_1
};

static u32 lfsr_mode_pattern[] =
{
	BIST_DATA_LFSR_SEED_L0,
	BIST_DATA_LFSR_SEED_L1,
	BIST_DATA_LFSR_SEED_H0,
	BIST_DATA_LFSR_SEED_H1
};
#endif

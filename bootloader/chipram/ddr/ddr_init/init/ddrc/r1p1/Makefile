obj-y += ddrc_r1p1.o  ddrc_r1p1_common.o ddrc_r1p1_ctrl_init.o ddrc_r1p1_lpddrx.o ddrc_r1p1_phy_cfg.o ddrc_r1p1_phy_init.o bist.o ddrc_r1p1_auto_detect.o \
    serial.o \
    ddr_test.o \
    roc1_dfs.o   \
    ddrc_r1p1_br_debug.o

# CONFIG_SPRD_DDR__POWER_TEST = y
ifneq ($(CONFIG_SPRD_DDR__POWER_TEST), )
ifeq ($(CONFIG_DDR_SCAN_BUILD), )
CFLAGS += -DPOWER_TEST
obj-y +=  roc1_ddr_reinit.o roc1_common.o ddrc_r1p1_power_consumption.o
endif
endif

obj-$(CONFIG_DDR_SCAN_BUILD) += ddr_scan_offline.o

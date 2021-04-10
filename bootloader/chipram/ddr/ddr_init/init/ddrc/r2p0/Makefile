obj-y += ddrc_init.o ddrc_common.o ddrc_feature_init.o ddrc_init_train.o ddrc_tmg_cfg.o dram_support.o dram_test.o

# obj-$(CONFIG_DDR_SCAN_BUILD) += ddrc_r2p0_scan_offline.o
obj-$(CONFIG_DDR_SCAN_BUILD) += ddrc_r2p0_scan_offline_eye.o

ifdef CONFIG_SPRD_DDR__POWER_TEST
ifndef CONFIG_DDR_SCAN_BUILD
obj-y += ddrc_r2p0_power_consumption.o
obj-y += serial.o
obj-y += ddrc_r2p0_power_deepsleep.o
CFLAGS += -DDDR_POWER_TEST
endif
endif

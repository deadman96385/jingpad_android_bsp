
obj-y = ddr_common/

ifneq ($(CONFIG_SOC_IWHALE2)$(CONFIG_SOC_ISHARKL2)$(CONFIG_WHALE2)$(CONFIG_SPRD_DDRC_R1P0)$(CONFIG_SPRD_DDRC_R1P1)$(CONFIG_SPRD_DDRC_R1P1_ORCA)$(CONFIG_SPRD_DDRC_R2P0)$(CONFIG_SPRD_DDRC_R2P2),)

obj-$(CONFIG_WHALE) += ddr_init/init/v0_0/
obj-$(CONFIG_WHALE) += ddr_init/qos/v0_0/
obj-$(CONFIG_WHALE) += ddr_init/timing/v0_0/

obj-$(CONFIG_WHALE2) += ddr_init/init/v0_1/
obj-$(CONFIG_WHALE2) += ddr_init/qos/v0_1/
obj-$(CONFIG_WHALE2) += ddr_init/timing/v0_1/

obj-$(CONFIG_SOC_IWHALE2) += ddr_init/init/v0_2/
obj-$(CONFIG_SOC_IWHALE2) += ddr_init/qos/v0_2/
obj-$(CONFIG_SOC_IWHALE2) += ddr_init/timing/v0_2/

obj-$(CONFIG_SOC_ISHARKL2) += ddr_init/init/v0_3/
obj-$(CONFIG_SPRD_DDRC_R1P0) += ddr_init/init/ddrc/r1p0/
obj-$(CONFIG_SPRD_DDRC_R1P1) += ddr_init/init/ddrc/r1p1/
obj-$(CONFIG_SPRD_DDRC_R1P1_ORCA) += ddr_init/init/ddrc/r1p1_orca/
obj-$(CONFIG_SPRD_DDRC_R2P0) += ddr_init/init/ddrc/r2p0/
obj-$(CONFIG_SPRD_DDRC_R2P2) += ddr_init/init/ddrc/r2p2/
obj-$(CONFIG_DDR_IP_CONFIG_FILE) += ddr_init/ip_cfg/v0_2/

endif


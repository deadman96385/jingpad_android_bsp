ifdef CONFIG_LOAD_TOS_ALONE
ifdef CONFIG_ARCH_SCX35L2
obj-y	+= tentry.o tos_entry.o
endif
endif

obj-y += firewall.o
obj-$(CONFIG_ARCH_SCX35L2) += firewall_sharkl2.o
obj-$(CONFIG_SOC_IWHALE2) += firewall_iwhale2.o
obj-$(CONFIG_SOC_ISHARKL2) += firewall_isharkl2.o
obj-$(CONFIG_SOC_SHARKLJ1) += firewall_sharklj1.o
obj-$(CONFIG_SOC_SHARKLE) += firewall_sharkle.o
obj-$(CONFIG_SOC_PIKE2) += firewall_pike2.o
obj-$(CONFIG_SOC_SHARKL3) += firewall_sharkl3.o
obj-$(CONFIG_SOC_SHARKL5) += firewall_sharkl5.o
obj-$(CONFIG_SOC_SHARKL5PRO) += firewall_sharkl5pro.o
obj-$(CONFIG_SOC_ROC1) += firewall_roc1.o

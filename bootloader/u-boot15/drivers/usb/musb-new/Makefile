#
# for USB OTG silicon based on Mentor Graphics INVENTRA designs
#

obj-$(CONFIG_MUSB_GADGET) += musb_gadget.o musb_gadget_ep0.o musb_core.o
obj-$(CONFIG_MUSB_GADGET) += musb_uboot.o sprd_musb2_driver.o
obj-$(CONFIG_MUSB_HOST) += musb_host.o musb_core.o musb_uboot.o
obj-$(CONFIG_USB_MUSB_DSPS) += musb_dsps.o
obj-$(CONFIG_USB_MUSB_AM35X) += am35x.o
obj-$(CONFIG_USB_MUSB_OMAP2PLUS) += omap2430.o
obj-$(CONFIG_USB_MUSB_SUNXI) += sunxi.o
obj-$(CONFIG_USB_SPRD_DMA) += sprd_musbhsdma.o
obj-$(CONFIG_USB_PHY_SPRD) += sprd_usb_phy.o
obj-$(CONFIG_USB_PHY_SNPS) += snps_usb_phy.o
obj-$(CONFIG_USB_PHY_SHARKLE) += sharkle_usb_phy.o
obj-$(CONFIG_USB_PHY_SHARKLER) += sharkler_usb_phy.o
obj-$(CONFIG_USB_PHY_SHARKL3) += sharkl3_usb_phy.o
obj-$(CONFIG_USB_PHY_ROC1) += roc1_usb_phy.o
obj-$(CONFIG_USB_PHY_SHARKL5) += sharkl5_usb_phy.o
obj-$(CONFIG_USB_PHY_ORCA) += orca_usb_phy.o
obj-$(CONFIG_USB_PHY_SHARKL5PRO) += sharkl5pro_usb_phy.o
obj-$(CONFIG_USB_PHY_QOGIRN6PRO) += qogirn6pro_usb_phy.o

ccflags-y := $(call cc-option,-Wno-unused-variable) \
		$(call cc-option,-Wno-unused-but-set-variable) \
		$(call cc-option,-Wno-unused-label)

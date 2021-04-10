#ifdef CONFIG_USB_DWC3
obj-y					:= core.o
obj-y					+= gadget.o ep0.o
obj-y					+= dwc3_uboot.o
obj-y					+= sprd_usb3_driver.o
#endif
obj-$(CONFIG_USB_DWC3_SPRD_INTEL)	+= sprd_intel_usb3_hw.o
obj-$(CONFIG_USB_DWC3_PHY_ROC1)		+= sprd_usb3_roc1_phy.o
obj-$(CONFIG_USB_DWC3_PHY_ORCA)		+= sprd_usb3_orca_phy.o

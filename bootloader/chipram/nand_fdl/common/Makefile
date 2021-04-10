obj-y += dl_engine.o fdl_crc.o packet.o fdl_channel.o fdl_stdio.o sprd_usb_dloader.o serial_sc8800x.o

ifdef CONFIG_USB_DWC3
obj-y += sprd_usb3_driver.o
else
ifdef CONFIG_MENTOR_USB
obj-y += sprd_musb2_driver.o
else
obj-y += sprd_usb2_driver.o
endif
endif

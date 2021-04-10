ifeq ($(TARGET_ARCH), x86_64)
	LOCAL_TOOLCHAIN := $(shell pwd)/prebuilts/gcc/linux-x86/x86/x86_64-linux-android-4.9/bin/x86_64-linux-android-
else
ifeq ($(TOOLCHAIN_64),true)
ifeq ($(UBOOT_USE_ANDROID_TOOLCHAIN),true)
     LOCAL_TOOLCHAIN := $(shell pwd)/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-
else
     LOCAL_TOOLCHAIN := $(shell pwd)/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-
endif
else
LOCAL_TOOLCHAIN := $(shell pwd)/prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin/arm-eabi-
endif
endif

CHIPRAM_OUT := $(TARGET_OUT_INTERMEDIATES)/chipram

BUILT_SPL := $(CHIPRAM_OUT)/nand_spl/u-boot-spl-16k.bin
BUILT_FDL1 := $(CHIPRAM_OUT)/nand_fdl/fdl1.bin
BUILT_DDR_SCAN := $(CHIPRAM_OUT)/ddr_scan/ddr_scan.bin

ifeq ($(BUILD_FPGA),true)
BUILT_DDR_SCAN := $(CHIPRAM_OUT)/ddr_scan/ddr_scan.bin
endif

CHIPRAM_CONFIG := $(CHIPRAM_OUT)/include/config.h

.PHONY: $(CHIPRAM_OUT)
$(CHIPRAM_OUT):
	@echo "Start chipram build"

$(CHIPRAM_CONFIG):  $(CHIPRAM_OUT)
	@mkdir -p $(CHIPRAM_OUT)
	$(MAKE) -C chipram CROSS_COMPILE=$(LOCAL_TOOLCHAIN) O=../$(CHIPRAM_OUT) distclean
ifeq ($(strip $(CHIPRAM_DEFCONFIG)),)
	$(MAKE) -C chipram CROSS_COMPILE=$(LOCAL_TOOLCHAIN) O=../$(CHIPRAM_OUT) $(UBOOT_DEFCONFIG)_config
else
	$(MAKE) -C chipram CROSS_COMPILE=$(LOCAL_TOOLCHAIN) O=../$(CHIPRAM_OUT) $(CHIPRAM_DEFCONFIG)_config
endif
ifeq ($(strip $(BOARD_KERNEL_SEPARATED_DT)),true)
	@echo "#define CONFIG_OF_LIBFDT" >> $(CHIPRAM_CONFIG)
endif

ifeq ($(strip $(TARGET_BUILD_VARIANT)),userdebug)
	@echo "#define CONFIG_DEBUG" >> $(CHIPRAM_CONFIG)
endif

ifeq ($(strip $(PRODUCT_SECURE_BOOT)),SPRD)
	@echo "#define CONFIG_SPRD_SECBOOT" >> $(CHIPRAM_CONFIG)
	@echo "#define CONFIG_SECBOOT" >> $(CHIPRAM_CONFIG)
	@echo "CONFIG_SPRD_SECBOOT = y" >> $(CHIPRAM_OUT)/include/config.mk
endif

ifeq ($(strip $(PKCS1_PSS_FLAG)),true)
	@echo "#define PKCS1_PSS_FLAG" >> $(CHIPRAM_CONFIG)
	@echo "PKCS1_PSS_FLAG = y" >> $(CHIPRAM_OUT)/include/config.mk
endif

ifeq ($(strip $(BOARD_KBC_BYPASS_SECURE_BOOT)),true)
	@echo "#define CONFIG_KBC_BYPASS_SECURE_BOOT" >> $(CHIPRAM_CONFIG)
endif

ifeq ($(strip $(CONFIG_SANSA_SECBOOT)),true)
	@echo "#define CONFIG_SANSA_SECBOOT" >> $(CHIPRAM_CONFIG)
	@echo "#define CONFIG_SECBOOT" >> $(CHIPRAM_CONFIG)
	@echo "CONFIG_SANSA_SECBOOT = y" >> $(CHIPRAM_OUT)/include/config.mk
endif

ifeq ($(strip $(BOARD_TEE_CONFIG)),trusty)
	@echo "#define CONFIG_LOAD_TOS_ALONE 1" >> $(CHIPRAM_CONFIG)
	@echo "CONFIG_LOAD_TOS_ALONE = y" >> $(CHIPRAM_OUT)/include/config.mk
endif

ifeq ($(strip $(BOARD_TEECFG_CUSTOM)),true)
	@echo "#define CONFIG_TEECFG_CUSTOM 1" >> $(CHIPRAM_CONFIG)
	@echo "CONFIG_TEECFG_CUSTOM = y" >> $(CHIPRAM_OUT)/include/config.mk
ifneq ($(strip $(BOARD_TEECFG_MEM_ADDR)),)
	@echo "#define CONFIG_TEECFG_LDADDR_START $(BOARD_TEECFG_MEM_ADDR)" >> $(CHIPRAM_CONFIG)
endif
endif

ifeq ($(strip $(BOARD_ATF_CONFIG)),true)
	@echo "#define CONFIG_LOAD_ATF 1" >> $(CHIPRAM_CONFIG)
	@echo "CONFIG_LOAD_ATF = y" >> $(CHIPRAM_OUT)/include/config.mk

ifeq ($(strip $(BOARD_ATF_BOOT_TOS_CONFIG)),true)
	@echo "#define CONFIG_ATF_BOOT_TOS 1" >> $(CHIPRAM_CONFIG)
	@echo "CONFIG_ATF_BOOT_TOS = y" >> $(CHIPRAM_OUT)/include/config.mk
endif
endif

ifneq ($(strip $(BOARD_SML_MEM_ADDR)),)
	@echo "#define CONFIG_SML_LDADDR_START $(BOARD_SML_MEM_ADDR)" >> $(CHIPRAM_CONFIG)
endif

ifneq ($(strip $(BOARD_TOS_MEM_ADDR)),)
	@echo "#define CONFIG_TOS_LDADDR_START $(BOARD_TOS_MEM_ADDR)" >> $(CHIPRAM_CONFIG)
endif

ifneq ($(strip $(BOARD_SEC_MEM_SIZE)),)
	@echo "#define CONFIG_SML_TOS_RUNNING_SIZE $(BOARD_SEC_MEM_SIZE)" >>$(CHIPRAM_CONFIG)
	@echo "#define CONFIG_SEC_MEM_SIZE $(BOARD_SEC_MEM_SIZE)" >>$(CHIPRAM_CONFIG)
endif

ifeq ($(strip $(CHIPRAM_DDR_512M_LIMITED)),true)
	@echo "#define CONFIG_CHIPRAM_DDR_512M " >> $(CHIPRAM_CONFIG)
endif

ifeq ($(strip $(CHIPRAM_DDR_1G_LIMITED)),true)
	@echo "#define CONFIG_CHIPRAM_DDR_1G " >> $(CHIPRAM_CONFIG)
endif

ifeq ($(strip $(CHIPRAM_DDR_CUSTOMIZE_LIMITED)),true)
	@echo "#define CONFIG_CHIPRAM_DDR_CUSTOMIZE $(CHIPRAM_DDR_CUSTOMIZE_SIZE) " >> $(CHIPRAM_CONFIG)
endif
$(INSTALLED_CHIPRAM_TARGET) : $(CHIPRAM_CONFIG)
	$(MAKE) -C chipram CROSS_COMPILE=$(LOCAL_TOOLCHAIN) AP_VERSION="$(ANDROID_BUILD_DESC)" O=../$(CHIPRAM_OUT)
	@cp $(BUILT_SPL) $(PRODUCT_OUT)
	@cp $(BUILT_DDR_SCAN) $(PRODUCT_OUT)
	@cp $(BUILT_FDL1) $(PRODUCT_OUT)
	@echo "Install chipram target done"

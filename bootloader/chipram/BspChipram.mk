BSP_OBJ :=`cat /proc/cpuinfo | grep processor | wc -l`

ifneq ($(strip $(BSP_CHIPRAM_TOOLCHAIN)),)
LOCAL_TOOLCHAIN := $(BSP_CHIPRAM_TOOLCHAIN)
else
#use default
ifeq ($(BSP_BOARD_ARCH) , arm64)
LOCAL_TOOLCHAIN := $(shell pwd)/../prebuilts/gcc/linaro-x86/aarch64/gcc-linaro-4.8/gcc-linaro-4.8-2015.06-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
else ifeq ($(BSP_BOARD_ARCH), arm)
LOCAL_TOOLCHAIN := $(shell pwd)/../prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin/arm-eabi-
else ifeq ($(BSP_BOARD_ARCH), x86)
LOCAL_TOOLCHAIN := $(shell pwd)/../prebuilts/gcc/linux-x86/x86/x86_64-linux-android-4.9/bin/x86_64-linux-android-
endif
endif

BSP_BUILT_SPL := $(BSP_CHIPRAM_OUT)/nand_spl/u-boot-spl-16k.bin
BSP_BUILT_FDL1 := $(BSP_CHIPRAM_OUT)/nand_fdl/fdl1.bin
BSP_BUILT_DDR_SCAN := $(BSP_CHIPRAM_OUT)/ddr_scan/ddr_scan.bin

ifeq ($(BUILD_FPGA),true)
BSP_BUILT_DDR_SCAN := $(BSP_CHIPRAM_OUT)/ddr_scan/ddr_scan.bin
endif

BSP_CHIPRAM_CONFIG := $(BSP_CHIPRAM_OUT)/include/config.h

all: $(BSP_CHIPRAM_CONFIG)
	$(MAKE) CROSS_COMPILE=$(LOCAL_TOOLCHAIN) AP_VERSION="$(ANDROID_BUILD_DESC)" O=$(BSP_CHIPRAM_OUT) -j$(BSP_OBJ)
	@mkdir -p $(BSP_CHIPRAM_DIST)
#	@cp $(BSP_BUILT_SPL) $(BSP_CHIPRAM_DIST)
#	@cp $(BSP_BUILT_DDR_SCAN) $(BSP_CHIPRAM_DIST)
#	@cp $(BSP_BUILT_FDL1) $(BSP_CHIPRAM_DIST)
	@echo "Install chipram target done"

.PHONY: $(BSP_CHIPRAM_OUT)
$(BSP_CHIPRAM_OUT):
	@echo "Start chipram build"

$(BSP_CHIPRAM_CONFIG):  $(BSP_CHIPRAM_OUT)
	@mkdir -p $(BSP_CHIPRAM_OUT)
	$(MAKE) CROSS_COMPILE=$(LOCAL_TOOLCHAIN) O=$(BSP_CHIPRAM_OUT) distclean
ifeq ($(strip $(BSP_CHIPRAM_DEFCONFIG)),)
	$(MAKE) CROSS_COMPILE=$(LOCAL_TOOLCHAIN) O=$(BSP_CHIPRAM_OUT) $(BSP_UBOOT_DEFCONFIG)_config
else
	$(MAKE) CROSS_COMPILE=$(LOCAL_TOOLCHAIN) O=$(BSP_CHIPRAM_OUT) $(BSP_CHIPRAM_DEFCONFIG)_config
endif
ifeq ($(strip $(BOARD_KERNEL_SEPARATED_DT)),true)
	@echo "#define CONFIG_OF_LIBFDT" >> $(BSP_CHIPRAM_CONFIG)
endif

ifeq ($(strip $(BSP_PRODUCT_SECURE_BOOT)),SPRD)
	@echo "#define CONFIG_SPRD_SECBOOT" >> $(BSP_CHIPRAM_CONFIG)
	@echo "#define CONFIG_SECBOOT" >> $(BSP_CHIPRAM_CONFIG)
	@echo "CONFIG_SPRD_SECBOOT = y" >> $(BSP_CHIPRAM_OUT)/include/config.mk
endif

ifeq ($(strip $(BSP_PKCS1_PSS_FLAG)),true)
	@echo "#define PKCS1_PSS_FLAG" >> $(BSP_CHIPRAM_CONFIG)
	@echo "PKCS1_PSS_FLAG = y" >> $(BSP_CHIPRAM_OUT)/include/config.mk
endif

ifeq ($(strip $(BOARD_KBC_BYPASS_SECURE_BOOT)),true)
	@echo "#define CONFIG_KBC_BYPASS_SECURE_BOOT" >> $(BSP_CHIPRAM_CONFIG)
endif

ifeq ($(strip $(CONFIG_SANSA_SECBOOT)),true)
	@echo "#define CONFIG_SANSA_SECBOOT" >> $(BSP_CHIPRAM_CONFIG)
	@echo "#define CONFIG_SECBOOT" >> $(BSP_CHIPRAM_CONFIG)
	@echo "CONFIG_SANSA_SECBOOT = y" >> $(BSP_CHIPRAM_OUT)/include/config.mk
endif

ifeq ($(strip $(BSP_BOARD_TEE_CONFIG)),trusty)
	@echo "#define CONFIG_LOAD_TOS_ALONE 1" >> $(BSP_CHIPRAM_CONFIG)
	@echo "CONFIG_LOAD_TOS_ALONE = y" >> $(BSP_CHIPRAM_OUT)/include/config.mk
endif

ifeq ($(strip $(BSP_BOARD_TEECFG_CUSTOM)),true)
	@echo "#define CONFIG_TEECFG_CUSTOM 1" >> $(BSP_CHIPRAM_CONFIG)
	@echo "CONFIG_TEECFG_CUSTOM = y" >> $(BSP_CHIPRAM_OUT)/include/config.mk
ifneq ($(strip $(BSP_BOARD_TEECFG_MEM_ADDR)),)
	@echo "#define CONFIG_TEECFG_LDADDR_START $(BSP_BOARD_TEECFG_MEM_ADDR)" >> $(BSP_CHIPRAM_CONFIG)
endif
endif

ifeq ($(strip $(BSP_BOARD_ATF_CONFIG)),true)
	@echo "#define CONFIG_LOAD_ATF 1" >> $(BSP_CHIPRAM_CONFIG)
	@echo "CONFIG_LOAD_ATF = y" >> $(BSP_CHIPRAM_OUT)/include/config.mk

ifeq ($(strip $(BSP_BOARD_ATF_BOOT_TOS_CONFIG)),true)
	@echo "#define CONFIG_ATF_BOOT_TOS 1" >> $(BSP_CHIPRAM_CONFIG)
	@echo "CONFIG_ATF_BOOT_TOS = y" >> $(BSP_CHIPRAM_OUT)/include/config.mk
endif
endif

ifneq ($(strip $(BSP_BOARD_SML_MEM_ADDR)),)
	@echo "#define CONFIG_SML_LDADDR_START $(BSP_BOARD_SML_MEM_ADDR)" >> $(BSP_CHIPRAM_CONFIG)
endif

ifneq ($(strip $(BSP_BOARD_TOS_MEM_ADDR)),)
	@echo "#define CONFIG_TOS_LDADDR_START $(BSP_BOARD_TOS_MEM_ADDR)" >> $(BSP_CHIPRAM_CONFIG)
endif

ifneq ($(strip $(BSP_BOARD_SEC_MEM_SIZE)),)
	@echo "#define CONFIG_SML_TOS_RUNNING_SIZE $(BSP_BOARD_SEC_MEM_SIZE)" >>$(BSP_CHIPRAM_CONFIG)
	@echo "#define CONFIG_SEC_MEM_SIZE $(BSP_BOARD_SEC_MEM_SIZE)" >>$(BSP_CHIPRAM_CONFIG)
endif

ifeq ($(strip $(BSP_DDR_512M_LIMITED)),true)
	@echo "#define CONFIG_CHIPRAM_DDR_512M " >> $(BSP_CHIPRAM_CONFIG)
endif

ifeq ($(strip $(BSP_DDR_1G_LIMITED)),true)
	@echo "#define CONFIG_CHIPRAM_DDR_1G " >> $(BSP_CHIPRAM_CONFIG)
endif

ifeq ($(strip $(BSP_DDR_CUSTOMIZE_LIMITED)),true)
	@echo "#define CONFIG_CHIPRAM_DDR_CUSTOMIZE $(BSP_DDR_CUSTOMIZE_SIZE) " >> $(BSP_CHIPRAM_CONFIG)
endif

ifeq ($(strip $(BSP_HWFEATURE_DDR)),true)
	@echo "#define CONFIG_CHIPRAM_DDR_MAX_FREQ 1536" >> $(BSP_CHIPRAM_CONFIG)
endif

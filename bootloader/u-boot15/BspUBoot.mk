BSP_OBJ :=`cat /proc/cpuinfo | grep processor | wc -l`

ifneq ($(strip $(BSP_UBOOT_TOOLCHAIN)),)
UBOOT_TOOLCHAIN := $(BSP_UBOOT_TOOLCHAIN)
else
#use default
ifeq ($(BSP_BOARD_ARCH) , arm64)
UBOOT_TOOLCHAIN := $(shell pwd)/../prebuilts/gcc/linaro-x86/aarch64/gcc-linaro-4.8/gcc-linaro-4.8-2015.06-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
else ifeq ($(BSP_BOARD_ARCH), arm)
UBOOT_TOOLCHAIN := $(shell pwd)/../prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin/arm-eabi-
else ifeq ($(BSP_BOARD_ARCH), x86)
UBOOT_TOOLCHAIN := $(shell pwd)/../prebuilts/gcc/linux-x86/x86/x86_64-linux-android-4.9/bin/x86_64-linux-android-
endif
endif

ifeq ($(BSP_BOARD_ARCH) , arm64)
SRCARCH := arm
else ifeq ($(BSP_BOARD_ARCH), arm)
SRCARCH := arm
else ifeq ($(BSP_BOARD_ARCH), x86)
SRCARCH := x86
endif

BSP_UBOOT_CONFIG := $(BSP_UBOOT_OUT)/include/config.h
BSP_UBOOT_DTB_BUILT_BIN := $(BSP_UBOOT_OUT)/u-boot-dtb.bin
BSP_UBOOT_BUILT_BIN := $(BSP_UBOOT_OUT)/u-boot.bin
BSP_FDL2_BUILT_BIN := $(BSP_UBOOT_OUT)/fdl2.bin
BSP_UBOOT_DTB_BUILT := $(BSP_UBOOT_OUT)/u-boot
BSP_UBOOT_DTB_SYSTEM_MAP := $(BSP_UBOOT_OUT)/System.map
BSP_UBOOT_DTB_CFG := $(BSP_UBOOT_OUT)/u-boot.cfg

ifeq ($(TARGET_BUILD_VARIANT),userdebug)
UBOOT_DEBUG_FLAG := -DDEBUG
endif

export UBOOT_CONFIG_PRODUCT UBOOT_DEBUG_FLAG

ifeq ($(strip $(BSP_PRODUCT_SECURE_BOOT)),SPRD)
UBOOT_SECURE_BOOT_FLAG := -DCONFIG_SECBOOT
UBOOT_SECURE_BOOT_FLAG += -DCONFIG_SPRD_SECBOOT
ifeq ($(strip $(BSP_PRODUCT_USE_DYNAMIC_PARTITIONS)),true)
UBOOT_SECURE_BOOT_FLAG += -DPRODUCT_USE_DYNAMIC_PARTITIONS
endif

ifeq ($(strip $(BSP_PKCS1_PSS_FLAG)),true)
UBOOT_SECURE_BOOT_FLAG += -DPKCS1_PSS_FLAG
endif

ifeq ($(strip $(BSP_NOT_VERIFY_MODEM_FLAG)),true)
UBOOT_SECURE_BOOT_FLAG += -DNOT_VERIFY_MODEM
endif

ifeq ($(strip $(BSP_SHARKL5_CDSP_FLAG)),true)
UBOOT_SECURE_BOOT_FLAG += -DSHARKL5_CDSP
endif

ifeq ($(strip $(BSP_PROJECT_SEC_CM4_FLAG)),true)
UBOOT_SECURE_BOOT_FLAG += -DPROJECT_SEC_CM4
endif

ifeq ($(strip $(BSP_PRODUCT_VBOOT)),V2)
UBOOT_SECURE_BOOT_FLAG += -DCONFIG_VBOOT_V2
ifeq (9,$(filter 9,$(PLATFORM_VERSION)))
UBOOT_SECURE_BOOT_FLAG += -DCONFIG_VBOOT_SYSTEMASROOT
endif
endif

ifneq ($(strip $(BOARD_PRODUCTIMAGE_PARTITION_SIZE)),)
UBOOT_SECURE_BOOT_FLAG += -DBOARD_PRODUCTIMAGE_PARTITION_SIZE
endif
endif #BSP_PRODUCT_SECURE_BOOT

ifneq ($(strip $(BSP_HWFEATURE)),)
UBOOT_HWFEATURE_FLAG += -DCONFIG_UBOOT_HWFEATURE='"$(strip $(BSP_HWFEATURE))"'
export UBOOT_HWFEATURE_FLAG
endif

ifeq ($(strip $(PRODUCT_DMVERITY_DISABLE)),true)
UBOOT_SECURE_BOOT_FLAG += -DCONFIG_DMVERITY_DISABLE
endif

export UBOOT_SECURE_BOOT_FLAG

ifeq ($(strip $(ROC1_CACHE_WORKAROUND)), true)
UBOOT_ROC1_CACHE_WA_FLAG := -DROC1_CACHE_MODIFICATION
endif

export UBOOT_ROC1_CACHE_WA_FLAG

ifeq ($(strip $(BSP_BOARD_TEE_CONFIG)),trusty)
UBOOT_TOS_TRUSTY_FLAG := -DTOS_TRUSTY
endif

export UBOOT_TOS_TRUSTY_FLAG

ifeq ($(strip $(BSP_BOARD_TEECFG_CUSTOM)),true)
UBOOT_TEECFG_CUSTOM_FLAG := -DCONFIG_TEECFG_CUSTOM
endif

export UBOOT_TEECFG_CUSTOM_FLAG

ifeq ($(strip $(CONFIG_CHIP_UID)),true)
UBOOT_CHIP_UID_FLAG += -DCONFIG_CHIP_UID
endif

export UBOOT_CHIP_UID_FLAG

ifeq ($(strip $(BSP_CONFIG_TEE_FIREWALL)),true)
UBOOT_FIREWALL_FLAG := -DCONFIG_TEE_FIREWALL
endif

export UBOOT_FIREWALL_FLAG

ifeq ($(BSP_BOARD_ARCH), arm)
ifeq ($(strip $(BSP_BOARD_ATF_CONFIG)),true)
UBOOT_ARMV7_LPAE_FLAG := -DCONFIG_ARMV7_LPAE
endif
endif
export UBOOT_ARMV7_LPAE_FLAG

ifeq ($(strip $(CONFIG_BOARD_KERNEL_CMDLINE)),true)
UBOOT_KERNEL_CMDLINE_FLAG := -DCONFIG_BOARD_KERNEL_CMDLINE
endif
export UBOOT_KERNEL_CMDLINE_FLAG

ifeq ($(strip $(CONFIG_PCTOOL_CHECK_MULTI_FIXNV)),true)
UBOOT_PCTOOL_CHECK_MULTI_FIXNV_FLAG := -DCONFIG_PCTOOL_CHECK_MULTI_FIXNV
endif
export UBOOT_PCTOOL_CHECK_MULTI_FIXNV_FLAG

ifeq ($(strip $(CONFIG_PCTOOL_CHECK_WRITE_PROTECT)),true)
UBOOT_PCTOOL_CHECK_WRITE_PROTECT_FLAG := -DCONFIG_PCTOOL_CHECK_WRITE_PROTECT
endif
export UBOOT_PCTOOL_CHECK_WRITE_PROTECT_FLAG

ifeq ($(strip $(BSP_CALIMODE_USE_BOOTIMG)),true)
UBOOT_CALIMODE_USE_BOOTIMG_FLAG := -DCONFIG_CALIMODE_USE_BOOTIMG
endif
export UBOOT_CALIMODE_USE_BOOTIMG_FLAG

all: $(BSP_UBOOT_CONFIG)
	@mkdir -p $(BSP_UBOOT_DIST)
	$(MAKE) ARCH=$(SRCARCH) DEVICE_TREE=$(BSP_UBOOT_TARGET_DTB) CROSS_COMPILE=$(UBOOT_TOOLCHAIN) AUTOBOOT_FLAG=true O=$(BSP_UBOOT_OUT) -j$(BSP_OBJ)
	-cp $(BSP_UBOOT_DTB_BUILT_BIN) $(BSP_UBOOT_BUILT_BIN)
	@mkdir -p $(BSP_UBOOT_OUT)/.out
	@cp $(BSP_UBOOT_BUILT_BIN) $(BSP_UBOOT_OUT)/.out/u-boot_autopoweron.bin
	@cp $(BSP_UBOOT_DTB_BUILT) $(BSP_UBOOT_OUT)/.out/u-boot_autopoweron
	@cp $(BSP_UBOOT_DTB_SYSTEM_MAP) $(BSP_UBOOT_OUT)/.out/System_autopoweron.map
	@cp $(BSP_UBOOT_DTB_CFG) $(BSP_UBOOT_OUT)/.out/u-boot_autopoweron.cfg
	$(MAKE) ARCH=$(SRCARCH) DEVICE_TREE=$(BSP_UBOOT_TARGET_DTB) CROSS_COMPILE=$(UBOOT_TOOLCHAIN) O=$(BSP_UBOOT_OUT) clean
	$(MAKE) ARCH=$(SRCARCH) DEVICE_TREE=$(BSP_UBOOT_TARGET_DTB) CROSS_COMPILE=$(UBOOT_TOOLCHAIN) O=$(BSP_UBOOT_OUT)
	-cp $(BSP_UBOOT_DTB_BUILT_BIN) $(BSP_UBOOT_BUILT_BIN)
	@cp $(BSP_UBOOT_BUILT_BIN) $(BSP_FDL2_BUILT_BIN)
	@mv $(BSP_UBOOT_OUT)/.out/* $(BSP_UBOOT_OUT)/
	@rm -rf $(BSP_UBOOT_OUT)/.out
	@echo "Install U-Boot target done"

$(BSP_UBOOT_OUT):
	@echo "Start U-Boot build board $(BSP_UBOOT_DEFCONFIG)"

$(BSP_UBOOT_CONFIG): configs/$(addsuffix _defconfig,$(BSP_UBOOT_DEFCONFIG)) $(BSP_UBOOT_OUT)
	@mkdir -p $(BSP_UBOOT_OUT)
	$(MAKE) ARCH=$(SRCARCH) CROSS_COMPILE=$(UBOOT_TOOLCHAIN) O=$(BSP_UBOOT_OUT) distclean
	$(MAKE) ARCH=$(SRCARCH) CROSS_COMPILE=$(UBOOT_TOOLCHAIN) O=$(BSP_UBOOT_OUT) $(BSP_UBOOT_DEFCONFIG)_defconfig

ifeq ($(strip $(NORMAL_UART_MODE)),true)
	@echo "#define NORMAL_UART_MODE" >> $(BSP_UBOOT_CONFIG)
endif

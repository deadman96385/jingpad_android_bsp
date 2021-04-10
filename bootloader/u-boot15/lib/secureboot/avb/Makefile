
ccflags-y := -I$(srctree)/lib/avb/libavb \
            -I$(srctree)/lib/avb
#libavb
obj-y += \
    libavb/avb_chain_partition_descriptor.o \
    libavb/avb_cmdline.o \
    libavb/avb_crc32.o \
    libavb/avb_crypto.o \
    libavb/avb_descriptor.o \
    libavb/avb_footer.o \
    libavb/avb_hash_descriptor.o \
    libavb/avb_hashtree_descriptor.o \
    libavb/avb_kernel_cmdline_descriptor.o \
    libavb/avb_property_descriptor.o \
    libavb/avb_rsa.o \
    libavb/avb_sha256.o \
    libavb/avb_sha512.o \
    libavb/avb_slot_verify.o \
    libavb/avb_sysdeps_posix.o \
    libavb/avb_util.o \
    libavb/avb_vbmeta_image.o \
    libavb/avb_version.o

obj-y += avb_check.o
obj-y += uboot_avb_ops.o
obj-y += uboot_avb_util.o

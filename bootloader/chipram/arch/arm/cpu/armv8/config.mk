
PLATFORM_RELFLAGS += -fno-common -ffixed-r8
#-msoft-float

# Make ARMv5 to allow more compilers to work, even though its v7a.
PF_CPPFLAGS_ARMV7 := $(call cc-option, -march=armv7-a, -march=armv8-a)
PLATFORM_CPPFLAGS += $(PF_CPPFLAGS_ARMV7)
# =========================================================================
#
# Supply options according to compiler version
#
# =========================================================================
PLATFORM_RELFLAGS +=$(call cc-option,-mshort-load-bytes,\
		    $(call cc-option,-malignment-traps,))

PLATFORM_RELFLAGS +=$(call cc-option,-mno-unaligned-access)
PLATFORM_RELFLAGS += $(call cc-option, -msoft-float)

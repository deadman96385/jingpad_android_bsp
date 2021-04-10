ifdef CONFIG_FPGA
DDR_COBJS       = dram_cfg_fpga.o umctl_fpga.o
SCAN_COBJS       = dram_cfg_28nm.o umctl_28nm.o ddr_scan_28nm.o
else
ifdef CONFIG_UMCTL_28NM
SCAN_COBJS       = dram_cfg_28nm.o umctl_28nm.o ddr_scan_28nm.o
DDR_COBJS       = dram_cfg_28nm.o umctl_28nm.o
DDR_AUTO_SLT_COBJS	= umctl_28nm.o dram_cfg_28nm.o auto_slt.o burst8_write_all.o burst_transfer.o 
else
ifdef CONFIG_SPRD_DMC_R1P0
DDR_COBJS	= dmc_sprd_r1p0.o dmc_sprd_r1p0_bist.o dmc_sprd_misc.o lpddr2_cfg.o lpddr3_cfg.o dmc_pin_cfg.o ddr_scan_online_sprd_r1p0.o
else
DDR_COBJS       = dram_cfg.o umctl.o ddr_scan.o
endif
endif
endif

DDR_SCAN: ddr_scan_dir_creat ddr_scan
DDR_AUTO_SLT: ddr_auto_slt_dir_creat ddr_auto_slt
ddr_scan_dir_creat:
	@mkdir -p $(obj)ddr_scan/board/$(VENDOR)/$(SOC)
ddr_auto_slt_dir_creat:
	@mkdir -p $(obj)ddr_auto_slt/board/$(VENDOR)/$(SOC)
ifdef CONFIG_FPGA
DDR_SCAN_LDSCRIPT      = $(TOPDIR)/ddr_scan/board/$(VENDOR)/$(SOC)/ddr_scan_fpga.lds
else
ifdef CONFIG_UMCTL_28NM
DDR_SCAN_LDSCRIPT      = $(TOPDIR)/ddr_scan/board/$(VENDOR)/$(SOC)/ddr_scan.lds
DDR_AUTO_SLT_LDSCRIPT  = $(TOPDIR)/ddr_auto_slt/board/$(VENDOR)/$(SOC)/ddr_auto_slt.lds
else
ifdef CONFIG_SPRD_DMC_R1P0
DDR_SCAN_LDSCRIPT      = $(TOPDIR)/ddr_scan/board/$(VENDOR)/$(SOC)/ddr_scan_sprd_dmc.lds
else
DDR_SCAN_LDSCRIPT      = $(TOPDIR)/ddr_scan/board/$(VENDOR)/$(SOC)/ddr_scan.lds
endif
endif
endif

DDR_SCAN_LDFLAGS  = -Bstatic -T $(DDR_SCAN_LDSCRIPT) $(PLATFORM_LDFLAGS)

DDR_SCAN_PATH     = $(TOPDIR)/ddr_scan/

DDR_SCAN_LNDIR   := $(OBJTREE)/ddr_scan/board/$(VENDOR)/$(SOC)
DDR_SCANOBJDIR   := $(DDR_SCAN_LNDIR)/

ifdef CONFIG_FPGA
DDR_SCAN_OBJ_FILE = ddr_scan_main.o  init.o chip_cfg.o
else
DDR_SCAN_OBJ_FILE = ddr_scan_main.o  switch64.o init.o chip_cfg.o
endif

DDR_SCAN_OBJ_FILE += adi.o $(SCAN_COBJS) mcu.o

DDR_SCAN_OBJS    = $(addprefix $(DDR_SCANOBJDIR),$(DDR_SCAN_OBJ_FILE))

ddr_scanobj       := $(OBJTREE)/ddr_scan/

ifdef CONFIG_SPRD_DMC_R1P0
#ddr_scan:	$(ddr_scanobj)ddr_scan.bin
else
ddr_scan:	$(ddr_scanobj)ddr_scan.bin
endif


$(ddr_scanobj)ddr_scan.bin : $(ddr_scanobj)ddr_scan.axf
	$(OBJCOPY) ${OBJCFLAGS} -O binary $< $@

$(ddr_scanobj)ddr_scan.axf: $(DDR_SCAN_OBJS)
	cd $(DDR_SCAN_LNDIR) && $(LD) $(DDR_SCAN_LDFLAGS) \
		$(DDR_SCAN_OBJ_FILE)  \
		-Map $(ddr_scanobj)ddr_scan.map \
		-o $@ $(PLATFORM_LIBS)

#########################################################################

$(DDR_SCAN_LNDIR)/%.o:$(SRCTREE)/ddr_scan/%.c
	$(CC) $(CFLAGS) -I $(DDR_SCAN_PATH)/inc  -c -o $@ $<
$(DDR_SCAN_LNDIR)/%.o:$(SRCTREE)/ddr_scan/%.S
	$(CC) $(AFLAGS) -I $(DDR_SCAN_PATH)/inc  -c -o $@ $<
$(DDR_SCAN_LNDIR)/%.o:$(SRCTREE)/arch/$(ARCH)/cpu/$(CPU)/$(SOC)/%.S
	$(CC) $(AFLAGS) -I $(DDR_SCAN_PATH)/inc  -c -o $@ $<
$(DDR_SCAN_LNDIR)/%.o:$(SRCTREE)/arch/$(ARCH)/cpu/$(CPU)/$(SOC)/%.c
	$(CC) $(CFLAGS) -I $(DDR_SCAN_PATH)/inc  -c -o $@ $<

$(DDR_SCAN_LNDIR)/%.o:$(SRCTREE)/arch/$(ARCH)/cpu/sprd_dmc/%.c
	$(CC) $(CFLAGS) -I $(DDR_SCAN_PATH)/inc  -DDDR_SCAN_SUPPORT_28NM -c -o $@ $<

#########################################################################i


DDR_AUTO_SLT_LDFLAGS  = -Bstatic -T $(DDR_AUTO_SLT_LDSCRIPT) $(PLATFORM_LDFLAGS)

DDR_AUTO_SLT_PATH     = $(TOPDIR)/ddr_auto_slt/

DDR_AUTO_SLT_LNDIR   := $(OBJTREE)/ddr_auto_slt/board/$(VENDOR)/$(SOC)
DDR_AUTO_SLTOBJDIR   := $(DDR_AUTO_SLT_LNDIR)/

DDR_AUTO_SLT_OBJ_FILE = ddr_auto_slt_main.o  switch64.o init.o chip_cfg.o
DDR_AUTO_SLT_OBJ_FILE += adi.o $(DDR_AUTO_SLT_COBJS) mcu.o

DDR_AUTO_SLT_OBJS    = $(addprefix $(DDR_AUTO_SLTOBJDIR),$(DDR_AUTO_SLT_OBJ_FILE))

ddr_auto_sltobj       := $(OBJTREE)/ddr_auto_slt/

ifdef CONFIG_SPRD_DMC_R1P0
#ddr_auto_slt: ddr_auto_slt_dir_creat   $(ddr_auto_sltobj)ddr_auto_slt.bin
else
ddr_auto_slt: ddr_auto_slt_dir_creat  $(ddr_auto_sltobj)ddr_auto_slt.bin
endif


$(ddr_auto_sltobj)ddr_auto_slt.bin : $(ddr_auto_sltobj)ddr_auto_slt.axf
	$(OBJCOPY) ${OBJCFLAGS} -O binary $< $@

$(ddr_auto_sltobj)ddr_auto_slt.axf: $(DDR_AUTO_SLT_OBJS)
	cd $(DDR_AUTO_SLT_LNDIR) && $(LD) $(DDR_AUTO_SLT_LDFLAGS) \
                $(DDR_AUTO_SLT_OBJ_FILE)  \
                -Map $(ddr_auto_sltobj)ddr_auto_slt.map \
                -o $@ $(PLATFORM_LIBS)

#########################################################################

$(DDR_AUTO_SLT_LNDIR)/%.o:$(SRCTREE)/ddr_auto_slt/%.c
	$(CC) $(CFLAGS) -I $(DDR_AUTO_SLT_PATH)/inc  -c -o $@ $<
$(DDR_AUTO_SLT_LNDIR)/%.o:$(SRCTREE)/ddr_auto_slt/%.S
	$(CC) $(AFLAGS) -I $(DDR_AUTO_SLT_PATH)/inc  -c -o $@ $<
$(DDR_AUTO_SLT_LNDIR)/%.o:$(SRCTREE)/arch/$(ARCH)/cpu/$(CPU)/$(SOC)/%.S
	$(CC) $(AFLAGS) -I $(DDR_AUTO_SLT_PATH)/inc  -c -o $@ $<
$(DDR_AUTO_SLT_LNDIR)/%.o:$(SRCTREE)/arch/$(ARCH)/cpu/$(CPU)/$(SOC)/%.c
	$(CC) $(CFLAGS) -I $(DDR_AUTO_SLT_PATH)/inc  -c -o $@ $<

$(DDR_AUTO_SLT_LNDIR)/%.o:$(SRCTREE)/arch/$(ARCH)/cpu/sprd_dmc/%.c
	$(CC) $(CFLAGS) -I $(DDR_AUTO_SLT_PATH)/inc  -DDDR_AUTO_SLT_SUPPORT_28NM -c -o $@ $<

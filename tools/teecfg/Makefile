ifeq ($(BSP_BOARD_TEECFG_CUSTOM),true)
inc := -Iinc/
libxml32 := lib/lib/libxml2.so.2.9.1
libxml64 := lib/lib64/libxml2.so.2.9.1

OS_BIT = $(shell getconf LONG_BIT)
ifeq ($(OS_BIT), 64)
libxml := $(libxml64)
else
libxml := $(libxml32)
endif

version := 0.1

teecfg_tool_deps := src/teecfg_tool.c src/teecfg_generate.c src/common.c src/teecfg_display.c
gcc_deps := $(inc) $(libxml) -DVERSION=\"$(version)\"

teecfg_tool: $(teecfg_tool_deps)
	gcc -o $@ $^ $(gcc_deps)
	chmod +x teecfg_tool
	mkdir -p "$(build_out)"
	mkdir -p "$(build_out)/lib"
	mkdir -p "$(build_out)/lib64"
	mv teecfg_tool $(build_out)
	cp -f $(libxml32) $(build_out)/lib
	cp -f $(libxml64) $(build_out)/lib64
endif




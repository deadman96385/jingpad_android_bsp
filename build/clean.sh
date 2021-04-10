#!/bin/bash

function source_configuration()
{
	# the max number of parameters is 1, one of "chipram uboot tos sml kernel"
	# if "$1".is null, only include the common.cfg
	if [[ -f $BSP_SYSTEM_COMMON/common.cfg ]]; then
		echo "source $BSP_SYSTEM_COMMON/common.cfg"
		source $BSP_SYSTEM_COMMON/common.cfg
	fi

	if [[ -f $BSP_SYSTEM_COMMON/$1.cfg ]]; then
		echo "source $BSP_SYSTEM_COMMON/1.cfg"
		source $BSP_SYSTEM_COMMON/$1.cfg
	fi

	if [[ -f $BSP_BOARD_BASE_PATH/common.cfg ]]; then
		echo "source $BSP_BOARD_BASE_PATH/common.cfg"
		source $BSP_BOARD_BASE_PATH/common.cfg
	fi

	if [[ -f $BSP_BOARD_BASE_PATH/$1.cfg ]]; then
		echo "source $BSP_BOARD_BASE_PATH/$1.cfg"
		source $BSP_BOARD_BASE_PATH/$1.cfg
	fi

	if [[ -f $BSP_PRODUCT_PATH/common.cfg ]]; then
		echo "source $BSP_PRODUCT_PATH/common.cfg"
		source $BSP_PRODUCT_PATH/common.cfg
	fi

	if [[ -f $BSP_PRODUCT_PATH/$1.cfg ]]; then
		echo "source $BSP_PRODUCT_PATH/$1.cfg"
		source $BSP_PRODUCT_PATH/$1.cfg
	fi
}

function do_clean_chipram()
{
	echo do_clean_chipram
}

function do_clean_sml()
{
	echo do_clean_sml
}

function do_clean_tos()
{
	echo do_clean_tos
}

function do_clean_uboot()
{
	echo do_clean_uboot
}

function clean_modules()
{
	for BSP_MOD_PATH in $BSP_MOD_PATH_LIST;
	do
		if (cat $BSP_MOD_PATH | grep -w "$BSP_MOD\.o\|KO_MODULE_NAME\s*:=\s*$BSP_MOD" > /dev/null); then
			echo ======================================================================
			echo CLEAN $BSP_MOD.o $BSP_MOD_PATH
			echo ======================================================================
			make -C ${BSP_MOD_PATH%/*} -f Makefile clean -j$BSP_OBJ
			if [[ $? -ne 0 ]]; then
				return_val=1
			fi
		fi
	done
}

function do_clean_modules()
{
	if [[ ! -d $BSP_MODULES_OUT ]]; then
		return
	fi

	echo -e "\033[32m #### start clean modules #### \033[0m"

	unset BSP_MOD

	BSP_MOD_PATH_LIST=`find $BSP_ROOT_DIR/modules -type f -name "Makefile"`

	if [[ $# -gt 2 ]]; then
		if [[ $# -eq 4 ]] && [[ $3 == "-m" ]]; then
			BSP_MOD=$(echo $4 | awk -F".ko" {'print $1'})
			clean_modules
		fi
	else
		for BSP_MOD_NAME in $BSP_MODULES_LIST;
		do
			BSP_MOD=$(echo $BSP_MOD_NAME | awk -F".ko" {'print $1'})

			clean_modules
			if [ $? -ne 0 ]; then
				return_val=1
				failure_handle $BSP_MOD.ko
				exit 1
			fi
		done
	fi

	failure_handle clean_modules
}

function do_clean_kernel()
{
	if [[ ! -d $BSP_KERNEL_OUT ]]; then
		return
	fi

	echo -e "\033[32m #### start clean kernel #### \033[0m"

	cd $BSP_KERNEL_PATH
	make -C $BSP_KERNEL_PATH O=$BSP_KERNEL_OUT $BSP_MAKE_EXTRA_ARGS ARCH=$BSP_BOARD_ARCH CROSS_COMPILE=$BSP_KERNEL_CROSS_COMPILE mrproper -j$BSP_OBJ
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi

	cd $BSP_ROOT_DIR

	failure_handle clean_kernel
}

function do_clean()
{
	source_configuration modules

	local bsp_clean_module bsp_module

	if [ $# -eq 1 ]; then
		bsp_module="chipram sml tos uboot kernel modules"
	elif [ $# -eq 2 ]; then
		case "$2" in
		chipram)   bsp_module="$bsp_module chipram" ;;
		sml)       bsp_module="$bsp_module sml"     ;;
		tos)       bsp_module="$bsp_module tos"     ;;
		uboot)     bsp_module="$bsp_module uboot"   ;;
		kernel)    bsp_module="$bsp_module kernel"  ;;
		modules)   bsp_module="$bsp_module modules" ;;
		*)
			echo -e "\033[31m bsp module name error. $2\033[0m"
		esac
	elif [ $# -eq 4 ]; then
		do_clean_modules $@
	else
		echo -e "\033[31m bsp module name error. $2\033[0m"
	fi

	for bsp_clean_module in $bsp_module;
	do
		do_clean_$bsp_clean_module $@
	done
}

do_clean $@

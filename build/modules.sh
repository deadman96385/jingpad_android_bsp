function source_configuration()
{
	# the max number of parameters is 1, one of "chipram uboot tos sml kernel"
	# if "$1".is null, only include the common.cfg
	if [[ -f $BSP_SYSTEM_COMMON/common.cfg ]]; then
		echo "source $BSP_SYSTEM_COMMON/common.cfg"
		source $BSP_SYSTEM_COMMON/common.cfg
	fi

	if [[ -f $BSP_SYSTEM_COMMON/$1.cfg ]]; then
		echo "source $BSP_SYSTEM_COMMON/$1.cfg"
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

function compile_modules()
{
	BSP_MOD_NAME="$BSP_MOD".ko

	if (cat $BSP_MOD_PATH | grep -w "$BSP_MOD\.o\|KO_MODULE_NAME\s*:=\s*$BSP_MOD" > /dev/null); then
		echo ======================================================================
		echo MAKE $BSP_MOD.o $BSP_MOD_PATH
		echo ======================================================================
		make -C ${BSP_MOD_PATH%/*} -f Makefile O=$BSP_KERNEL_OUT $BSP_MAKE_EXTRA_ARGS ARCH=$BSP_BOARD_ARCH CROSS_COMPILE=$BSP_KERNEL_CROSS_COMPILE modules -j$BSP_OBJ
		if [ $? -ne 0 ]; then
			return_val=1
			failure_handle $BSP_MOD.ko
			exit 1
		fi

		make -C ${BSP_MOD_PATH%/*} -f Makefile O=$BSP_KERNEL_OUT $BSP_MAKE_EXTRA_ARGS ARCH=$BSP_BOARD_ARCH CROSS_COMPILE=$BSP_KERNEL_CROSS_COMPILE INSTALL_MOD_PATH=$BSP_MODULES_OUT modules_install -j$BSP_OBJ
		if [ $? -ne 0 ]; then
			return_val=1
			failure_handle $BSP_MOD.ko
			exit 1
		fi

		find $BSP_MODULES_OUT/lib/modules -name $BSP_MOD_NAME | xargs -i cp {} $BSP_MODULES_DIST
	fi
}

function do_make_modules()
{
	source_configuration modules

	source build/envsetup.sh

	if [ "$(type -t make_kernel)" = "function" ] ; then
		make_kernel
		if [ $? -ne 0 ]; then
			exit 1
		fi
	fi

	mkdir $BSP_MODULES_OUT -p
	mkdir $BSP_MODULES_DIST -p

	BSP_MOD_PATH_LIST=`find $BSP_ROOT_DIR/modules -type f -name "Makefile"`

	while ((1)); do
		if [ "$(type -t make)" = "function" ] ; then
			unset make
		else
			break
		fi
	done

	local specified_ko
	shift
	while getopts ":m:" opt
	do
		case "$opt" in
		m) specified_ko=$OPTARG ;;
		*) ;;
		esac
	done

	if [[ -z $specified_ko ]]; then
		local bsp_modules_list_result bsp_modules_del

		bsp_modules_list_result=$BSP_MODULES_LIST$BSP_MODULES_LIST_ADD

		for bsp_modules_del in $BSP_MODULES_LIST_DEL;
		do
			bsp_modules_list_result=`echo $bsp_modules_list_result | sed "s/$bsp_modules_del//g"`
		done

		echo ======================================================================
		echo COMPILE MODULES: $bsp_modules_list_result
		echo ======================================================================

		for BSP_MOD_NAME in $bsp_modules_list_result;
		do
			BSP_MOD=$(echo $BSP_MOD_NAME | awk -F".ko" {'print $1'})

			for BSP_MOD_PATH in $BSP_MOD_PATH_LIST;
			do
				compile_modules
				if [ $? -ne 0 ]; then
					return_val=1
					failure_handle $BSP_MOD.ko
					exit 1
				fi
			done
		done
	else
		echo "Only compile the specified ko named $specified_ko."
		BSP_MOD=$(echo $specified_ko | awk -F".ko" {'print $1'})
		for BSP_MOD_PATH in $BSP_MOD_PATH_LIST;
		do
			compile_modules
			if [ $? -ne 0 ]; then
				return_val=1
				failure_handle $BSP_MOD.ko
				exit 1
			fi
		done
	fi

	export make
}

do_make_modules $@


if [[ $BUILD_FROM_ANDROID == "true" ]]; then
	echo "Compile from Android ..."
else
	echo "Compile from BSP ..."
fi

function export_env_first()
{
	export BSP_ROOT_DIR=$PWD
	export BSP_OUT_DIR=$BSP_ROOT_DIR/out
	export BSP_SIGN_DIR=$BSP_ROOT_DIR/build/packimage_scripts
	export BSP_OBJ=`cat /proc/cpuinfo | grep processor | wc -l`

	if [[ ! -d "$BSP_ROOT_DIR/toolchain/prebuilts/clang" ]]; then
		echo clang is not exist, create link from android
		ln -sf $BSP_ROOT_DIR/../prebuilts/clang $BSP_ROOT_DIR/toolchain/prebuilts/clang
	fi
}
export_env_first

function get_product()
{
	SEARCH_DIR="device"
	BOARD_PATH=`find $BSP_ROOT_DIR/$SEARCH_DIR -type d`
	for product_path in $BOARD_PATH;
	do
		if [[ "common" == `echo $product_path | awk -F"$SEARCH_DIR/" {'print $2'} | awk -F"/" {'print $3'}` ]]; then
			continue
		fi

		local product_name=`echo $product_path | awk -F"$SEARCH_DIR/" {'print $2'} | awk -F"/" {'if (NF == 4 && $NF != ".git" && !($NF~"_base")) print $NF'}`
		local platform=`echo $product_path | awk -F"$SEARCH_DIR/" {'print $2'} | awk -F"/" {'print $2'}`

		if [[ -n "$product_name" ]]; then
			local key=$product_name"-"$platform
			d_product+=([$key]="$product_path")
			l_product=("${l_product[@]}" "$key")
		fi
	done
}

function print_header()
{
	echo "Lunch menu... pick a combo:"
	echo
	echo "You're building on Linux"
	echo "Pick a number:"
	echo "choice a project"

	for i in $(seq 0 $((${#l_product[@]}-1)) ); do
		local tmp_platform=`echo ${d_product["${l_product[$i]}"]} \
			| awk -F"device/" {'print $2'} | awk -F"/" {'print $2'}`
		local tmp_product=`echo ${l_product[$i]} | awk -F"-" '{sub( FS "[^" FS "]*$","");print $0}'`
		local tmp_platform=`echo ${l_product[$i]} | awk -F"-" {'print $NF'}`

		printf "  %d. %s-%s-%s\n" $((i+1)) $tmp_product 'userdebug' $tmp_platform
	done

	printf "Which would you like? "
}

function chooseboard()
{
	if [[ $# == 0 ]]; then
		print_header
		read -a get_line
	elif [[ $# == 1 ]]; then
		get_line=$1
		echo $get_line
	else
		echo -e "\033[31m The num of parameter is error. \033[0m"
		return 1
	fi

	if (echo -n $get_line | grep -q -e "^[0-9][0-9]*$"); then
		if [[ "$get_line" -le "${#l_product[@]}" ]] ; then
			input_product=`echo ${l_product[$((get_line-1))]} | awk -F"-" '{sub( FS "[^" FS "]*$","");print $0}'`
			input_platform=`echo ${l_product[$((get_line-1))]} | awk -F"-" {'print $NF'}`
			product_platform_version=$input_product"-userdebug"
			product_version="userdebug"
		else
			echo -e "\033[31m The num you input is out of range, please check. \033[0m"
			return 1
		fi
	else
		if (echo $get_line | grep -v "-" > /dev/null); then
			echo -e "\033[31m The board name was error, please check. \033[0m"
			return 1
		fi

		input_product=`echo $get_line | awk -F"-" {'print $1'}`
		input_platform=`echo $get_line | awk -F"-" {'print $NF'}`
		local key=$input_product"-"$input_platform
		if [[ -n $d_product[$key] ]]; then
			product_version=`echo $get_line | awk -F"-" {'print $2'}`
			if [[ $product_version != "userdebug" ]] && [[ $product_version != "user" ]]; then
				echo -e "\033[31m The board name was error, please check. \033[0m"
				return 1
			else
				product_platform_version=$input_product"-"$product_version
			fi
		else
			echo -e "\033[31m The board name was error, please check. \033[0m"
			return 1
		fi
	fi

	product_platform=$input_product"-"$input_platform
	export BSP_BUILD_VARIANT=$product_version
	export BSP_PLATFORM_VERSION=$input_platform

	return 0
}

function print_envinfo()
{
	export BSP_PRODUCT_NAME=$input_product
	export BSP_PRODUCT_PATH=${d_product["$product_platform"]}
	export BSP_BOARD_NAME=`echo $BSP_PRODUCT_PATH | awk -F"$SEARCH_DIR/" {'print $2'} | awk -F"/" {'print $3'}`
	export BSP_BOARD_PATH=`echo $BSP_PRODUCT_PATH | awk -F"/" '{sub( FS "[^" FS "]*$","");print $0}'`
	export BSP_SYSTEM_VERSION=`echo $BSP_PRODUCT_PATH | awk -F"$SEARCH_DIR/" {'print $2'} | awk -F"/" {'print $1'}`
	export BSP_BOARD_BASE_PATH=$BSP_BOARD_PATH/"$BSP_BOARD_NAME"_base
	export BSP_SYSTEM_COMMON=`echo $BSP_PRODUCT_PATH | awk -F"$SEARCH_DIR/" {'print $1'}`"device/"$BSP_SYSTEM_VERSION"/"$BSP_PLATFORM_VERSION

	echo "BSP_PRODUCT_NAME  : " $BSP_PRODUCT_NAME
	echo "BSP_BUILD_VARIANT : " $BSP_BUILD_VARIANT
	echo "BSP_PRODUCT_PATH  : " $BSP_PRODUCT_PATH
}

function source_configuration()
{
	# the max number of parameters is 1, one of "chipram uboot tos sml kernel"
	# if "$1".is null, only include the common.cfg
	if [[ -f $BSP_SYSTEM_COMMON/common/common.cfg ]]; then
		echo "source $BSP_SYSTEM_COMMON/common/common.cfg"
		source $BSP_SYSTEM_COMMON/common/common.cfg
	fi

	if [[ -f $BSP_SYSTEM_COMMON/common/$1.cfg ]]; then
		echo "source $BSP_SYSTEM_COMMON/common/$1.cfg"
		source $BSP_SYSTEM_COMMON/common/$1.cfg
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

function lunch()
{
	input_product=''
	product_platform_version=''
	get_line=''
	unset l_product d_product

	env_clean
	declare -A d_product

	export_env_first

	get_product
	chooseboard $1
	if [[ $? == 0 ]]; then
		print_envinfo
	fi

	get_kernel_cfg
}

function sprd_create_user_config()
{
	if [ $# -ne 2 ]; then
		echo "Parameters error! Please check."
	fi
	cd $BSP_KERNEL_PATH
	bash scripts/sprd/sprd_create_user_config.sh $1 $2
	l_diffconfig_files_used=("${l_diffconfig_files_used[@]}" "$2")
	cd $BSP_ROOT_DIR
}

function add_diffconfig()
{
	local BSP_OUT_KERNEL_CONFIG="$BSP_KERNEL_OUT/.config"
	local BSP_BOARD_SPEC_CONFIG=$BSP_KERNEL_DIFF_CONFIG_ARCH/$BSP_BOARD_NAME"_diff_config"
	sprd_create_user_config $BSP_OUT_KERNEL_CONFIG $BSP_BOARD_SPEC_CONFIG

	local BSP_PRODUCT_SPEC_CONFIG=$BSP_KERNEL_DIFF_CONFIG_ARCH/$BSP_PRODUCT_NAME"_diff_config"
	sprd_create_user_config $BSP_OUT_KERNEL_CONFIG $BSP_PRODUCT_SPEC_CONFIG

	# e.g. sprd-diffconfig/android/sharkl3/common/sharkl3_diff_config can be touched if needed.
	# Be careful, this file is also effective to non-andriod product.
	local BSP_BOARD_COMMON_CONFIG=$BSP_KERNEL_DIFF_CONFIG_COMMON/$BSP_SYSTEM_VERSION"_diff_config"
	sprd_create_user_config $BSP_OUT_KERNEL_CONFIG $BSP_BOARD_COMMON_CONFIG

	if [ "$BSP_BOARD_DEBIAN_CONFIG" == "true" ]; then
		local BSP_DEVICE_DEBIAN_CONFIG=$BSP_KERNEL_PATH/sprd-diffconfig/debian/debian_diff_config
		sprd_create_user_config $BSP_OUT_KERNEL_CONFIG $BSP_DEVICE_DEBIAN_CONFIG
	fi

	if [ "$BSP_BOARD_TEST_CONFIG" == "true" ]; then
		local BSP_DEVICE_TEST_CONFIG=$BSP_KERNEL_PATH/sprd-diffconfig/debian/test_diff_config
		sprd_create_user_config $BSP_OUT_KERNEL_CONFIG $BSP_DEVICE_TEST_CONFIG
	fi

	if [ "$BSP_BOARD_TEE_CONFIG" == "trusty" ]; then
		if [ -n "$BSP_BOARD_TEE_64BIT" ]; then
			if [ "$BSP_BOARD_TEE_64BIT" == "false" ]; then
				local BSP_DEVICE_TRUSTY_CONFIG=$BSP_KERNEL_DIFF_CONFIG_ARCH/trusty_aarch32_diff_config
			else
				local BSP_DEVICE_TRUSTY_CONFIG=$BSP_KERNEL_DIFF_CONFIG_ARCH/trusty_aarch64_diff_config
			fi
		else
			local BSP_DEVICE_TRUSTY_CONFIG=$BSP_KERNEL_DIFF_CONFIG_ARCH/trusty_diff_config
		fi

		sprd_create_user_config $BSP_OUT_KERNEL_CONFIG $BSP_DEVICE_TRUSTY_CONFIG
	fi

	if [ "$BSP_BOARD_WCN_CONFIG" == "ext" ]; then
		local BSP_DEVICE_WCN_CONFIG=$BSP_KERNEL_DIFF_CONFIG_COMMON/wcn_ext_diff_config
	elif [ "$BSP_BOARD_WCN_CONFIG" == "built-in" ]; then
		local BSP_DEVICE_WCN_CONFIG=$BSP_KERNEL_DIFF_CONFIG_COMMON/wcn_built_in_diff_config
	fi

	if [ -n "$BSP_DEVICE_WCN_CONFIG" ]; then
		sprd_create_user_config $BSP_OUT_KERNEL_CONFIG $BSP_DEVICE_WCN_CONFIG
	fi

	if [ "$BSP_PRODUCT_GO_DEVICE" == "true" ]; then
		local BSP_GO_DEVICE_CONFIG=$BSP_KERNEL_DIFF_CONFIG_ARCH/go_google_diff_config
		sprd_create_user_config $BSP_OUT_KERNEL_CONFIG $BSP_GO_DEVICE_CONFIG
	fi

	if [ "$BSP_BUILD_VARIANT" == "user" ]; then
		if [ "$BSP_BUILD_VARIANT" == "user" ]; then
			if [ "$BSP_BOARD_ARCH" == "arm" ]; then
				local BSP_DEVICE_USER_CONFIG=$BSP_KERNEL_DIFF_CONFIG_ARCH/aarch32_user_diff_config
			elif [ "$BSP_BOARD_ARCH" == "arm64" ]; then
				local BSP_DEVICE_USER_CONFIG=$BSP_KERNEL_DIFF_CONFIG_ARCH/aarch64_user_diff_config
			fi
		fi

		sprd_create_user_config $BSP_OUT_KERNEL_CONFIG $BSP_DEVICE_USER_CONFIG
	fi

	echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	echo "  ****  WARNING: listed diffconfigs below are used for compile  ****     "
	for files in ${l_diffconfig_files_used[@]};
	do
		echo $files
	done
	echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
}

function kuconfig()
{
	command make -C $BSP_KERNEL_PATH O=$BSP_KERNEL_OUT $BSP_MAKE_EXTRA_ARGS ARCH=$BSP_BOARD_ARCH CROSS_COMPILE=$BSP_KERNEL_CROSS_COMPILE $BSP_KERNEL_DEFCONFIG menuconfig -j$BSP_OBJ
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi

	cp $BSP_KERNEL_OUT/.config $BSP_KERNEL_PATH/arch/$BSP_BOARD_ARCH/configs/$BSP_KERNEL_DEFCONFIG
	cd $BSP_ROOT_DIR
}

function get_kernel_cfg()
{
	if [[ -n $BSP_KERNEL_OUT ]]; then
		return
	fi

	source_configuration kernel

	export BSP_KERNEL_OUT=$BSP_OUT_DIR/$BSP_BOARD_NAME/obj/kernel
	export BSP_KERNEL_DIST=$BSP_OUT_DIR/$BSP_BOARD_NAME/dist/kernel
	export BSP_KERNEL_PATH=$BSP_ROOT_DIR/kernel/$BSP_KERNEL_VERSION

	export BSP_MODULES_OUT=$BSP_OUT_DIR/$BSP_BOARD_NAME/obj/modules
	export BSP_MODULES_DIST=$BSP_OUT_DIR/$BSP_BOARD_NAME/dist/modules
}

function make_modules()
{
	echo -e "\033[32m #### start build modules #### \033[0m"

	bash build/modules.sh $@
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi

	failure_handle modules
}

function make_chipram()
{
	echo -e "\033[32m #### start build chipram #### \033[0m"
	source_configuration chipram

	export BSP_CHIPRAM_OUT=$BSP_OUT_DIR/$BSP_BOARD_NAME/obj/$BSP_CHIPRAM_VERSION
	export BSP_CHIPRAM_DIST=$BSP_OUT_DIR/$BSP_BOARD_NAME/dist/$BSP_CHIPRAM_VERSION
	export BSP_CHIPRAM_PATH=$BSP_ROOT_DIR/bootloader/$BSP_CHIPRAM_VERSION

	cd $BSP_CHIPRAM_PATH
	bash make.sh bsp
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi
	cd $BSP_ROOT_DIR

	mkdir -p $BSP_CHIPRAM_DIST
	for BSP_CHIPRAM_BIN in $BSP_CHIPRAM_FILE_LIST;
	do
		find $BSP_CHIPRAM_OUT -name $BSP_CHIPRAM_BIN | xargs -i cp {} $BSP_CHIPRAM_DIST
	done

	failure_handle chipram
}

function make_bootloader()
{
	echo -e "\033[32m #### start build bootloader #### \033[0m"

	source_configuration uboot

	export BSP_UBOOT_OUT=$BSP_OUT_DIR/$BSP_BOARD_NAME/obj/$BSP_UBOOT_VERSION
	export BSP_UBOOT_DIST=$BSP_OUT_DIR/$BSP_BOARD_NAME/dist/$BSP_UBOOT_VERSION
	export BSP_UBOOT_PATH=$BSP_ROOT_DIR/bootloader/$BSP_UBOOT_VERSION

	cd $BSP_UBOOT_PATH
	bash make.sh bsp
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi
	cd $BSP_ROOT_DIR

	for BSP_UBOOT_BIN in $BSP_UBOOT_FILE_LIST;
	do
		find $BSP_UBOOT_OUT -name $BSP_UBOOT_BIN | xargs -i cp {} $BSP_UBOOT_DIST
	done

	failure_handle bootloader
}

function make_sml()
{
	echo -e "\033[32m #### start build sml #### \033[0m"

	source_configuration sml

	export BSP_SML_OUT=$BSP_OUT_DIR/$BSP_BOARD_NAME/obj/sml
	export BSP_SML_DIST=$BSP_OUT_DIR/$BSP_BOARD_NAME/dist/sml


	if [[ "${BSP_SML_VERSION}" = "1.4" ]]; then
		export BSP_SML_PATH=$BSP_ROOT_DIR/sml/arm-trusted-firmware
	else
		export BSP_SML_PATH=$BSP_ROOT_DIR/sml/arm-trusted-firmware-1.3
	fi

	ATF_ARCH=`echo "${BSP_SML_TARGET_CONFIG}"|awk -F '@' '{print $3}'`

	if [[ "${ATF_ARCH}" = "arm64" ]]; then
		ATF_IMAGE="bl31.bin"
		ATF_SYMBOLS="bl31.elf"
	elif [[ "${ATF_ARCH}" = "arm32" ]]; then
		ATF_IMAGE="bl32.bin"
		ATF_SYMBOLS="bl32.elf"
	else
		${error No proper SML target configuration!}
	fi

	command make -C $BSP_SML_PATH -f Bspbuild.mk TOOL_CHAIN_ROOT=$BSP_ROOT_DIR/toolchain
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi

	if [[ ! -d "$BSP_SML_DIST" ]]; then
		mkdir -p $BSP_SML_DIST
	fi

	find $BSP_SML_OUT -name ${ATF_IMAGE} | xargs -i cp {} $BSP_SML_DIST/sml.bin
	find $BSP_SML_OUT -name ${ATF_SYMBOLS} | xargs -i cp {} $BSP_SML_DIST/

	failure_handle sml
}

function make_teecfg()
{
	echo -e "\033[32m #### start build teecfg #### \033[0m"

	get_kernel_cfg
	source_configuration common

	BSP_TEECFG_PATH=${BSP_ROOT_DIR}/tools/teecfg
	BSP_TEECFG_OUT=${BSP_OUT_DIR}/${BSP_BOARD_NAME}/obj/teecfg
	BSP_TEECFG_DIST=${BSP_OUT_DIR}/${BSP_BOARD_NAME}/dist/teecfg

	if [[ "${BSP_BOARD_TEECFG_CUSTOM}" != "true" ]]; then
		return 0
	fi

	signed_images+=" teecfg"

	echo "Build teecfg_tool"
	command make -C ${BSP_TEECFG_PATH} build_out=${BSP_TEECFG_OUT}
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi

	BSP_TEECFG_PLATFORM_XML_PATH=${BSP_ROOT_DIR}/device/${BSP_SYSTEM_VERSION}/${BSP_PLATFORM_VERSION}/common/teecfg
	BSP_BOARD_NAME_SUFFIX=_base
	BSP_TEECFG_BOARD_XML_PATH=${BSP_ROOT_DIR}/device/${BSP_SYSTEM_VERSION}/${BSP_PLATFORM_VERSION}/${BSP_BOARD_NAME}/${BSP_BOARD_NAME}${BSP_BOARD_NAME_SUFFIX}/teecfg
	BSP_TEECFG_PRODUCT_XML_PATH=${BSP_ROOT_DIR}/device/${BSP_SYSTEM_VERSION}/${BSP_PLATFORM_VERSION}/${BSP_BOARD_NAME}/${input_product}/teecfg
	BSP_TEECFG_INTERMEDIATE_XML_PATH=${BSP_TEECFG_OUT}/xml

	BSP_TEECFG_XML_OVERLAY_PARAMS="-i "${BSP_TEECFG_PLATFORM_XML_PATH}
	if [[ -e "${BSP_TEECFG_BOARD_XML_PATH}" ]]; then
		BSP_TEECFG_XML_OVERLAY_PARAMS+=" -b "${BSP_TEECFG_BOARD_XML_PATH}
	fi
	if [[ -e "${BSP_TEECFG_PRODUCT_XML_PATH}" ]]; then
		BSP_TEECFG_XML_OVERLAY_PARAMS+=" -p "${BSP_TEECFG_PRODUCT_XML_PATH}
	fi
	if [[ -e "${BSP_TEECFG_INTERMEDIATE_XML_PATH}" ]]; then
		rm -rf ${BSP_TEECFG_INTERMEDIATE_XML_PATH}
	fi
	if [[ "${BSP_BOARD_ARCH}" = "arm64" ]]; then
		BSP_TARGET_DTB_PATH=${BSP_KERNEL_PATH}/arch/arm64/boot/dts/sprd
	else
		BSP_TARGET_DTB_PATH=${BSP_KERNEL_PATH}/arch/arm/boot/dts
	fi
	BSP_TARGET_DTB=${BSP_TARGET_DTB_PATH}/${BSP_DTB}.dts
	BSP_TEECFG_XML_OVERLAY_PARAMS+=" --dtb "${BSP_TARGET_DTB}
	BSP_TARGET_DTBO=${BSP_TARGET_DTB_PATH}/${BSP_DTBO}.dts
	BSP_TEECFG_XML_OVERLAY_PARAMS+=" --dtbo "${BSP_TARGET_DTBO}
	mkdir -p ${BSP_TEECFG_INTERMEDIATE_XML_PATH}
	BSP_TEECFG_XML_OVERLAY_PARAMS+=" -o "${BSP_TEECFG_INTERMEDIATE_XML_PATH}

	echo "Overlay xml files"
	bash ${BSP_TEECFG_PATH}/teecfg_xml_overlay.sh ${BSP_TEECFG_XML_OVERLAY_PARAMS}
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi

	echo "Compile teecfg image using teecfg_tool"
	${BSP_TEECFG_OUT}/teecfg_tool -g -i ${BSP_TEECFG_INTERMEDIATE_XML_PATH} -o ${BSP_TEECFG_OUT}/teecfg.bin

	if [[ $? -ne 0 ]]; then
		return_val=1
	fi

	if [[ ! -e "${BSP_TEECFG_DIST}" ]]; then
		mkdir -p ${BSP_TEECFG_DIST}
	fi

	find ${BSP_TEECFG_OUT} -name teecfg.bin | xargs -i cp {} ${BSP_TEECFG_DIST}/
	failure_handle teecfg
}

function make_trusty()
{
	echo -e "\033[32m #### start build trusty #### \033[0m"

	source_configuration tos

	export BSP_TOS_OUT=$BSP_OUT_DIR/$BSP_BOARD_NAME/obj/trusty
	export BSP_TOS_PATH=$BSP_ROOT_DIR/trusty
	BSP_TOS_DIST=$BSP_OUT_DIR/$BSP_BOARD_NAME/dist/trusty

	if [[ "${BSP_BOARD_ARCH}" = "arm64" ]]; then
		TARGET_DTB_PATH=${BSP_KERNEL_PATH}/arch/arm64/boot/dts/sprd
	else
		TARGET_DTB_PATH=${BSP_KERNEL_PATH}/arch/arm/boot/dts
	fi

	TOS_TARGET_DTS=${TARGET_DTB_PATH}/${BSP_DTB}.dts

	if  [[ `echo $1 | grep "\-j"` = "" ]]; then
		shift 1
	fi

	command make -C $BSP_TOS_PATH -f Bspbuild.mk TOOL_CHAIN_ROOT=$BSP_ROOT_DIR/toolchain TOS_TARGET_DTS=${TOS_TARGET_DTS} TOP=$BSP_TOS_PATH $@
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi

	if [[ ! -d "$BSP_TOS_DIST" ]]; then
		mkdir -p $BSP_TOS_DIST
	fi

	find $BSP_TOS_OUT -name lk.bin | xargs -i cp {} $BSP_TOS_DIST/tos.bin
	find $BSP_TOS_OUT -name lk.elf | xargs -i cp {} $BSP_TOS_DIST/

	failure_handle trusty
}

function make_kernel()
{
	echo -e "\033[32m #### start build kernel #### \033[0m"

	make_config
	if [[ $? -ne 0 ]]; then
		echo_failure kernel
		return 1
	fi

	make_headers
	if [[ $? -ne 0 ]]; then
		echo_failure kernel
		return 1
	fi

	make_dtb
	if [[ $? -ne 0 ]]; then
		echo_failure kernel
		return 1
	fi

	mkdir $BSP_KERNEL_OUT -p
	command make -C $BSP_KERNEL_PATH O=$BSP_KERNEL_OUT $BSP_MAKE_EXTRA_ARGS ARCH=$BSP_BOARD_ARCH CROSS_COMPILE=$BSP_KERNEL_CROSS_COMPILE -j$BSP_OBJ
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi

	if [ -n $BSP_KERNEL_DIST ]; then
		mkdir $BSP_KERNEL_DIST -p
		find $BSP_KERNEL_OUT -name $BSP_DTB.dtb | xargs -i cp {} $BSP_KERNEL_DIST
		find $BSP_KERNEL_OUT -name $BSP_DTBO.dtbo | xargs -i cp {} $BSP_KERNEL_DIST
	fi

	cd $BSP_KERNEL_OUT
	command make -C $BSP_KERNEL_OUT O=$BSP_KERNEL_OUT $BSP_MAKE_EXTRA_ARGS ARCH=$BSP_BOARD_ARCH INSTALL_MOD_PATH=$BSP_KERNEL_DIST modules_install -j$BSP_OBJ
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi

	cd $BSP_ROOT_DIR
	for BSP_KERNEL_BIN in $BSP_KERNEL_FILE_LIST;
	do
		if [[ $BSP_KERNEL_BIN == "vmlinux" ]]; then
			cp -f $BSP_KERNEL_OUT/vmlinux $BSP_KERNEL_DIST
		else
			find $BSP_KERNEL_OUT -name $BSP_KERNEL_BIN | xargs -i cp {} $BSP_KERNEL_DIST
		fi
	done

	failure_handle kernel
}

function dtbo_check()
{
	if [[ -z $BSP_DTBO ]]; then
		return
	fi

	case "$BSP_PLATFORM_VERSION" in
	androidq)
	if [ $BSP_BOARD_ARCH = "arm64" ];then
		$BSP_KERNEL_OUT/scripts/dtc/dtc -M $BSP_KERNEL_OUT/arch/$BSP_BOARD_ARCH/boot/dts/sprd/$BSP_DTB.dtb $BSP_KERNEL_OUT/arch/$BSP_BOARD_ARCH/boot/dts/sprd/$BSP_DTBO.dtbo
		if [[ $? -ne 0 ]]; then
			return_val=1
		fi
		if [ -f "$BSP_KERNEL_OUT/arch/$BSP_BOARD_ARCH/boot/dts/sprd/fdt.dtb" ];then
			$BSP_KERNEL_OUT/scripts/dtc/dtc -I dtb -O dts $BSP_KERNEL_OUT/arch/$BSP_BOARD_ARCH/boot/dts/sprd/fdt.dtb -o $BSP_KERNEL_OUT/arch/$BSP_BOARD_ARCH/boot/dts/sprd/fdt.dts > /dev/null 2>&1

			$BSP_ROOT_DIR/tools/$BSP_PLATFORM_VERSION/mkdtimg/ufdt_verify_overlay_host $BSP_KERNEL_OUT/arch/$BSP_BOARD_ARCH/boot/dts/sprd/fdt.dtb $BSP_KERNEL_OUT/arch/$BSP_BOARD_ARCH/boot/dts/sprd/$BSP_DTBO.dtbo
			if [[ $? -ne 0 ]]; then
				return_val=1
			fi
		fi
	fi

	if [ $BSP_BOARD_ARCH = "arm" ];then
		$BSP_KERNEL_OUT/scripts/dtc/dtc -M $BSP_KERNEL_OUT/arch/$BSP_BOARD_ARCH/boot/dts/$BSP_DTB.dtb $BSP_KERNEL_OUT/arch/$BSP_BOARD_ARCH/boot/dts/$BSP_DTBO.dtbo
		if [[ $? -ne 0 ]]; then
			return_val=1
		fi
		if [ -f "$BSP_KERNEL_OUT/arch/$BSP_BOARD_ARCH/boot/dts/fdt.dtb" ];then
			$BSP_KERNEL_OUT/scripts/dtc/dtc -I dtb -O dts $BSP_KERNEL_OUT/arch/$BSP_BOARD_ARCH/boot/dts/fdt.dtb -o $BSP_KERNEL_OUT/arch/$BSP_BOARD_ARCH/boot/dts/fdt.dts > /dev/null 2>&1

			$BSP_ROOT_DIR/tools/$BSP_PLATFORM_VERSION/mkdtimg/ufdt_verify_overlay_host $BSP_KERNEL_OUT/arch/$BSP_BOARD_ARCH/boot/dts/fdt.dtb $BSP_KERNEL_OUT/arch/$BSP_BOARD_ARCH/boot/dts/$BSP_DTBO.dtbo
			if [[ $? -ne 0 ]]; then
				return_val=1
			fi
		fi
	fi
	;;
	esac
}

function make_dtb()
{
	make_config
	if [[ $? -ne 0 ]]; then
		echo_failure dtb
		return 1
	fi

	echo -e "\033[32m #### start build dtb #### \033[0m"

	if [ -f $BSP_ROOT_DIR/modules/audio/extra_sound_card_component.dtsi ]; then
		echo -e "Linkfile extra_sound_card_component.dtsi from audio to kernel."
		mv $BSP_KERNEL_PATH/arch/arm64/boot/dts/sprd/extra_sound_card_component.dtsi $BSP_KERNEL_PATH/arch/arm64/boot/dts/sprd/extra_sound_card_component.dtsi.backup
		ln -sf $BSP_ROOT_DIR/modules/audio/extra_sound_card_component.dtsi $BSP_KERNEL_PATH/arch/arm64/boot/dts/sprd/extra_sound_card_component.dtsi
	fi

	command make -C $BSP_KERNEL_PATH O=$BSP_KERNEL_OUT $BSP_MAKE_EXTRA_ARGS ARCH=$BSP_BOARD_ARCH CROSS_COMPILE=$BSP_KERNEL_CROSS_COMPILE dtbs -j$BSP_OBJ
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi

	dtbo_check

	if [ -f $BSP_KERNEL_PATH/arch/arm64/boot/dts/sprd/extra_sound_card_component.dtsi.backup ]; then
		echo -e "After compiling dtb done, checkout extra_sound_card_component.dtsi in kernel/common"
		mv $BSP_KERNEL_PATH/arch/arm64/boot/dts/sprd/extra_sound_card_component.dtsi.backup $BSP_KERNEL_PATH/arch/arm64/boot/dts/sprd/extra_sound_card_component.dtsi
	fi

	if [ -n $BSP_KERNEL_DIST ]; then
		mkdir $BSP_KERNEL_DIST -p
		find $BSP_KERNEL_OUT -name $BSP_DTB.dtb | xargs -i cp {} $BSP_KERNEL_DIST
	fi

	cd $BSP_ROOT_DIR

	failure_handle dtb
}

function make_dtbo()
{
	if [[ -z $BSP_DTBO ]]; then
		echo BSP_DTBO is null, skipped.
		return
	fi

	make_config
	if [[ $? -ne 0 ]]; then
		echo_failure dtbo
		return 1
	fi

	echo -e "\033[32m #### start build dtbo #### \033[0m"

	command make -C $BSP_KERNEL_PATH O=$BSP_KERNEL_OUT $BSP_MAKE_EXTRA_ARGS ARCH=$BSP_BOARD_ARCH CROSS_COMPILE=$BSP_KERNEL_CROSS_COMPILE dtbs -j$BSP_OBJ
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi

	dtbo_check

	if [ -n $BSP_KERNEL_DIST ]; then
		mkdir $BSP_KERNEL_DIST -p
		find $BSP_KERNEL_OUT -name $BSP_DTBO.dtbo | xargs -i cp {} $BSP_KERNEL_DIST
	fi

	cd $BSP_ROOT_DIR
	BSP_MKDTIMG=$BSP_ROOT_DIR/tools/$BSP_PLATFORM_VERSION/mkdtimg/mkdtimg

	$BSP_MKDTIMG create $BSP_KERNEL_DIST/dtbo.img $BSP_KERNEL_DIST/$BSP_DTBO.dtbo --id=0
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi

	failure_handle dtbo
}

function make_config()
{
	echo -e "\033[32m #### start build config #### \033[0m"

	unset l_diffconfig_files_used l_config_create_diff

	command make -C $BSP_KERNEL_PATH O=$BSP_KERNEL_OUT $BSP_MAKE_EXTRA_ARGS ARCH=$BSP_BOARD_ARCH CROSS_COMPILE=$BSP_KERNEL_CROSS_COMPILE $BSP_KERNEL_DEFCONFIG -j$BSP_OBJ
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi
	cp $BSP_KERNEL_OUT/.config $BSP_KERNEL_OUT/tmp_defconfig

	add_diffconfig
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi
	cp $BSP_KERNEL_OUT/.config $BSP_KERNEL_PATH/arch/$BSP_BOARD_ARCH/configs/sprd_nrule_defconfig

	command make -C $BSP_KERNEL_PATH O=$BSP_KERNEL_OUT $BSP_MAKE_EXTRA_ARGS ARCH=$BSP_BOARD_ARCH CROSS_COMPILE=$BSP_KERNEL_CROSS_COMPILE sprd_nrule_defconfig -j$BSP_OBJ
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi

	diffconfig_check
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi

	if [ $BSP_PLATFORM_VERSION == "androidq" ]; then
		check_android_base
		if [[ $? -ne 0 ]]; then
			return_val=1
		fi
	fi

	cd $BSP_ROOT_DIR
	failure_handle config
}

function diffconfig_check()
{
	diff_config_base_def $BSP_KERNEL_OUT/tmp_defconfig $BSP_KERNEL_PATH/arch/$BSP_BOARD_ARCH/configs/sprd_nrule_defconfig $BSP_KERNEL_OUT/nrule_diff
	diff_config_base_def $BSP_KERNEL_OUT/tmp_defconfig $BSP_KERNEL_OUT/.config $BSP_KERNEL_OUT/yrule_diff

	tmp_config_create_diff=`diff $BSP_KERNEL_OUT/nrule_diff $BSP_KERNEL_OUT/yrule_diff | awk '$1==">"|| $1 =="<" {print $0}' | awk '$1="";{print $0}' \
					|awk '{if($1=="#") print $2;else print $1}' | awk -F "=" {'print $1'}`

	for config in $tmp_config_create_diff
	do
		if [[ `grep -rw $config "$BSP_KERNEL_PATH/$BSP_KERNEL_DIFF_CONFIG_ARCH"` == "" && `grep -w $config $BSP_KERNEL_OUT/.config` == "" ]];then
			echo "Wrong config"
		elif echo "${l_config_create_diff[@]}" | grep -w "$config" &>/dev/null; then
			echo "Repeated"
		else
			l_config_create_diff=("${l_config_create_diff[@]}" "$config")
		fi
	done

	if [[ $l_config_create_diff != "" ]];then
		echo "ERROR============================================================================================================"
		echo "ERROR: Dependency error, please modify diffconfig to meet the rules."
		for config in ${l_config_create_diff[@]};
		do
			echo "------------------------------------------------------------------------------------------------"
			found_flag=0
			if [[ `grep -w $config $BSP_KERNEL_PATH/arch/$BSP_BOARD_ARCH/configs/sprd_nrule_defconfig` != "" ]];then
				for files in ${l_diffconfig_files_used[@]};
				do
					if [[ -f $BSP_KERNEL_PATH/$files ]];then
						if [[ `grep -w $config $BSP_KERNEL_PATH/$files` != "" && `grep ^#.*$config.* $BSP_KERNEL_PATH/$files` == "" ]];then
							echo -e "diffconfig operation: `grep -w $config $BSP_KERNEL_PATH/$files`"
							found_flag=1
						fi
					fi
				done
				if [[ $found_flag != 1 ]];then
					echo "diffconfig operation: No Operation"
				fi
			else
				echo "diffconfig operation: No Operation"
			fi

			if [[ `grep -w $config $BSP_KERNEL_OUT/.config` != "" ]];then
				if [[ `grep -w $config $BSP_KERNEL_OUT/nrule_diff` != "" ]];then
					echo -e ".config status: `grep -w $config $BSP_KERNEL_OUT/.config` The operation doesn't work."
				else
					echo -e ".config status: `grep -w $config $BSP_KERNEL_OUT/.config` Need check the dependency of diffconfigs."
				fi
			else
				if [[ `grep -w $config $BSP_KERNEL_OUT/nrule_diff` == " # "$config" is not set" ]];then
					echo -e ".config status: $config is not in .config originally. The 'DEL' Operation is extra."
				else
					echo ".config status: Nonexistent. The operation doesn't work."
				fi
			fi
		done
		echo "ERROR============================================================================================================"
		return_val=1
	fi

	rm -rf $BSP_KERNEL_OUT/tmp_defconfig
	rm -rf $BSP_KERNEL_PATH/arch/$BSP_BOARD_ARCH/configs/sprd_nrule_defconfig
	rm -rf $BSP_KERNEL_OUT/nrule_diff $BSP_KERNEL_OUT/yrule_diff
}

function diff_config_base_def()
{
	diff $1 $2 | awk -F ">" {'print $2'} | awk '{if($2~"CONFIG_"||$1 ~"CONFIG_") print $0}' > $3
	sort $3 -o $3
}

function check_android_base()
{
	local BSP_ANDROID_BASE=$BSP_ROOT_DIR/../kernel/configs/q/android-4.14
	local BSP_ANDROID_BASE_CONFIG=$BSP_ANDROID_BASE/android-base.config
	local BSP_ANDROID_BASE_XML=$BSP_ANDROID_BASE/android-base-conditional.xml

	echo "============================================================="

	if [ -f $BSP_ANDROID_BASE_CONFIG ]; then
		echo "Check whether .config meets android-base.config of androidq"

		local l_base_config_off=`cat $BSP_ANDROID_BASE_CONFIG | awk -F " " {'print $2'}|awk '{if($1~/CONFIG/) print}'`
		local l_base_config_on=`cat $BSP_ANDROID_BASE_CONFIG | awk '{if($1~/=/) print}'|awk -F "=" '{print $1}'`

		for config in $l_base_config_on;
		do
			if [[ `grep -w $config $BSP_KERNEL_OUT/.config` == `grep -w $config $BSP_ANDROID_BASE_CONFIG` ]]; then
				continue
			else
				echo -e "ERROR configuration: Should [enable] $config to satisfy requirement of android-base.config"
				return_val=1
			fi
		done

		for config in $l_base_config_off;
		do
			if [[ `grep -w $config $BSP_KERNEL_OUT/.config` == "" ]]; then
				continue
			elif [[ `grep -w $config $BSP_KERNEL_OUT/.config` == `grep -w $config $BSP_ANDROID_BASE_CONFIG` ]]; then
				continue
			else
				echo -e "ERROR configuration: Should [disable] $config to satisfy requirement of android-base.config"
				return_val=1
			fi
		done
		echo "Check android-base.config End"
	fi

	echo "-------------------------------------------------------------"

	if [ -f $BSP_ANDROID_BASE_XML ]; then
		echo "Check whether .config meets android-base-conditional.xml of androidq"

		cd $BSP_ROOT_DIR
		python ./build/check-android-base_xml.py $BSP_KERNEL_OUT $BSP_ANDROID_BASE
		if [[ $? -ne 0 ]]; then
			return_val=1
		fi

		echo "Check android-base-conditional.xml End"
	fi

	echo "============================================================="
}

function make_headers()
{
	echo -e "\033[32m #### start build headers #### \033[0m"

	export BSP_KERNEL_HEADERS_DIR=$BSP_OUT_DIR/$BSP_BOARD_NAME/headers/kernel

	if [ -n $BSP_KERNEL_DIST ]; then
		command make -C $BSP_KERNEL_PATH O=$BSP_KERNEL_OUT ARCH=$BSP_BOARD_ARCH CROSS_COMPILE=$BSP_KERNEL_CROSS_COMPILE \
			$BSP_MAKE_EXTRA_ARGS INSTALL_HDR_PATH="$BSP_KERNEL_HEADERS_DIR/usr" headers_install -j$BSP_OBJ
		if [[ $? -ne 0 ]]; then
			return_val=1
		fi

		find $BSP_KERNEL_HEADERS_DIR \( -name ..install.cmd -o -name .install \) -exec rm '{}' +
		BSP_KERNEL_HEADER_TAR=$BSP_KERNEL_DIST/kernel-uapi-headers.tar.gz
		mkdir $BSP_KERNEL_DIST -p
		tar -czPf $BSP_KERNEL_HEADER_TAR --directory=$BSP_KERNEL_HEADERS_DIR usr/
		tar -xf $BSP_KERNEL_HEADER_TAR -C $BSP_KERNEL_DIST
	fi

	if [[ $? -ne 0 ]]; then
		return_val=1
	fi

	cd $BSP_ROOT_DIR
	failure_handle headers
}

function make_bootimage()
{
	echo -e "\033[32m #### start build bootimage #### \033[0m"

	make_kernel
	if [[ $? -ne 0 ]]; then
		echo_failure bootimage
		return 1
	fi
	signed_images+=" bootimage"

	local BSP_INTERNAL_BOOTIMAGE_ARGS
	local BSP_INTERNAL_KERNEL_CMDLINE

	local BSP_INSTALLED_KERNEL_TARGET="$BSP_KERNEL_DIST/Image"
	local BSP_INSTALLED_DTBIMAGE_TARGET="$BSP_KERNEL_DIST/$BSP_DTB.dtb"

	if [[ ! -f "$BSP_INSTALLED_KERNEL_TARGET" ]]; then
		echo -e "\033[31m $BSP_INSTALLED_KERNEL_TARGET doesn't exist. \033[0m"
		return_val=1
	elif [[ ! -f "$BSP_INSTALLED_DTBIMAGE_TARGET" ]]; then
		echo -e "\033[31m $BSP_INSTALLED_DTBIMAGE_TARGET doesn't exist. \033[0m"
		return_val=1
	elif [[ ! -f "$BSP_INSTALLED_RAMDISK_TARGET" ]]; then
		echo -e "\033[31m $BSP_INSTALLED_RAMDISK_TARGET doesn't exist. \033[0m"
		return_val=1
	fi

	BSP_MKBOOTIMG="$BSP_ROOT_DIR/tools/$BSP_PLATFORM_VERSION/mkbootimg/mkbootimg"

	# -----------------------------------------------------------------
	# the boot image, which is a collection of other images.
	BSP_INTERNAL_BOOTIMAGE_ARGS=$BSP_INTERNAL_BOOTIMAGE_ARGS" --kernel $BSP_INSTALLED_KERNEL_TARGET"

#TODO
#	$(addprefix --second ,$(BSP_INSTALLED_2NDBOOTLOADER_TARGET)) \

	BSP_INTERNAL_MKBOOTIMG_VERSION_ARGS=" --os_version $BSP_PLATFORM_VERSION --os_patch_level $BSP_PLATFORM_SECURITY_PATCH"
	BSP_INTERNAL_KERNEL_CMDLINE="$BSP_BOARD_KERNEL_CMDLINE"
	BSP_INTERNAL_KERNEL_CMDLINE="$BSP_INTERNAL_KERNEL_CMDLINE buildvariant=$BSP_BUILD_VARIANT"

	if [[ -n "$BSP_BOARD_INCLUDE_DTB_IN_BOOTIMG" ]]; then
		BSP_INTERNAL_BOOTIMAGE_ARGS=$BSP_INTERNAL_BOOTIMAGE_ARGS" --dtb $BSP_INSTALLED_DTBIMAGE_TARGET"
	fi

	if [[ -n "$BSP_BOARD_KERNEL_BASE" ]]; then
		BSP_INTERNAL_BOOTIMAGE_ARGS=$BSP_INTERNAL_BOOTIMAGE_ARGS" --base $BSP_BOARD_KERNEL_BASE"
	fi

	if [[ -n "$BSP_BOARD_KERNEL_PAGESIZE" ]]; then
		BSP_INTERNAL_BOOTIMAGE_ARGS=$BSP_INTERNAL_BOOTIMAGE_ARGS" --pagesize $BSP_BOARD_KERNEL_PAGESIZE"
	fi

	if [[ $BSP_BOARD_BUILD_SYSTEM_ROOT_IMAGE != "true" ]]; then
		BSP_INTERNAL_BOOTIMAGE_ARGS=$BSP_INTERNAL_BOOTIMAGE_ARGS" --ramdisk $BSP_INSTALLED_RAMDISK_TARGET"
	fi

#TODO
#	if [[ -n "$BSP_INTERNAL_KERNEL_CMDLINE" ]]; then
#		BSP_INTERNAL_BOOTIMAGE_ARGS=$BSP_INTERNAL_BOOTIMAGE_ARGS" --cmdline \"$BSP_INTERNAL_KERNEL_CMDLINE\""
#	fi

#TODO
#	BSP_INTERNAL_BOOTIMAGE_FILES="$filter-out --%,$BSP_INTERNAL_BOOTIMAGE_ARGS"

	BSP_INSTALLED_BOOTIMAGE_TARGET="$BSP_KERNEL_DIST/boot.img"

	$BSP_MKBOOTIMG $BSP_INTERNAL_BOOTIMAGE_ARGS $BSP_INTERNAL_MKBOOTIMG_VERSION_ARGS $BSP_BOARD_MKBOOTIMG_ARGS --cmdline "$BSP_INTERNAL_KERNEL_CMDLINE" --output $BSP_INSTALLED_BOOTIMAGE_TARGET

	failure_handle bootimage
}

function make_distclean()
{
	echo -e "\033[32m #### start distclean #### \033[0m"

	rm -rf $BSP_OUT_DIR

	failure_handle distclean
}

function make_clean()
{
	echo -e "\033[32m #### start clean #### \033[0m"

	if [[ ! -d $BSP_OUT_DIR ]]; then
		echo "$BSP_OUT_DIR is not exist, skipped."
		failure_handle clean
		return
	fi

	bash build/clean.sh $@
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi

	failure_handle clean
}

function make_mrproper()
{
	echo -e "\033[32m #### start mrproper #### \033[0m"

	cd $BSP_KERNEL_PATH

	command make mrproper -j$BSP_OBJ
	if [[ $? -ne 0 ]]; then
		return_val=1
	fi

	cd $BSP_ROOT_DIR

	failure_handle mrproper
}

function env_clean()
{
	while ((1)); do
		BSP_ENV_LIST=`env | grep BSP | awk -F"=" {'print $1'}`

		if [[ -n "$BSP_ENV_LIST" ]]; then
			for BSP_ENV in $BSP_ENV_LIST;
			do
				unset $BSP_ENV
			done
		else
			break
		fi
	done
}

function make_unset()
{
	echo -e "\033[32m #### Begin clean the environment... #### \033[0m"

	env_clean

	while ((1)); do
		if [[ "$(type -t make)" = "function" ]] ; then
			unset make
		else
			break
		fi
	done

	echo -e "\033[32m #### Clean the environment done. #### \033[0m"
}

function make_help()
{
	echo "
	make                             : Compile all bsp modules
	make all                         : Compile all bsp modules
	make chipram                     : Compile chipram related image and output binary to out directory
	make bootloader                  : Compile uboot related image and output binary to out directory
	make sml                         : Compile sml related image and output binary to out directory
	make teecfg                      : Compile teecfg related image and output binary to out directory
	make trusty                      : Compile tos related image and output binary to out directory
	make config                      : Only compile .config
	make kernel                      : Compile all kernel related image and output binary to out directory
	make dtb                         : Only generate product_name.dtb
	make dtbo                        : Only generate product_name.dtbo
	make headers                     : Install kernel headers into dist
	make unset                       : Delete the BSP related environment variable
	make help                        : Print the usage
	make -h                          : Print the usage
	make modules                     : Compile the internal and external modules
	make modules -m sample.ko        : Compile only one modules
	make clean                       : Clean all bsp obj files
	make clean kernel                : Clean the only one bsp module (chipram / sml / teecfg /  tos / uboot / kernel)
	make clean modules -m sample.ko  : When clean modules, support clean only one module
	make distclean                   : Clean all bsp obj files and output files
	make mrproper                    : Clean the kernel temporary files

	kuconfig                         : Using menuconfig generate .config and replace defconfig
	"""
}

is_packing=0
signed_images="chipram bootloader sml trusty"
function build_tool_and_sign_images()
{
	if [[ $BUILD_FROM_ANDROID == "true" ]]; then
		echo "just do nothing for not independent compile."
		return 0
	fi

	echo "secboot = $BSP_PRODUCT_SECURE_BOOT"
	if [[ "$BSP_PRODUCT_SECURE_BOOT" != "NONE" ]]; then
		if [[ ! -e $BSP_OUT_DIR/PRODUCT_SECURE_BOOT_SPRD ]]; then
			echo "touch PRODUCT_SECURE_BOOT_SPRD"
			touch $BSP_OUT_DIR/PRODUCT_SECURE_BOOT_SPRD
		fi
	fi

	if [[ $is_packing -eq 0 ]]; then
		is_packing=1
		. $BSP_SIGN_DIR/packimage.sh "$@"
		if [[ $? -ne 0 ]]; then
			return_val=1
		fi
		is_packing=0
	fi

	failure_handle sign_images
}

function echo_failure()
{
	echo -e "\033[31m #### build $1 failed #### \033[0m"
}


function failure_handle()
{
	if [[ $? -ne 0 ]]; then
		echo_failure $1
		return 1
	elif [[ $return_val -ne 0 ]]; then
		echo_failure $1
		return 1
	else
		echo -e "\033[32m #### build $1 completed successfully #### \033[0m"
	fi
}
export -f failure_handle

function croot()
{
	cd $BSP_ROOT_DIR
}

function make()
{
	unset parameter

	local OLD_PATH=$OLDPWD

	if [[ $# == 0 ]]; then
		# support: make
		parameter="chipram bootloader sml teecfg trusty kernel modules dtbo"
	elif [[ $# == 1 ]] && [[ `echo $1 | grep "\-j"` ]]; then
		# support: make -j
		parameter="chipram bootloader sml teecfg trusty kernel modules dtbo"
	else
		# support make "parameters" [[-j]]
		local parameter cmd

		while [[ -n "$1" ]]
		do
			case "$1" in
			all)         parameter="$parameter chipram bootloader sml teecfg trusty kernel modules dtbo" ;;
			chipram)     parameter="$parameter chipram"    ;;
			bootloader)  parameter="$parameter bootloader" ;;
			sml)         parameter="$parameter sml"        ;;
			teecfg)      parameter="$parameter teecfg"     ;;
			trusty)      parameter="$parameter trusty"     ;;
			config)      parameter="$parameter config"     ;;
			kernel)      parameter="$parameter kernel"     ;;
			modules)     parameter="$parameter modules"    ;;
			dtb)         parameter="$parameter dtb"        ;;
			dtbo)        parameter="$parameter dtbo"       ;;
			bootimage)   parameter="$parameter bootimage"  ;;
			headers)     parameter="$parameter headers"    ;;
			clean)       parameter="$parameter clean"      ;;
			distclean)   parameter="$parameter distclean"  ;;
			mrproper)    parameter="$parameter mrproper"   ;;
			unset)       parameter="$parameter unset"      ;;
			help)        parameter="$parameter help"       ;;
			-h)          parameter="$parameter help"       ;;
			*)
				# Do nothing when get the -j parameter.
				# In the others report the ERROR.
				if [[ -z `echo $1 | grep "\-j"` ]]; then
					echo -e "\033[31m Paramenter error! Please check. \033[0m"
					return 1
				fi
			;;

			esac
			if [[ -z $parameter ]]; then
				shift
			else
				break
			fi
		done
	fi

	unset return_val

	for cmd in $parameter;
	do
		if ([[ $cmd == "trusty" ]] || [[ $cmd == "sml" ]]) && \
			([[ ! -d "$BSP_ROOT_DIR/trusty/lk/trusty" ]] || \
			[[ ! -d "$BSP_ROOT_DIR/sml/arm-trusted-firmware" ]]); then
			continue
		fi

		make_$cmd $@
		if [[ $? -ne 0 ]]; then
			return 1
		fi

		if [[ `echo "$signed_images" | grep $cmd` ]]; then
			build_tool_and_sign_images "$@"
			if [[ $? -ne 0 ]]; then
				return 1
			fi
		fi

	done

	OLDPWD=$OLD_PATH
}

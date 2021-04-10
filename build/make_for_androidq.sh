export BUILD_FROM_ANDROID="true"
export PLATFORM_VERSION="androidq"

cd $PWD/bsp

BSP_MODULES_LIST="
bspallimage
chipram
bootloader
sml
teecfg
trusty
bootimage
bootimage_debug
dtboimage
recoveryimage
systemimage
sockoimage
odmkoimage
superimage
vendorimage
vbmetaimage
kheader
kuconfig
"

if [[ ${TARGET_PRODUCT:0:4} == "aosp" ]]; then
	exit 0
fi

if [[ $# -eq 0 ]]; then
	source build/envsetup.sh
	lunch $TARGET_PRODUCT-$TARGET_BUILD_VARIANT-$PLATFORM_VERSION

	make all
elif [[ $# == 1 ]] && [[ `echo $1 | grep "\-j"` ]]; then
	# support: make -j
	source build/envsetup.sh
	lunch $TARGET_PRODUCT-$TARGET_BUILD_VARIANT-$PLATFORM_VERSION

	make all
elif [[ $# == 2 ]] && [[ `echo $1 | grep "KALLSYMS_EXTRA_PASS"` ]]; then
	# support: make KALLSYMS_EXTRA_PASS
	source build/envsetup.sh
	lunch $TARGET_PRODUCT-$TARGET_BUILD_VARIANT-$PLATFORM_VERSION

	make all
else
	if !(echo -n $BSP_MODULES_LIST | grep -w $1 > /dev/null); then
		exit 0
	fi

	source build/envsetup.sh
	lunch $TARGET_PRODUCT-$TARGET_BUILD_VARIANT-$PLATFORM_VERSION

	if [[ $? -ne 0 ]]; then
		exit 1
	fi

	COMPILE_COMMAND=$1
	shift

	case $COMPILE_COMMAND in
	"chipram")        	make chipram    $@;;
	"bootloader")     	make bootloader $@;;
	"sml")            	make sml        $@;;
	"teecfg")           make teecfg     $@;;
	"trusty")         	make trusty     $@;;
	"bootimage")      	make kernel     $@;;
	"bootimage_debug") 	make kernel     $@;;
	"dtboimage")      	make dtbo       $@;;
	"recoveryimage")  	make kernel	    $@
						make dtbo       $@
	;;
	"sockoimage")     	make modules    $@;;
	"odmkoimage")     	make modules    $@;;
	"vendorimage")     	make headers    $@;;
	"superimage")       make all        $@;;
	"systemimage")    	make all        $@;;
	"bspallimage")    	make all        $@;;
	"vbmetaimage")    	make all        $@;;
	"kheader")	    	make headers    $@;;
	"kuconfig")	    	kuconfig        $@;;
	*) ;;
	esac
fi

failure_handle $1

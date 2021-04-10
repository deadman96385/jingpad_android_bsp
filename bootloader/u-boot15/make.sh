if [ "$1" = "bsp" ]
then
	make -f BspUBoot.mk
	exit
fi

if [ "$1" = "" ] || [ "$2" = "" ]
then
	echo "Pleast input command : make 'arch_name' 'board_name'"
	echo "for examle: make x86 iwhale2"
	exit
fi

export KBUILD_OUTPUT=./out
export UBOOT_DEBUG_FLAG=-DDEBUG

if [ "$1" = "arm" ];then
	export PATH=$PATH:$(pwd)/../prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin
	export CROSS_COMPILE=arm-eabi-
	make distclean
	make ARCH=arm "$2"_defconfig
	make ARCH=arm DEVICE_TREE="$3" -j4

elif [ "$1" = "arm64" ]; then
	export PATH=$PATH:$(pwd)/../prebuilts/gcc/linaro-x86/aarch64/gcc-linaro-4.8/gcc-linaro-4.8-2015.06-x86_64_aarch64-linux-gnu/bin
	export CROSS_COMPILE=aarch64-linux-gnu-
	make distclean
	make ARCH=arm "$2"_defconfig
	make ARCH=arm DEVICE_TREE="$3" -j4

elif [ "$1" = "x86" ]; then
	export PATH=$PATH:$(pwd)/../prebuilts/gcc/linux-x86/x86/x86_64-linux-android-4.9/bin
	export make CROSS_COMPILE=x86_64-linux-android-
	make distclean
	make ARCH=x86 "$2"_defconfig
	make ARCH=x86 DEVICE_TREE="$3" -j4
else
	echo "not suppported arch"
fi


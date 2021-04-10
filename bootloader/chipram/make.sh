if [ "$1" = "bsp" ]
then
	make -f BspChipram.mk
	exit
fi

if [ "$1" = "" ] || [ "$2" = "" ]
then
	echo "Pleast input command : make 'arch_name' 'board_name'"
	echo "for examle: ./make.sh armv7 sp7731e_1h10"
	exit
fi

export BUILD_DIR=./out
if [ "$1" = "armv7" ];then
	export PATH=$PATH:$(pwd)/../../toolchain/prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin
	export make ARM_EABI_TOOLCHAIN=$(pwd)/../prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin
	export make CROSS_COMPILE=arm-eabi-
	make distclean
	make "$2"_config
	make -j

elif [ "$1" = "armv8" ]; then
	export PATH=$PATH:$(pwd)/../prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin
	export make ARM_EABI_TOOLCHAIN=$(pwd)/../prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin
	export make CROSS_COMPILE=aarch64-linux-android-
	make distclean
	make "$2"_config
	make -j

elif [ "$1" = "x86" ]; then
	export PATH=$PATH:$(pwd)/../prebuilts/gcc/linux-x86/x86/x86_64-linux-android-4.9/bin
	export make CROSS_COMPILE=x86_64-linux-android-
	make distclean
	make ARCH=x86 "$2"_config
	make ARCH=x86 -j4
else
	echo "not suppported arch"
fi

./imgheaderinsert ./out/ddr_scan/ddr_scan.bin 1
./imgheaderinsert ./out/nand_fdl/fdl1.bin 1
./imgheaderinsert ./out/nand_spl/u-boot-spl-16k.bin 1


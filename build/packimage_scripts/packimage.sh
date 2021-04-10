#!/bin/sh
#sign tools config
SECURE_BOOT=$BSP_PRODUCT_SECURE_BOOT
echo "SECURE_BOOT is $SECURE_BOOT"
HOST_OUT=$BSP_SIGN_DIR
PRODUCT_OUT=$BSP_OUT_DIR
CFGPATH=$BSP_SIGN_DIR/config
DESTDIR=$BSP_SIGN_DIR/mkdbimg/bin

#chipram bins location
SPL=$BSP_CHIPRAM_DIST/u-boot-spl-16k.bin
SPLSIGN=$BSP_CHIPRAM_DIST/u-boot-spl-16k-sign.bin
FDL1=$BSP_CHIPRAM_DIST/fdl1.bin
FDL1SIGN=$BSP_CHIPRAM_DIST/fdl1-sign.bin
DDR_SCAN=$BSP_CHIPRAM_DIST/ddr_scan.bin
DDR_SCANSIGN=$BSP_CHIPRAM_DIST/ddr_scan-sign.bin

#sml bins location
SML=$BSP_SML_DIST/sml.bin
SMLSIGN=$BSP_SML_DIST/sml-sign.bin

#teecfg bins location
TEECFG=$BSP_TEECFG_DIST/teecfg.bin
TEECFGSIGN=$BSP_TEECFG_DIST/teecfg-sign.bin

#tos bins location
TOS=$BSP_TOS_DIST/tos.bin
TOSSIGN=$BSP_TOS_DIST/tos-sign.bin
TA_DESTDIR=$BSP_SIGN_DIR

#uboot bins location
UBOOTDT=$BSP_UBOOT_DIST/u-boot-dtb.bin
UBOOTDTSIGN=$BSP_UBOOT_DIST/u-boot-dtb-sign.bin
UBOOT=$BSP_UBOOT_DIST/u-boot.bin
UBOOTSIGN=$BSP_UBOOT_DIST/u-boot-sign.bin
FDL2=$BSP_UBOOT_DIST/fdl2.bin
FDL2SIGN=$BSP_UBOOT_DIST/fdl2-sign.bin
UBOOTAUTO=$BSP_UBOOT_DIST/u-boot_autopoweron.bin
UBOOTAUTOSIGN=$BSP_UBOOT_DIST/u-boot_autopoweron-sign.bin

VBMETA=$PRODUCT_OUT/vbmeta.img

getModuleName()
{
    local name="allmodules"
    if [ $# -gt 0 ]; then
        for loop in $@
        do
            case $loop in
            "chipram")
            name="chipram"
            break
            ;;
            "bootloader")
            name="bootloader"
            break
            ;;
            "bootimage")
            name="bootimage"
            break
            ;;
            "recoveryimage")
            name="recoveryimage"
            break
            ;;
            "prodnvimage")
            name="prodnvimage"
            break
            ;;
            "systemimage")
            name="systemimage"
            break
            ;;
            "vendorimage")
            name="vendorimage"
            break
            ;;
            "userdataimage")
            name="userdataimage"
            break
            ;;
            "cacheimage")
            name="cacheimage"
            break
            ;;
            "trusty")
            name="trusty"
            break
	        ;;
            "teecfg")
            name="teecfg"
            break
            ;;
            "sml")
            name="sml"
            break
            ;;
            "vbmetaimage")
            name="vbmetaimage"
            break
            ;;
            "vbmetaimage-nodeps")
            name="vbmetaimage"
            break
            ;;
            "clean")
            name="clean"
            break
            ;;
            *)
            ;;
            esac
        done
    fi
    echo $name
}

doImgHeaderInsert()
{
    local NO_SECURE_BOOT
    local remove_orig_file_if_succeed=0
    local ret

    if [ "NONE" = $SECURE_BOOT ]; then
        NO_SECURE_BOOT=1
    else
        NO_SECURE_BOOT=0
    fi

    for loop in $@
    do
        if [ -f $loop ] ; then
            $HOST_OUT/imgheaderinsert $loop $NO_SECURE_BOOT $remove_orig_file_if_succeed
            ret=$?
            if [ "$ret" = "1" ]; then
                 echo "####imgheaderinsert $loop NO_SECURE_BOOT=$NO_SECURE_BOOT remove_orig_file_if_succeed=$remove_orig_file_if_succeed failed!####"
                 return 1
            fi
        else
            echo "#### no $loop,please check ####"
        fi
    done
    return 0
}

dosprdcopy()
{
    if [ -f $SPLSIGN ];then
        cp $SPLSIGN $DESTDIR
        #echo -e "\033[33m copy spl-sign.bin finish!\033[0m"
    fi

    if [ -f $FDL1SIGN ]; then
        cp $FDL1SIGN $DESTDIR
        #echo -e "\033[33m copy fdl1-sign.bin finish!\033[0m"
    fi
}

doSignImage()
{
    if [ "NONE" = $SECURE_BOOT ]; then
        return
    fi
    #/*add sprd sign*/
    if [ "SPRD" = $SECURE_BOOT ]; then
        for image in $@
        do
            if [ -f $image ]; then
                echo "BSP_PKCS1_PSS_FLAG is $BSP_PKCS1_PSS_FLAG"
                if [[ "true" = $BSP_PKCS1_PSS_FLAG ]]; then
                    $HOST_OUT/sprd_sign  $image  $CFGPATH  pss
                else
                    $HOST_OUT/sprd_sign  $image  $CFGPATH  pkcs15
                fi
            else
                echo -e "\033[31m ####  no $image, pls check #### \033[0m"
            fi
        done
        #call this function do copy fdl1&spl to mkdbimg/bin document
#        dosprdcopy
    fi
}

doPackImage()
{
    case $(getModuleName "$@") in
        "chipram")
            doImgHeaderInsert $SPL $FDL1 $DDR_SCAN
            if [ "$?" = "1" ]; then
               return 1
            fi
            doSignImage $SPLSIGN $FDL1SIGN $DDR_SCANSIGN
            ;;
        "bootloader")
            doImgHeaderInsert $UBOOT $FDL2 $UBOOTAUTO
            if [ "$?" = "1" ]; then
               return 1
            fi
            doSignImage $UBOOTSIGN $FDL2SIGN $UBOOTAUTOSIGN
            ;;
        "trusty")
            #the next line is for dynamic TA
            python $TA_DESTDIR/dynamicTA/genkey/main_process.py $BSP_TOS_DIST $TA_DESTDIR
            doImgHeaderInsert $TOS
            if [ "$?" = "1" ]; then
               return 1
            fi
            doSignImage $TOSSIGN
            ;;
        "teecfg")
                doImgHeaderInsert $TEECFG
                if [ "$?" = "1" ]; then
                   return 1
                fi
                doSignImage $TEECFGSIGN
	    ;;
        "sml")
            doImgHeaderInsert $SML
            if [ "$?" = "1" ]; then
               return 1
            fi
            doSignImage $SMLSIGN
            ;;
        "allmodules")
            if [ "NONE" = $SECURE_BOOT ]; then
                #the next line is for dynamic TA
                python $TA_DESTDIR/dynamicTA/genkey/main_process.py $BSP_TOS_DIST $TA_DESTDIR
                doImgHeaderInsert $SPL $UBOOT $FDL1 $FDL2 $UBOOTAUTO $SML $TEECFG $TOS $DDR_SCANSIGN
            else
                #the next line is for dynamic TA
                python $TA_DESTDIR/dynamicTA/genkey/main_process.py $BSP_TOS_DIST $TA_DESTDIR
                doImgHeaderInsert $SPL $UBOOT $FDL1 $FDL2 $UBOOTAUTO $SML $TEECFG $TOS $DDR_SCAN
                if [ "$?" = "1" ]; then
                   return 1
                fi
                doSignImage $SPLSIGN $UBOOTSIGN $FDL1SIGN $FDL2SIGN $SMLSIGN $TEECFGSIGN $TOSSIGN $UBOOTAUTOSIGN $DDR_SCANSIGN
                #$HOST_OUT/imgheaderinsert $VBMETA 1 1
            fi
            ;;
        "vbmetaimage")
            $HOST_OUT/imgheaderinsert $VBMETA 1 1
            ;;
        "clean")
            #do nothing
            ;;
        *)
            ;;
    esac
}

doPackImage "$@"


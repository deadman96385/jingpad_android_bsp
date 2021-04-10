#!/bin/bash
ROOTDIR=$(pwd)

if [ "$1" = "" ]
	then echo -e "\033[31m please input debug mask val such as 0xffffffff  eg.\033[0m"
	    exit
fi
MASK=$1
KEY_PATH=$ROOTDIR/../../config
BIN_DIR=$ROOTDIR/../bin
PSS_FLAG=$(get_build_var BSP_PKCS1_PSS_FLAG)

doSprdmkprimarycert()
{
  if [ "true" = $PSS_FLAG ]; then
    PSS_FLAG=pss
  else
    PSS_FLAG=pkcs15
  fi
  echo "use $PSS_FLAG flag"

  $BIN_DIR/mkprimarycert $MASK $KEY_PATH $PSS_FLAG
}

doSprdmkprimarycert

if [ -f primary_debug.cert ] ;
	then mv primary_debug.cert $ROOTDIR/../../mkdbimg/bin
		echo -e "\033[32m create primary_debug.cert sucessfull! \033[0m"
fi

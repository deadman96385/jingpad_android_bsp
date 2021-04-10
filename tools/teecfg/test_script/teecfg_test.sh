#!/bin/bash

####################初始化project相关变量####################
project_path=
project_name=
soc_name=
board_name=
product_name=
android_platform_name=

SOC_NAMES="9863a 7731e 9832e ums512"
ANDROID_PLATFORM_NAMES="androidq"

usage()
{
	echo "usage: bash $0 -p <project_path> -n <project_name>"
	echo "eg. bash $0 -p ~/works/sprdroidq_trunk/bsp -n s9863a1h10_Natv-userdebug-androidq"
}

if [[ $# == 4 ]]
then
	while getopts "p:n:" arg
	do
		case $arg in
			p)
				project_path=${OPTARG}
				;;
			n)
				project_name=${OPTARG}
				;;
			?)
				usage
				exit 1
				;;
		esac
	done
else
	usage
	exit 1
fi

get_sharkl3_board_name()
{
	local board_names=
	local name=

	name=$(echo $1 | grep "1h10_go_32b")
	if [[ ${name} != "" ]]
	then
		echo "s9863a1h10_go_32b"
	else
		board_names=(${1//\_/ })
		echo ${board_names[0]}
	fi
}

set_dir_names()
{
	local soc_names=(${SOC_NAMES})
	local name=

	local i=0
	while [[ $i -lt ${#soc_names[@]} ]]
	do
		name=$(echo $1 | grep ${soc_names[$i]})
		if [[ ${name} != "" ]]
		then
			case ${soc_names[$i]} in
				9863a)
					soc_name="sharkl3"
					board_name=$(get_sharkl3_board_name $1)
					product_name=$1
					return 0
					;;
				7731e)
					soc_name="pike2"
					return 0
					;;
				9832e)
					soc_name="sharkle"
					return 0
					;;
				ums512)
					soc_name="sharkl5Pro"
					return 0
					;;
			esac
		fi

		let i++
	done
}

set_android_platform_name()
{
	local android_platform_names=(${ANDROID_PLATFORM_NAMES})
	local name=

	local i=0
	while [[ $i -lt ${#android_platform_names[@]} ]]
	do
		name=$(echo $1 | grep ${android_platform_names[$i]})
		if [[ ${name} != "" ]]
		then
			android_platform_name=${android_platform_names[$i]}
		fi

		let i++
	done
}

init_global_vars()
{
	project_infos=(${project_name//\-/ })

	for info in ${project_infos[@]}
	do
		set_dir_names ${info}
		set_android_platform_name ${info}
	done
}

init_global_vars

echo "==========infos=========="
echo "project_path:"${project_path}
echo "project_name:"${project_name}
echo "soc:"${soc_name}
echo "board:"${board_name}
echo "product:"${product_name}
echo "android_platform:"${android_platform_name}


####################测试cases####################
TEST_CASE_SUCCESS="测试例\033[32msuccess\033[0m"
TEST_CASE_FAIL="测试例\033[31mfail\033[0m"
SEARCH_KEY_WORDS="build teecfg failed"

#==========数据设置超限测试cases==========#
DATA_LIMIT_CASE0_STRING="data_limit_case0:xml文件配置正确，编译teecfg image成功"
DATA_LIMIT_CASE1_STRING="data_limit_case1:设置ATTR_TYPE_UINT8类型的数据超过其上限值，编译teecfg image失败"
DATA_LIMIT_CASE2_STRING="data_limit_case2:设置ATTR_TYPE_UINT8类型的数据超过其下限值，编译teecfg image失败"
DATA_LIMIT_CASE3_STRING="data_limit_case3:设置ATTR_TYPE_UINT16类型的数据超过其上限值，编译teecfg image失败"
DATA_LIMIT_CASE4_STRING="data_limit_case4:设置ATTR_TYPE_UINT16类型的数据超过其下限值，编译teecfg image失败"
DATA_LIMIT_CASE5_STRING="data_limit_case5:设置ATTR_TYPE_UINT32类型的数据超过其上限值，编译teecfg image失败"
DATA_LIMIT_CASE6_STRING="data_limit_case6:设置ATTR_TYPE_UINT32类型的数据超过其下限值，编译teecfg image失败"
DATA_LIMIT_CASE7_STRING="data_limit_case7:设置ATTR_TYPE_UINT64类型的数据超过其上限值，编译teecfg image失败"
DATA_LIMIT_CASE8_STRING="data_limit_case8:设置ATTR_TYPE_UINT64类型的数据超过其下限值，编译teecfg image失败"
DATA_LIMIT_CASE9_STRING="data_limit_case9:设置ATTR_TYPE_BOOL类型的数据为非true/false字符串，编译teecfg image失败"
DATA_LIMIT_CASE10_STRING="data_limit_case10:设置ATTR_TYPE_STRING类型的数据超过其最大长度限制，编译teecfg image失败"

DATA_LIMIT_CASE1_XML_FILE="test_attr_type_uint8_upper_limit.xml"
DATA_LIMIT_CASE2_XML_FILE="test_attr_type_uint8_lower_limit.xml"
DATA_LIMIT_CASE3_XML_FILE="test_attr_type_uint16_upper_limit.xml"
DATA_LIMIT_CASE4_XML_FILE="test_attr_type_uint16_lower_limit.xml"
DATA_LIMIT_CASE5_XML_FILE="test_attr_type_uint32_upper_limit.xml"
DATA_LIMIT_CASE6_XML_FILE="test_attr_type_uint32_lower_limit.xml"
DATA_LIMIT_CASE7_XML_FILE="test_attr_type_uint64_upper_limit.xml"
DATA_LIMIT_CASE8_XML_FILE="test_attr_type_uint64_lower_limit.xml"
DATA_LIMIT_CASE9_XML_FILE="test_attr_type_bool.xml"
DATA_LIMIT_CASE10_XML_FILE="test_attr_type_string_exceed_max_length.xml"

#==========xml文件overlay测试cases==========#
XML_OVERLAY_CASE0_STRING="xml_overlay_case0:测试board级xml文件overlay功能-overlay one item，数据overlay正确，编译teecfg image成功"
XML_OVERLAY_CASE1_STRING="xml_overlay_case1:测试board级xml文件overlay功能-overlay more items，数据overlay正确，编译teecfg image成功"
XML_OVERLAY_CASE2_STRING="xml_overlay_case2:测试board级xml文件overlay功能-add new property，数据overlay正确，编译teecfg image成功"
XML_OVERLAY_CASE3_STRING="xml_overlay_case3:测试product级xml文件overlay功能-overlay one item，数据overlay正确，编译teecfg image成功"
XML_OVERLAY_CASE4_STRING="xml_overlay_case4:测试product级xml文件overlay功能-overlay more items，数据overlay正确，编译teecfg image成功"
XML_OVERLAY_CASE5_STRING="xml_overlay_case5:测试product级xml文件overlay功能-add new property，数据overlay正确，编译teecfg image成功"
XML_OVERLAY_CASE6_STRING="xml_overlay_case6:测试board&product两级xml文件overlay功能，数据overlay正确，编译teecfg image成功"

XML_OVERLAY_CASE0_XML_FILE="test_xml_overlay_board_overlay_one_item.xml"
XML_OVERLAY_CASE1_XML_FILE="test_xml_overlay_board_overlay_more_items.xml"
XML_OVERLAY_CASE2_XML_FILE="test_xml_overlay_board_overlay_add_new_property.xml"
XML_OVERLAY_CASE3_XML_FILE="test_xml_overlay_product_overlay_one_item.xml"
XML_OVERLAY_CASE4_XML_FILE="test_xml_overlay_product_overlay_more_items.xml"
XML_OVERLAY_CASE5_XML_FILE="test_xml_overlay_product_overlay_add_new_property.xml"
XML_OVERLAY_CASE6_XML_FILE="test_xml_overlay_board_product_overlay.xml"

teecfg_test_path=${project_path}/teecfg_test_xml
teecfg_test_data_limit_path=${teecfg_test_path}/data_limit
teecfg_test_xml_overlay_original_path=${teecfg_test_path}/overlay/original
teecfg_test_xml_overlay_board_path=${teecfg_test_path}/overlay/overlay/board
teecfg_test_xml_overlay_product_path=${teecfg_test_path}/overlay/overlay/product
teecfg_soc_path=${project_path}/device/${soc_name}/${android_platform_name}/common/teecfg
teecfg_board_path=${project_path}/device/${soc_name}/${android_platform_name}/${board_name}/${board_name}_base/teecfg
teecfg_product_path=${project_path}/device/${soc_name}/${android_platform_name}/${board_name}/${product_name}/teecfg
teecfg_output_path=${project_path}/out/${board_name}/obj/teecfg/xml
teecfg_board_path_exit=
teecfg_product_path_exit=
expect_ret=
make_ret=
test_ret=
begin_property_id=
end_property_id=
item_names=

config_test_environment()
{
	#拷贝待测试的xml文件
	case $1 in
		soc)
			$(cp ${teecfg_test_data_limit_path}/$2 ${teecfg_soc_path})
			;;
		board)
			if [[ ! -d ${teecfg_board_path} ]]
			then
				teecfg_board_path_exit=false
				mkdir ${teecfg_board_path}
			fi

			$(cp ${teecfg_test_xml_overlay_original_path}/$2 ${teecfg_soc_path})
			$(cp ${teecfg_test_xml_overlay_board_path}/$2 ${teecfg_board_path})
			;;
		product)
			if [[ ! -d ${teecfg_product_path} ]]
			then
				teecfg_product_path_exit=false
				mkdir ${teecfg_product_path}
			fi

			$(cp ${teecfg_test_xml_overlay_original_path}/$2 ${teecfg_soc_path})
			$(cp ${teecfg_test_xml_overlay_product_path}/$2 ${teecfg_product_path})
			;;
		all)
			if [[ ! -d ${teecfg_board_path} ]]
			then
				teecfg_board_path_exit=false
				mkdir ${teecfg_board_path}
			fi

			if [[ ! -d ${teecfg_product_path} ]]
			then
				teecfg_product_path_exit=false
				mkdir ${teecfg_product_path}
			fi

			$(cp ${teecfg_test_xml_overlay_original_path}/$2 ${teecfg_soc_path})
			$(cp ${teecfg_test_xml_overlay_board_path}/$2 ${teecfg_board_path})
			$(cp ${teecfg_test_xml_overlay_product_path}/$2 ${teecfg_product_path})
			;;
	esac

	#设置期望的测试结果
	expect_ret=$3
}

clear_test_environment()
{
	#清除测试用的xml文件
	case $1 in
		soc)
			$(rm -rf ${teecfg_soc_path}/$2)
			;;
		board)
			$(rm -rf ${teecfg_soc_path}/$2)

			if [[ ${teecfg_board_path_exit} == false ]]
			then
				$(rm -rf ${teecfg_board_path})
			else
				$(rm -rf ${teecfg_board_path}/$2)
			fi
			;;
		product)
			$(rm -rf ${teecfg_soc_path}/$2)

			if [[ ${teecfg_product_path_exit} == false ]]
			then
				$(rm -rf ${teecfg_product_path})
			else
				$(rm -rf ${teecfg_product_path}/$2)
			fi
			;;
		all)
			$(rm -rf ${teecfg_soc_path}/$2)

			if [[ ${teecfg_board_path_exit} == false ]]
			then
				$(rm -rf ${teecfg_board_path})
			else
				$(rm -rf ${teecfg_board_path}/$2)
			fi

			if [[ ${teecfg_product_path_exit} == false ]]
			then
				$(rm -rf ${teecfg_product_path})
			else
				$(rm -rf ${teecfg_product_path}/$2)
			fi
			;;
	esac

	teecfg_board_path_exit=
	teecfg_product_path_exit=
	expect_ret=
	make_ret=
	test_ret=
	begin_property_id=
	end_property_id=
	item_names=
}

test_result_check_and_print()
{
	if [[ ${expect_ret} == "" ]]
	then
		if [[ ${test_ret} == "" ]]
		then
			if [[ $2 != "" ]]
			then
				case $2 in
					true)
						echo -e $1 --- ${TEST_CASE_SUCCESS}
						;;
					false)
						echo -e $1 --- ${TEST_CASE_FAIL}
						;;
				esac
			else
				echo -e $1 --- ${TEST_CASE_SUCCESS}
			fi
		else
			echo -e $1 --- ${TEST_CASE_FAIL}
		fi
	else
		if [[ ${test_ret} != "" ]]
		then
			echo -e $1 --- ${TEST_CASE_SUCCESS}
		else
			echo -e $1 --- ${TEST_CASE_FAIL}
		fi
	fi
}

compare_xml_overlay_data()
{
	local overlay_path=
	case $1 in
		board)
			overlay_path=${teecfg_board_path}
			;;
		product)
			overlay_path=${teecfg_product_path}
			;;
	esac

	local items=($5)
	local overlay_item=
	local output_item=
	local item_count=${#items[@]}
	local match_count=0

	local i=0
	while [[ $i -lt ${#items[@]} ]]
	do
		overlay_item=$(sed -n '/'"$3"'/,/'"$4"'/p' ${overlay_path}/$2 | grep -w ${items[$i]} | sed 's/^[ \t]*//g')
		output_item=$(sed -n '/'"$3"'/,/'"$4"'/p' ${teecfg_output_path}/$2 | grep -w ${items[$i]} | sed 's/^[ \t]*//g')

		if [[ "${overlay_item}" == "${output_item}" ]]
		then
			let match_count++
		fi

		let i++
	done

	if [[ ${match_count} == ${item_count} ]]
	then
		echo "true"
	else
		echo "false"
	fi
}

check_rets()
{

	if [[ $1 == "true" && $2 == "true" ]]
	then
		echo "true"
	else
		echo "false"
	fi
}

set_search_params()
{
	begin_property_id="$1"
	end_property_id="$2"
	item_names="$3"
}


####################开始测试####################
echo "==========数据设置超限测试=========="
#==========数据设置超限测试cases==========#
###data_limit_case0:xml文件配置正确，编译teecfg image成功###
#配置测试环境
config_test_environment "" "" ""

#开始测试
make_ret=$(. ${project_path}/build/envsetup.sh; \
	   lunch ${project_name}; \
	   make teecfg -j16)

#检查测试结果
test_ret=$(echo ${make_ret} | grep "${SEARCH_KEY_WORDS}")
test_result_check_and_print "${DATA_LIMIT_CASE0_STRING}" ""

#清除测试环境
clear_test_environment "" ""


###data_limit_case1:设置ATTR_TYPE_UINT8类型的数据超过其上限值，编译teecfg image失败###
#配置测试环境
config_test_environment "soc" "${DATA_LIMIT_CASE1_XML_FILE}" "${SEARCH_KEY_WORDS}"

#开始测试
make_ret=$(. ${project_path}/build/envsetup.sh; \
	   lunch ${project_name}; \
	   make teecfg -j16)

#检查测试结果
test_ret=$(echo ${make_ret} | grep "${SEARCH_KEY_WORDS}")
test_result_check_and_print "${DATA_LIMIT_CASE1_STRING}" ""

#清除测试环境
clear_test_environment "soc" "${DATA_LIMIT_CASE1_XML_FILE}"


###data_limit_case2:设置ATTR_TYPE_UINT8类型的数据超过其下限值，编译teecfg image失败###
#配置测试环境
config_test_environment "soc" "${DATA_LIMIT_CASE2_XML_FILE}" "${SEARCH_KEY_WORDS}"

#开始测试
make_ret=$(. ${project_path}/build/envsetup.sh; \
	   lunch ${project_name}; \
	   make teecfg -j16)

#检查测试结果
test_ret=$(echo ${make_ret} | grep "${SEARCH_KEY_WORDS}")
test_result_check_and_print "${DATA_LIMIT_CASE2_STRING}" ""

#清除测试环境
clear_test_environment "soc" "${DATA_LIMIT_CASE2_XML_FILE}"


###data_limit_case3:设置ATTR_TYPE_UINT16类型的数据超过其上限值，编译teecfg image失败###
#配置测试环境
config_test_environment "soc" "${DATA_LIMIT_CASE3_XML_FILE}" "${SEARCH_KEY_WORDS}"

#开始测试
make_ret=$(. ${project_path}/build/envsetup.sh; \
	   lunch ${project_name}; \
	   make teecfg -j16)

#检查测试结果
test_ret=$(echo ${make_ret} | grep "${SEARCH_KEY_WORDS}")
test_result_check_and_print "${DATA_LIMIT_CASE3_STRING}" ""

#清除测试环境
clear_test_environment "soc" "${DATA_LIMIT_CASE3_XML_FILE}"


###data_limit_case4:设置ATTR_TYPE_UINT16类型的数据超过其下限值，编译teecfg image失败###
#配置测试环境
config_test_environment "soc" "${DATA_LIMIT_CASE4_XML_FILE}" "${SEARCH_KEY_WORDS}"

#开始测试
make_ret=$(. ${project_path}/build/envsetup.sh; \
	   lunch ${project_name}; \
	   make teecfg -j16)

#检查测试结果
test_ret=$(echo ${make_ret} | grep "${SEARCH_KEY_WORDS}")
test_result_check_and_print "${DATA_LIMIT_CASE4_STRING}" ""

#清除测试环境
clear_test_environment "soc" "${DATA_LIMIT_CASE4_XML_FILE}"


###data_limit_case5:设置ATTR_TYPE_UINT32类型的数据超过其上限值，编译teecfg image失败###
#配置测试环境
config_test_environment "soc" "${DATA_LIMIT_CASE5_XML_FILE}" "${SEARCH_KEY_WORDS}"

#开始测试
make_ret=$(. ${project_path}/build/envsetup.sh; \
	   lunch ${project_name}; \
	   make teecfg -j16)

#检查测试结果
test_ret=$(echo ${make_ret} | grep "${SEARCH_KEY_WORDS}")
test_result_check_and_print "${DATA_LIMIT_CASE5_STRING}" ""

#清除测试环境
clear_test_environment "soc" "${DATA_LIMIT_CASE5_XML_FILE}"


###data_limit_case6:设置ATTR_TYPE_UINT32类型的数据超过其下限值，编译teecfg image失败###
#配置测试环境
config_test_environment "soc" "${DATA_LIMIT_CASE6_XML_FILE}" "${SEARCH_KEY_WORDS}"

#开始测试
make_ret=$(. ${project_path}/build/envsetup.sh; \
	   lunch ${project_name}; \
	   make teecfg -j16)

#检查测试结果
test_ret=$(echo ${make_ret} | grep "${SEARCH_KEY_WORDS}")
test_result_check_and_print "${DATA_LIMIT_CASE6_STRING}" ""

#清除测试环境
clear_test_environment "soc" "${DATA_LIMIT_CASE6_XML_FILE}"


###data_limit_case7:设置ATTR_TYPE_UINT64类型的数据超过其上限值，编译teecfg image失败###
#配置测试环境
config_test_environment "soc" "${DATA_LIMIT_CASE7_XML_FILE}" "${SEARCH_KEY_WORDS}"

#开始测试
make_ret=$(. ${project_path}/build/envsetup.sh; \
	   lunch ${project_name}; \
	   make teecfg -j16)

#检查测试结果
test_ret=$(echo ${make_ret} | grep "${SEARCH_KEY_WORDS}")
test_result_check_and_print "${DATA_LIMIT_CASE7_STRING}" ""

#清除测试环境
clear_test_environment "soc" "${DATA_LIMIT_CASE7_XML_FILE}"


###data_limit_case8:设置ATTR_TYPE_UINT64类型的数据超过其下限值，编译teecfg image失败###
#配置测试环境
config_test_environment "soc" "${DATA_LIMIT_CASE8_XML_FILE}" "${SEARCH_KEY_WORDS}"

#开始测试
make_ret=$(. ${project_path}/build/envsetup.sh; \
	   lunch ${project_name}; \
	   make teecfg -j16)

#检查测试结果
test_ret=$(echo ${make_ret} | grep "${SEARCH_KEY_WORDS}")
test_result_check_and_print "${DATA_LIMIT_CASE8_STRING}" ""

#清除测试环境
clear_test_environment "soc" "${DATA_LIMIT_CASE8_XML_FILE}"


###data_limit_case9:设置ATTR_TYPE_BOOL类型的数据为非true/false字符串，编译teecfg image失败###
#配置测试环境
config_test_environment "soc" "${DATA_LIMIT_CASE9_XML_FILE}" "${SEARCH_KEY_WORDS}"

#开始测试
make_ret=$(. ${project_path}/build/envsetup.sh; \
	   lunch ${project_name}; \
	   make teecfg -j16)

#检查测试结果
test_ret=$(echo ${make_ret} | grep "${SEARCH_KEY_WORDS}")
test_result_check_and_print "${DATA_LIMIT_CASE9_STRING}" ""

#清除测试环境
clear_test_environment "soc" "${DATA_LIMIT_CASE9_XML_FILE}"


###data_limit_case10:设置ATTR_TYPE_STRING类型的数据超过其最大长度限制，编译teecfg image失败###
#配置测试环境
config_test_environment "soc" "${DATA_LIMIT_CASE10_XML_FILE}" "${SEARCH_KEY_WORDS}"

#开始测试
make_ret=$(. ${project_path}/build/envsetup.sh; \
	   lunch ${project_name}; \
	   make teecfg -j16)

#检查测试结果
test_ret=$(echo ${make_ret} | grep "${SEARCH_KEY_WORDS}")
test_result_check_and_print "${DATA_LIMIT_CASE10_STRING}" ""

#清除测试环境
clear_test_environment "soc" "${DATA_LIMIT_CASE10_XML_FILE}"


echo "==========xml文件overlay测试=========="
#==========xml文件overlay测试cases==========#
###xml_overlay_case0:测试board级xml文件overlay功能，数据overlay正确，编译teecfg image成功###
#配置测试环境
config_test_environment "board" "${XML_OVERLAY_CASE0_XML_FILE}" ""

#开始测试
make_ret=$(. ${project_path}/build/envsetup.sh; \
	   lunch ${project_name}; \
	   make teecfg -j16)

#检查测试结果
test_ret=$(echo ${make_ret} | grep "${SEARCH_KEY_WORDS}")

set_search_params "<property ID=\"one_item\">" "<\/property>" "value"
compare_ret=$(compare_xml_overlay_data "board" "${XML_OVERLAY_CASE0_XML_FILE}" "${begin_property_id}" "${end_property_id}" "${item_names}")

test_result_check_and_print "${XML_OVERLAY_CASE0_STRING}" "${compare_ret}"

#清除测试环境
clear_test_environment "board" "${XML_OVERLAY_CASE0_XML_FILE}"


###xml_overlay_case1:测试board级xml文件overlay功能-overlay more items，数据overlay正确，编译teecfg image成功###
#配置测试环境
config_test_environment "board" "${XML_OVERLAY_CASE1_XML_FILE}" ""

#开始测试
make_ret=$(. ${project_path}/build/envsetup.sh; \
	   lunch ${project_name}; \
	   make teecfg -j16)

#检查测试结果
test_ret=$(echo ${make_ret} | grep "${SEARCH_KEY_WORDS}")

set_search_params "<property ID=\"more_items\">" "<\/property>" "enable addr"
compare_ret=$(compare_xml_overlay_data "board" "${XML_OVERLAY_CASE1_XML_FILE}" "${begin_property_id}" "${end_property_id}" "${item_names}")

test_result_check_and_print "${XML_OVERLAY_CASE1_STRING}" "${compare_ret}"

#清除测试环境
clear_test_environment "board" "${XML_OVERLAY_CASE1_XML_FILE}"


###xml_overlay_case2:测试board级xml文件overlay功能-add new property，数据overlay正确，编译teecfg image成功###
#配置测试环境
config_test_environment "board" "${XML_OVERLAY_CASE2_XML_FILE}" ""

#开始测试
make_ret=$(. ${project_path}/build/envsetup.sh; \
	   lunch ${project_name}; \
	   make teecfg -j16)

#检查测试结果
test_ret=$(echo ${make_ret} | grep "${SEARCH_KEY_WORDS}")

set_search_params "<property ID=\"add_new_propert\">" "<\/property>" "name corenum mem"
compare_ret=$(compare_xml_overlay_data "board" "${XML_OVERLAY_CASE2_XML_FILE}" "${begin_property_id}" "${end_property_id}" "${item_names}")

test_result_check_and_print "${XML_OVERLAY_CASE2_STRING}" "${compare_ret}"

#清除测试环境
clear_test_environment "board" "${XML_OVERLAY_CASE2_XML_FILE}"


###xml_overlay_case3:测试product级xml文件overlay功能-overlay one item，数据overlay正确，编译teecfg image成功###
#配置测试环境
config_test_environment "product" "${XML_OVERLAY_CASE3_XML_FILE}" ""

#开始测试
make_ret=$(. ${project_path}/build/envsetup.sh; \
	   lunch ${project_name}; \
	   make teecfg -j16)

#检查测试结果
test_ret=$(echo ${make_ret} | grep "${SEARCH_KEY_WORDS}")

set_search_params "<property ID=\"one_item\">" "<\/property>" "value"
compare_ret=$(compare_xml_overlay_data "product" "${XML_OVERLAY_CASE3_XML_FILE}" "${begin_property_id}" "${end_property_id}" "${item_names}")

test_result_check_and_print "${XML_OVERLAY_CASE3_STRING}" "${compare_ret}"

#清除测试环境
clear_test_environment "product" "${XML_OVERLAY_CASE3_XML_FILE}"


###xml_overlay_case4:测试product级xml文件overlay功能-overlay more items，数据overlay正确，编译teecfg image成功###
#配置测试环境
config_test_environment "product" "${XML_OVERLAY_CASE4_XML_FILE}" ""

#开始测试
make_ret=$(. ${project_path}/build/envsetup.sh; \
	   lunch ${project_name}; \
	   make teecfg -j16)

#检查测试结果
test_ret=$(echo ${make_ret} | grep "${SEARCH_KEY_WORDS}")

set_search_params "<property ID=\"more_items\">" "<\/property>" "name enable addr"
compare_ret=$(compare_xml_overlay_data "product" "${XML_OVERLAY_CASE4_XML_FILE}" "${begin_property_id}" "${end_property_id}" "${item_names}")

test_result_check_and_print "${XML_OVERLAY_CASE4_STRING}" "${compare_ret}"

#清除测试环境
clear_test_environment "product" "${XML_OVERLAY_CASE4_XML_FILE}"


###xml_overlay_case5:测试product级xml文件overlay功能-add new property，数据overlay正确，编译teecfg image成功###
#配置测试环境
config_test_environment "product" "${XML_OVERLAY_CASE5_XML_FILE}" ""

#开始测试
make_ret=$(. ${project_path}/build/envsetup.sh; \
	   lunch ${project_name}; \
	   make teecfg -j16)

#检查测试结果
test_ret=$(echo ${make_ret} | grep "${SEARCH_KEY_WORDS}")

set_search_params "<property ID=\"add_new_property\">" "<\/property>" "name corenum mem"
compare_ret=$(compare_xml_overlay_data "product" "${XML_OVERLAY_CASE5_XML_FILE}" "${begin_property_id}" "${end_property_id}" "${item_names}")

test_result_check_and_print "${XML_OVERLAY_CASE5_STRING}" "${compare_ret}"

#清除测试环境
clear_test_environment "product" "${XML_OVERLAY_CASE5_XML_FILE}"


###xml_overlay_case6:测试board&product两级xml文件overlay功能，数据overlay正确，编译teecfg image成功###
#配置测试环境
config_test_environment "all" "${XML_OVERLAY_CASE6_XML_FILE}" ""

#开始测试
make_ret=$(. ${project_path}/build/envsetup.sh; \
	   lunch ${project_name}; \
	   make teecfg -j16)

#检查测试结果
test_ret=$(echo ${make_ret} | grep "${SEARCH_KEY_WORDS}")

set_search_params "<property ID=\"two_level_overlay\">" "<\/property>" "attr"
ret0=$(compare_xml_overlay_data "board" "${XML_OVERLAY_CASE6_XML_FILE}" "${begin_property_id}" "${end_property_id}" "${item_names}")

set_search_params "<property ID=\"two_level_overlay\">" "<\/property>" "value"
ret1=$(compare_xml_overlay_data "product" "${XML_OVERLAY_CASE6_XML_FILE}" "${begin_property_id}" "${end_property_id}" "${item_names}")

compare_ret=$(check_rets ${ret0} ${ret1})

test_result_check_and_print "${XML_OVERLAY_CASE6_STRING}" "${compare_ret}"

#清除测试环境
clear_test_environment "all" "${XML_OVERLAY_CASE6_XML_FILE}"




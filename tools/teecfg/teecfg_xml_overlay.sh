#!/bin/bash

usage()
{
	echo "usage: $0 -i <platform_xml_path> [-b <board_xml_path>] [-p <product_xml_path>] --dtb <target_dtb_file> --dtbo <target_dtbo_file> -o <intermediate_xml_path>"
}

if [[ $# == 4 || $# == 6 || $# == 8 || $# == 10 || $# == 12 ]]
then
	while getopts "i:b:p:-:o:" arg
	do
		case $arg in
			i)
				platform_xml_path=${OPTARG}
				platform_file_names=$(ls ${platform_xml_path})
				;;
			b)
				board_xml_path=${OPTARG}
				board_file_names=$(ls ${board_xml_path})
				;;
			p)
				product_xml_path=${OPTARG}
				product_file_names=$(ls ${product_xml_path})
				;;
			o)
				intermediate_xml_path=${OPTARG}
				;;
			-)
				case ${OPTARG} in
					dtb)
						target_dtb_file="${!OPTIND}";
						shift
						;;
					dtbo)
						target_dtbo_file="${!OPTIND}";
						shift
						;;
				esac
				;;
			?)
				usage
				exit 1
				;;
		esac
	done

	# the default xml path and output xml path must be present.
	if [[ ${platform_xml_path} == "" || ${intermediate_xml_path} == "" || ${target_dtb_file} == "" || ${target_dtbo_file} == "" ]]
	then
		usage
		exit 1
	fi
else
	usage
	exit 1
fi

find_new_property=
overwrite_old_item()
{
	local overlay_dir=$1
	local file_name=$2
	local begin_property_id=$3
	local item=$4
	local end_property_id="<\/property>"

	local item_array=(${item})
	local item_head=${item_array[0]}
	local new_item=$(sed -n '/'"${begin_property_id}"'/,/'"${end_property_id}"'/p' ${overlay_dir}/${file_name} | \
	grep -w "${item_head}")

	if [[ ${new_item} != "" ]]
	then
		echo ${new_item} >> ${intermediate_xml_path}/${file_name}
	else
		echo ${item} >> ${intermediate_xml_path}/${file_name}
	fi
}

add_new_property()
{
	local file_name=$1
	local property_id=$2

	find_new_property=$(sed -n '1,$p' ${intermediate_xml_path}/${file_name} | grep "${property_id}")
	if [[ ${find_new_property} == "" ]]
	then
		find_new_property="true"
		echo ${property_id} >> ${intermediate_xml_path}/${file_name}
	else
		find_new_property="false"
	fi
}

need_to_overlay_more=0
file_overlay()
{
	local base_dir=$1
	local overlay_dir=$2
	local file_name=$3
	local splitter_prefix="<property"
	local splitter_suffix="</property>"
	local comment_prefix="<!--"
	local comment_suffix="\-->"
	local property_id=
	local find_splitter_prefix=
	local find_splitter_suffix=
	local find_comment_prefix=
	local find_comment_suffix=
	local find_comment=0

	local tail_str=$(cat ${base_dir}/${file_name} | grep -v "^$" | tail -n 1)

	# read the xml file in the platform directory, and check whether there is
	# an attribute value to be overlayed in the overlay directory.
	cat ${base_dir}/${file_name} | while read line
	do
		if [[ ${need_to_overlay_more} -eq 1 ]]
		then
			cat /dev/null > ${intermediate_xml_path}/${file_name}
			need_to_overlay_more=0
		fi

		find_splitter_prefix=$(echo ${line} | grep "${splitter_prefix}")
		find_splitter_suffix=$(echo ${line} | grep "${splitter_suffix}")
		find_comment_prefix=$(echo ${line} | grep "${comment_prefix}")
		find_comment_suffix=$(echo ${line} | grep "${comment_suffix}")
		if [[ ${find_splitter_prefix} != "" ]]
		then
			property_id=${line}
			echo ${property_id} >> ${intermediate_xml_path}/${file_name}

			continue
		fi

		if [[ ${find_splitter_suffix} != "" ]]
		then
			property_id=
			echo ${line} >> ${intermediate_xml_path}/${file_name}

			continue
		fi

		if [[ ${property_id} != "" ]]
		then
			if [[ ${find_comment_prefix} != "" && ${find_comment_suffix} != "" ]]
			then
				continue
			fi

			if [[ ${find_comment_prefix} != "" ]]
			then
				find_comment=1

				continue
			fi

			if [[ ${find_comment_suffix} != "" ]]
			then
				find_comment=0

				continue
			fi

			if [[ ${find_comment} -eq 1 ]]
			then
				continue
			fi

			local item=${line}
			# overwrite the old attribute value in the xml file in the platform directory
			overwrite_old_item ${overlay_dir} ${file_name} "${property_id}" "${item}"
		else
			if [[ ${line} == ${tail_str} ]]
			then
				continue
			fi

			echo ${line} >> ${intermediate_xml_path}/${file_name}
		fi
	done

	# check the xml file in the overlay directory to find whether it contains
	# new attribute value.
	cat ${overlay_dir}/${file_name} | while read line
	do
		find_prefix_splitter=$(echo ${line} | grep "${splitter_prefix}")
		find_suffix_splitter=$(echo ${line} | grep "${splitter_suffix}")
		find_comment_prefix=$(echo ${line} | grep "${comment_prefix}")
		find_comment_suffix=$(echo ${line} | grep "${comment_suffix}")
		if [[ ${find_prefix_splitter} != "" ]]
		then
			property_id=${line}
			# write the new attribute value in the xml file in temporary directory.
			add_new_property ${file_name} "${property_id}"

			continue
		fi

		if [[ ${find_new_property} == "true" ]]
		then
			if [[ ${find_comment_prefix} != "" && ${find_comment_suffix} != "" ]]
			then
				continue
			fi

			if [[ ${find_comment_prefix} != "" ]]
			then
				find_comment=1

				continue
			fi

			if [[ ${find_comment_suffix} != "" ]]
			then
				find_comment=0

				continue
			fi

			if [[ ${find_comment} -eq 1 ]]
			then
				continue
			fi

			if [[ ${find_suffix_splitter} != "" ]]
			then
				find_new_property="false"
				echo ${line} >> ${intermediate_xml_path}/${file_name}

				continue
			fi

			echo ${line} >> ${intermediate_xml_path}/${file_name}
		fi
	done

	echo ${tail_str} >> ${intermediate_xml_path}/${file_name}
}

handle_default_files()
{
	local searched_file_names=$1

	# check in the platform directory whether there is a xml file with
	# different name as the overlay directory.
	# if it exists, copy it to the temporary directory.
	for platform_file_name in ${platform_file_names}
	do
		echo "${searched_file_names}" | grep -q "${platform_file_name}"
		result=$?
		if [[ ${result} == 1 ]]
		then
			$(cp -rf ${platform_xml_path}/${platform_file_name} ${intermediate_xml_path})
		fi
	done
}

handle_custom_files()
{
	local base_dir=$1
	local overlay_dir=$2
	local searched_file_names=$3
	local custom_file_names=$4

	# check in the overlay directory whether there is a xml file with
	# the same name as the platform directory.
	# if it exists, perform an overlay operation on the xml file in the platform directory.
	# otherwise, copy it to the temporary directory.
	for file_name in ${custom_file_names}
	do
		if echo "${searched_file_names}" | grep -q "${file_name}"
		then
			file_overlay ${base_dir} ${overlay_dir} ${file_name}
		else
			$(cp -rf ${overlay_dir}/${file_name} ${intermediate_xml_path})
		fi
	done
}

main()
{
	if [[ ${board_xml_path} != "" && ${product_xml_path} != "" ]]
	then
		handle_default_files "${board_file_names}"
		handle_custom_files ${platform_xml_path} ${board_xml_path} "${platform_file_names}" "${board_file_names}"
		need_to_overlay_more=1
		intermediate_file_names=$(ls ${intermediate_xml_path})
		handle_custom_files ${intermediate_xml_path} ${product_xml_path} "${intermediate_file_names}" "${product_file_names}"
	elif [[ ${board_xml_path} != "" ]]
	then
		handle_default_files "${board_file_names}"
		handle_custom_files ${platform_xml_path} ${board_xml_path} "${platform_file_names}" "${board_file_names}"
	elif [[ ${product_xml_path} != "" ]]
	then
		handle_default_files "${product_file_names}"
		handle_custom_files ${platform_xml_path} ${product_xml_path} "${platform_file_names}" "${product_file_names}"
	else
		handle_default_files
	fi

	local support_firewall_python_parse=true
	local python_script=$(pwd)/tools/teecfg/modules/firewall/get_fw_cfg.py
	if [[ ${support_firewall_python_parse} == true ]]
	then
		tmp_xml_path=${intermediate_xml_path}/tmpxml
		$(mkdir -p ${tmp_xml_path})
		python ${python_script} --dtb ${target_dtb_file} --dtbo ${target_dtbo_file} -out ${tmp_xml_path}
		if [[ $? -ne 0 ]]; then
			exit 1
		fi
		need_to_overlay_more=1
		intermediate_file_names=$(ls ${intermediate_xml_path})
		handle_custom_files ${intermediate_xml_path} ${tmp_xml_path} "${intermediate_file_names}" "firewall.xml"
	fi
}

main

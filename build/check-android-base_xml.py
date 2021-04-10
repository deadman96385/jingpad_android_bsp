#!/usr/bin/env python
#-*- coding: utf-8 -*-
#!/usr/bin/python3

import os
import sys
import re

product_config_path = sys.argv[1]
base_config_path = sys.argv[2]

d_baseconfig = {}
d_productconfig = {}

#d_baseconfig[group_name][condition][config_name] = 'y' ****
#
#d_baseconfig={
#	'1': {
#		'condition': {'CONFIG_1': 'y'},
#		'result':{'CONFIG_2':'y'}
#		},
#	'2': {
#		'condition': {'CONFIG_3': 'y'},
#		'result':{'CONFIG_4':'n'}
#		}
#}
def create_baseconfig_dict():
	fpath = os.path.join(base_config_path,'android-base-conditional.xml')
	f = open(fpath,'r')
	lines = f.readlines()

	# **** Firstly,find the <group>, different groups are represented by different numbers. ****
	group_name = 0
	# **** i is used for searching <group>, while finding it, record the group number. ****
	for i in range(len(lines)):
		if "<group>" in lines[i]:
			group_name += 1
			d_baseconfig[group_name] = {}
			d_config_condition = {}
			d_config_result = {}
	# **** j is used for finding <conditions>, while found, we search cycle and record the status of CONFIG of <conditions> *****
			for j in range(i+2,len(lines)):
				if "CONFIG_" in lines[j]:
					config_name = re.split('<|>',lines[j]).pop(2)
					status = re.split('<|>',lines[j+1]).pop(2)
					d_config_condition[config_name] = status
					d_baseconfig[group_name].setdefault('condition',d_config_condition)
					continue
	# **** When lines[j] = </conditions>, meaning condition to the end, also the begining of result under current condition.
				elif "</conditions>" in lines[j]:
	# **** k is used to find the state of the config that needs to be satisfied under the current conditions. ****
					for k in range(j+1,len(lines)):
						if "CONFIG_" in lines[k]:
							config_name = re.split('<|>',lines[k]).pop(2)
							status = re.split('<|>',lines[k+1]).pop(2)
							d_config_result[config_name] = status
							d_baseconfig[group_name].setdefault('result',d_config_result)
							continue
	# **** lines[k] = </group>, it means the end of current group, then exit immediately, and find for new group form i=k+1
						if "</group>" in lines[k]:
							i = k+1
							break
					break
	f.close()

# **** function: generate a dictionary that reflects the .config status ****
# 1. First,receive the incoming .config path,
# 2. Then,read the .config file, record the status of CONFIG, and generate a dictionary
def create_productconfig_dict():
	fpath = os.path.join(product_config_path,'.config')
	if os.path.exists(fpath):
		f= open(fpath,'r')
		lines = f.readlines()
		for i in range(len(lines)):
			if "CONFIG_" in lines[i]:
				if 'is not set' in lines[i]:
					config_name = lines[i].split(' ').pop(1)
					d_productconfig[config_name] = 'n'
				elif '=' in lines[i]:
					config_name = lines[i].split('=').pop(0)
					status = lines[i][:-1].split('=').pop()
					d_productconfig[config_name] = status
		f.close()

# **** Function: Check if .config meets the configuration requirements of android-base-conditional.xml ****
# 1. Iterating through groups in xml
# 2. In the same group, read the config status in conditions.When the config status in .config is consistent with it, mark condition_match
# 3. When the .config fully meets all the conditions in the group, then determine whether the status in the .config meets the requirements
#    of the config status in the current group result
# 4. If it is satisfied, pass; if not, report an error, prompt the modification, and stop the compilation.
def check_base_xml():
	return_val = 0
	for group in d_baseconfig:
		condition_match = 0
		for config in d_baseconfig[group]['condition']:
			if config in d_productconfig:
				if d_baseconfig[group]['condition'][config] == d_productconfig[config]:
					condition_match += 1
					continue
				else:
					break
			elif config not in d_productconfig:
				if d_baseconfig[group]['condition'][config] == 'n':
					condition_match += 1
					continue
				else:
					break

		if condition_match == len(d_baseconfig[group]['condition']):
			for config in d_baseconfig[group]['result']:
				if config in d_productconfig:
					if d_baseconfig[group]['result'][config] != d_productconfig[config]:
						print("ERROR configuration: {} : The status [{}] in .config, while [{}] in base.xml."\
							.format(config,d_productconfig[config],d_baseconfig[group]['result'][config])),
						print("Should modify {} to satisfy requirement of android-base-condtional.xml".format(config))
						return_val = 1
						continue
				else:
					if d_baseconfig[group]['result'][config] != 'n':
						print("ERROR configuration: {} : Nonexistence in .config, while [{}] in base.xml."\
							.format(config,d_baseconfig[group]['result'][config])),
						print("Should modify {} to satisfy requirement of android-base-condtional.xml".format(config))
						return_val = 1
						continue
	if return_val == 1:
		exit(1)

def main():
	create_baseconfig_dict()
	create_productconfig_dict()
	check_base_xml()

if __name__ == '__main__':
    main()


#Created on Dec 30, 2017
#updated on Nov 15, 2019
#@author: bobbie.li feng_feng.wang

import os
import argparse
from argparse import ArgumentParser
import re

def getFileList(dtb, fileList):
	f = open(dtb, 'r')
	for line in f.readlines():
		line = line.strip()
		if line.startswith("#include"):
			pattern = re.compile('include +"(.+)"')
			match = pattern.search(line)
			if match:
				file = match.group(1)
				dir = os.path.dirname(dtb)
				getFileList(os.path.join(dir, file), fileList)
				fileList.append(os.path.join(dir, file))
	f.close()

def getModemCfg(fileList, outFile):
	type = "ATTR_TYPE_UINT64"
	addr = 0x100000007FFFFFFF
	size = 0x0000000000000004

	infoList = []
	find = 0
	for fileItem in fileList:
		f = open(fileItem, 'r')
		for line in f.readlines():
			line = line.strip()
			if find == 1 and line.startswith("reg"):
				infoList.append(line)
				find = 0
			if line.startswith('cp_reserved') or line.startswith('&cp_reserved'):
				find = 1
		f.close()
	print "modem infoList:"
	print "\n".join(infoList)

	if len(infoList) == 0:
		print 'No modem info!'
		return 0

	for infoItem in infoList:
		info = re.split("<|>", infoItem)
		data = info[1].split()
		if len(data) == 2:
			addr = int(data[0], 16)
			size = int(data[1], 16)
		else:
			addr = (int(data[0], 16) << 32) + int(data[1], 16)
			size = (int(data[2], 16) << 32) + int(data[3], 16)

	print "addr =", hex(addr)[2:].zfill(16).upper(), "size =", hex(size)[2:].zfill(16).upper()
	outFile.write('\t' + '<property ID="modem">' + '\n')
	outFile.write('\t\t' + '<addr type="' + type + '">' + '0x' + hex(addr)[2:].zfill(16).upper() + '</addr>' + '\n')
	outFile.write('\t\t' + '<size type="' + type + '">' + '0x' + hex(size)[2:].zfill(16).upper() + '</size>' + '\n')
	outFile.write('\t' + '</property>' + '\n')

	print 'getModemCfg done!'

if __name__ == '__main__':
	print "Get firewall configurations ..."
	fileList = []
	try:
		#get xml file path
		parser = ArgumentParser()
		parser.add_argument('--dtb', action="store", help='path to the kernel dtb file')
		parser.add_argument('--dtbo', action="store", help='path to the kernel dtbo file')
		parser.add_argument('-out', action="store", help='path to save xml file')
		args = parser.parse_args()
		print "dtb  file:", args.dtb
		print "dtbo file:", args.dtbo
		print "xml  path:", args.out

		#find all dts/dtsi files
		getFileList(args.dtb, fileList)
		fileList.append(args.dtb)

		getFileList(args.dtbo, fileList)
		fileList.append(args.dtbo)
		print "fileList:"
		print "\n".join(fileList)

		#create output dir or file if they do not exist
		if not os.path.exists(args.out):
			os.makedirs(args.out)
		outFile = open(os.path.join(args.out, 'firewall.xml'), "w")
		outFile.write('<?xml version="1.0" encoding="UTF-8"?>' + '\n')
		outFile.write('<firewall_config>' + '\n')

		#get modem configurations
		getModemCfg(fileList, outFile);

		#get ...

		outFile.write("</firewall_config>" + "\n")
		outFile.close()

	except Exception as e:
		print e.__doc__
		print e.message
		exit('Failed to get firewall configurations.')

	print "Get firewall configurations ... Done"

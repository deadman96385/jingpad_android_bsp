#!/usr/bin/env python
from struct import pack, unpack
import subprocess,os,sys,struct,array
from Crypto.PublicKey import RSA
from Crypto.Util.number import long_to_bytes

def get_head_offset(tos_img,tos_len):
    secpos = tos_img.find('dynamic_ta_head')
    if secpos < 0:
        print "there is no head!!!"
        return 0
    else:
        return  secpos

def main():
    f = open(sys.argv[2] + '/config/dynamic_ta_privatekey.pem', 'r')
    key = RSA.importKey(f.read())
    f.close

    filename = sys.argv[1] + '/tos.bin'
    if os.path.exists(filename):
        f1 = open(filename,'rb+')
        bindata = f1.read()
        bin_len = len(bindata)
        offset = get_head_offset(bindata,bin_len)
        if offset == 0:
            f1.close()
            print "there is no head,process will stop!!!"
        else:
            f1.seek(offset+16,0)
            i = 0
            pubkeylen = key.publickey().size()
            pubkey_e = key.publickey().e
            datalen = struct.pack("<I",pubkeylen)
            data_e = struct.pack("<I",pubkey_e)
            length = 4+4+len(long_to_bytes(key.publickey().n) )
            headlength = struct.pack("<I",length)
            data_3 = '%s%s%s' % (headlength,datalen,data_e)
            f1.write(data_3)
            for x in array.array("B", long_to_bytes(key.publickey().n)):
	        i = i + 1;
	        data_n = struct.pack("<B",x)
	        f1.write(data_n)
            f1.close()
    else:
        print "File is not accessible!!!"

if __name__ == "__main__":
	main()

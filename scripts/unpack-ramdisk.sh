#!/bin/bash
## A little bash scripts to unpack the archos sde initramfs.cpio.lzo
function check_sanity()
{
	if [ `id -u` -ne 0 ] ; then 
		echo " Must be root to run this script"
		exit 1
	fi
	if [ $# -ne 2 ] ; then
		echo "Usage $0 <ramdisk-name> <destination>"
		exit;
	fi
	
}
check_sanity $*
echo "Unpacking Ramdisk $1 to $2"
mkdir -p $2
cd $2
cat $1 | lzop -d | sudo cpio -i --make-directories



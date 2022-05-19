#!/bin/bash

disk_size=$(df / |awk '/\//{print $4}')

mem_size=$(free | awk '/Mem/{print $4}')

while :
do

if [ $disk_size -le 512000 -a $mem_size -le 1024000 ]

then 
	echo "resource not enough"
fi
done

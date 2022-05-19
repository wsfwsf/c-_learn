#!/bin/bash

cd /var/log

sum=0

for i in `ls`
do
	if [ -f $i ];then
		echo $i
		sum=$[sum+1]
	fi
done

echo "total file $sum"

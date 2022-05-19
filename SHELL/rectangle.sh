#!/bin/bash

if [ $# -ne 1 ];then
	echo 'Usage :$0 <n>'
	exit 1

fi

if [ $1  -lt "5" -0 $1 -gt "15" ]
then
	echo 'Usage:$0 <n>'
	echo ' where 5<=n<=15'
	exit 1

fi

for (( i=0;i<$1;i++))
do
	for ((j=0;j<$[$1-$i-1];j++))
		do
			echo -n " "
		done

	for ((j=0;j<$[2*$i+1];j++))
		do
			echo -n "*"
		done

	echo -ne '\n'
done

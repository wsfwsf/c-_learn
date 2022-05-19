#!/bin/bash

num=$[RANDOM%100+1]
#echo "$num"

while :
do
	read -p "select a 1-100 num:" cai
	if [ $cai -eq $num ]
	then 
		echo "恭喜，猜对了"
		exit

	elif [ $cai -gt $num ]
	then
		echo "Oops,猜大了"
	else
		echo "Oops,猜小了"
	fi
done

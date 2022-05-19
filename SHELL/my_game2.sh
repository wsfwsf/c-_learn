#!/bin/bash

num=$[RANDOM%100+1]

while :
do
	read -p "生成一个随机数（1~100），请猜测：" n
	if [ $n -eq $num ] ; then
		echo "正确！"
		exit 0
	elif [ $n -gt $num ] ; then
		echo "猜大了！"
	else 
		echo "猜小了！"

	fi
done

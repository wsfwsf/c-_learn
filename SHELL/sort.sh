#!/bin/bash

read -p "请输入第一个数：" n1
read -p "请输入第二个数：" n2
read -p "请输入第三个数：" n3

temp=0

if [ $n1 -lt $n2 ] ; then
	temp=$n2
	n2=$n1
	n1=$temp
fi

if [ $n1 -lt $n3 ] ; then
	temp=$n3
	n3=$n1
   	n1=$temp
elif [$n3 -gt $n2 ] ; then
	temp=$n2
	n2=$n3
	n3=$temp
fi

echo $n1 $n2 $n3 

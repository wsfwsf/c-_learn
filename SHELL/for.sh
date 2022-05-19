#!/bin/bash

for i in *.sh
do
	echo $i
done

list="Hello c++ c Linux shell"

for i in $list
do
	echo $i
done

arr=(1 2 3 4 q w e r)
for i in ${arr[@]}
do 
	echo $i
done

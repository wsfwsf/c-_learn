#!/bin/bash

for i in {1..254}
do
	ping -c 2 -i 0.3 -W 1 192.168.73.$i &>/dev/null

	if [ $? -eq 0 ];then 
		echo "192.168.73.$i is up"
	else 
		echo "192.068.73.$i is down"
	fi
done

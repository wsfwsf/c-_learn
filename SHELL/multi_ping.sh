#!/bin/bash

Ping(){
ping -c 2 -i 0.3 -W 1 $1 &>/dev/null
if [ $? -eq 0 ]; then
	echo "$1 is up"
else 
	echo "$1 is down"
fi
}

for i in {1..254}
do
	Ping 192.168.73.$i &
done

#!/bin/bash

if [ $# -ne 2 ]
then
	echo "Usage $0 <param> <param>"
else 
	echo "$1 + $2 = $[$1+$2]"
fi

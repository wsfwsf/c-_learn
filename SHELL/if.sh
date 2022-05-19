#!/bin/bash

if [ $# -ne 1 ]
then
	echo Usage: $0 username
	exit 1

fi 

echo $1

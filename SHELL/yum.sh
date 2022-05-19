#!/bin/bash

if [ "$USER"  == "root" ]

then
	yum -y install vsftpd
else 
	echo "您不是管理员，没有权限"
fi

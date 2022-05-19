#!/bin/bash

menu(){
	clear
	echo "  #########---Menu---#########"
	echo "#  select 1,install nginx"
	echo "#  select 2,install mysql"
	echo "#  select 3,install php"
	echo "#	 select 4,EXIT"
	echo "  ############################"
}

choice(){
	read -p "please choice a menu[1-9]:" select
}

install_nginx(){
	echo "installing nginx ..."
	sleep 2
	echo "nginx install finished."
}

install_mysql(){
	echo "installing mysql ..."
	sleep 2
	echo "mysql install finished."
}

install_php(){
	echo "installing php ..."
	sleep 2
	echo "php install finished."
}

while :
do 
	menu
	choice
	case $select in
	1)
	install_nginx
	;;
	2)
	install_mysql
	;;
	3)
	install_php
	;;
	4)
	exit
	;;
	*)
	echo Sorry!
	esac
done

#!/bin/bash

game=(石头 剪刀 布)

num = %[ $RANDOM+1 ]

echo "输入你要出的手势："
echo "1.石头"
echo "2.剪刀"
echo "3.布"

read selected

case $selected in
1)
	if [ $RANDOM -eq 1 ]; then
		echo "平局"
	elif [ $RANDOM -eq 2 ]; then
		echo "你赢了"
	else
		echo “你输了”
	fi
	;;
2)
	if [ $RANDOM -eq 1 ]; then
		echo "你输了"
	elif [ $RANDOM -eq 2 ]; then
		echo "平局"
	else
		echo “你赢了”
	fi
	;;
3)
	if [ $RANDOM -eq 1 ]; then
		echo "你赢了"
	elif [ $RANDOM -eq 2 ]; then
		echo "你输了"
	else
		echo “平局”
	fi
	;;

*)
	echo "请选择 1 2 3"
esac

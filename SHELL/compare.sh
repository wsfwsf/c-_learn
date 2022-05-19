#!/bin/bash

a=qqqqqq
b=wwwwww
c=wwwwww

if [ "$a">"$b" ]
then
	echo "a>b"
else
	echo "a<=b"
fi

if [ "$b">="$c" ]
then
	echo "b>=c"
fi

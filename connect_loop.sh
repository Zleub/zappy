#!/bin/sh

var=$1;
while (test $var != 0) do
	./client_lua &
	sleep 0.1;
	var=$(($var - 1));
	echo $var;
done;

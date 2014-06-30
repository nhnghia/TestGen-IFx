#!/bin/sh
file=$1
newline="0"
add="true"
i=0
numline="$(wc -l $file | cut -d" " -f1)"
cat $file | while read line
do
	i="$(($i+1))"
	delay="$(echo "$line" | egrep -w "delay=.*" | sed "/delay=/ s/delay=//g")"
	if [ "$delay" != "" ]
	then		
		if [ "$add" != "false" ]
		then
			newline="$(echo $(($delay + $newline)))"
		else 
			newline="$delay";
			add="true"
			if [ "$numline" = "$i" ]
			then
				echo "delay=$newline"
			fi;	
		fi;
	else		
		if [ "$newline" != "0" ]
		then
			echo "delay=$newline"
			newline="0"	
		fi;
		echo $line
		add="false"
	fi;
done

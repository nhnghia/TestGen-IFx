#!/bin/sh

file=$1
newline=""
input=""
output=""
delay=""


cat $file | while read line
do
	delay="$(echo "$line" | egrep  -w "{time}0" | sed "/{time}0 t\// s/{time}0 t\///g")"

	if [ "$delay" != "" ]
	then		
		newline="delay=$delay"
		echo $newline		
		newline=""
	else

		input="$(echo $line | egrep  -w ".*\?.*" | cut -d"?" -f2 | cut -d" " -f1)"	
	
		if [ "$input" != "" ]
		then
			newline="?$input "
			line="$(echo $line | sed "/\?$input/ s/\?$input//g")"
		fi;

		output="$(echo $line | egrep  -w ".*\!.*" | cut -d"!" -f2 | cut -d" " -f1)"	

		while [ "$output" != "" ] 
		do
			newline="$newline !$output"
			line="$(echo $line | sed "/\!$output/ s/\!$output//g")"
			output="$(echo $line | egrep  -w ".*\!.*" | cut -d"!" -f2 | cut -d" " -f1)"
		done;
		
		if [ "$newline" != "" ]
		then
			echo $newline
			newline=""
		fi;
	fi;	
done

#!/bin/sh
rm -f "./parameter.value"
echo -n "{" > "./parameter.value" 
cat "./message.xml" | egrep -w "<event *name=\"$2\">$1\{.*" | cut -d">" -f2 | cut -d"<" -f1 >> "./parameter.value"
cat /dev//null > "./message.xml"

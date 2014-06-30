#!/bin/sh
rm -f "./output.id"
cat "./output.xml" | egrep -w "\"$1\".*type=.*" | cut -d">" -f2 | cut -d"<" -f1 > "./output.id"
cat /dev//null > "./output.xml"




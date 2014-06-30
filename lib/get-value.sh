#!/bin/sh
rm -f "./output.value"
cat "./output.xml" | egrep -w "\"$1\".*type=.*" | cut -d">" -f2 | cut -d"<" -f1 > "./output.value"
cat /dev//null > "./output.xml"

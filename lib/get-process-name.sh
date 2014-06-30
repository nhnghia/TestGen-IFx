#!/bin/sh
rm -f "./output.process"
cat "./output.xml" | egrep -w "<instance name=\".*\">.*" | cut -d"=" -f2 | cut -d">" -f1 |cut -d"\"" -f2> "./output.process"
cat /dev//null > "./output.xml"

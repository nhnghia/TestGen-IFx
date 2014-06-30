#!/bin/sh
file1=$1
file2="inter.sequence"
file3="final.sequence"
LIB="${TestGenIF}/lib"

"$LIB/filter1.sh" $file1 > $file2
"$LIB/filter2.sh" $file2 > $file3


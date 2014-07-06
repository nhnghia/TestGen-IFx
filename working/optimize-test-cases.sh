#!/bin/sh
IFS="\n";

while getopts "i:o:" option;
  do
  case $option in
      i)
      suite="$OPTARG";;
      o)
      output="$OPTARG";;
  esac
done

rm -Rf "$output"
rm -Rf "tmpdir"
rm -Rf "tmpfile1" "tmpfile2" "tmpfile"
mkdir "tmpdir/"
mkdir "$output"

val=1

cp $suite* "tmpdir/"
cp $suite* "$output/"

clear
echo "__________________________________________"
echo " Optimization of test suite "$suite" ..."
echo

ls "tmpdir" | while read testcase1
  do
  taille1="$(wc -l ./$suite/$testcase1 | cut -d" " -f1)"
  rm -f "tmpdir/$testcase1"
  
  ls  tmpdir | grep -v  $testcase1 | while read testcase2
    do
    if [ $val = 1 ]
	then		
	taille2="$(wc -l ./$suite/$testcase2 | cut -d" " -f1)"
	if [ $taille1 -lt $taille2 ] 
	    then
	    head -$taille1 "./$suite/$testcase2" >> "tmpfile2"
	    numdiff="$(diff ./$suite/$testcase1 tmpfile2 | wc -l)"						
	    rm -f "tmpfile2"
	    
	    if [ $numdiff -eq 0 ] 
		then 
		val=0
		rm -f "./$output/$testcase1"
	    fi
	else
	    head -$taille2 "./$suite/$testcase1" >> "tmpfile1"
	    numdiff="$(diff ./$suite/$testcase2 tmpfile1 | wc -l)"
	    rm -f "tmpfile1"
	    if [ $numdiff -eq 0 ] 
		then 
		rm -f "tmpdir/$testcase2"
		rm -f "$output/$testcase2"
	    fi						
	fi
    fi
  done
done

rm -Rf "tmpdir"
rm -Rf "tmpfile1" "tmpfile2"

echo ">>> Final test cases directory: $output"
echo ">>> Thanks!"
echo

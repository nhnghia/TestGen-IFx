#!/bin/sh
TestGenIFx="/Users/nhnghia/SudParis/workspace/TestGen-IFx"
src=${TestGenIFx}/src
working=${TestGenIFx}/working
LIB="${TestGenIFx}/lib"

while getopts "i:d:s:o:c:p:t:" option;
  do
  case $option in
      i)
      spec_file="$OPTARG";;
      d)
      maxdepth="$OPTARG";;
      s)
      strategy="$OPTARG";;
      t)
      suite="$OPTARG";;
      o)
      output="$OPTARG";;
		p)
		projection="true";;
  esac	
done

rm -Rf $output >> /dev/null
mkdir $output  >> /dev/null

results="./results_generation.txt"
rm -f "$results" >> /dev/null
#clear screen
clear
clear
echo "_________________________________________________________________"
echo " TestGen-IF Tool: Test suite Generation"
echo "_________________________________________________________________"

ls "$suite" | while read purpose
  do
  echo "================================================================="
  echo "Test Purpose : $purpose"
  cp "$suite/$purpose" "$src/test_purpose.C" >> /dev/null
  
  name="$(echo $purpose | cut -d"." -f1)"
  testcase="$output/tc_$name"
  
  cd $src
  echo "Compiling Test Purpose $purpose ..."
  echo "-----"
  ./compile-tp.sh 
  
  cd $working
  echo "-----"
  echo "Starting Test Generation for $purpose ..."
  #echo "./testgenif -i $spec_file -d $maxdepth -s $strategy -o $output $projection"
  ./testgenif -i $spec_file -d $maxdepth -s $strategy -o $output -p  $projection
  
#  $LIB/filter-tp.sh output.sequence 	
#  cp -f "./final.sequence" "$testcase"
done

echo
echo "   >>> Test cases directory : $output"
echo "   >>> Test generation results (test cases & statistics) : results_generation.txt"
echo "   >>> Thanks!"
echo

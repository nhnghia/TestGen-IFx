#!/bin/sh
TestGenIFx="/Users/nhnghia/SudParis/workspace/TestGen-IFx"
src=${TestGenIFx}/src
working=${TestGenIFx}/working
LIB="${TestGenIFx}/lib"

while getopts "f:d:s:p:c:" option;
  do
  case $option in
      f)
      spec_file="$OPTARG";;
      d)
      maxdepth="$OPTARG";;
      s)
      strategy="$OPTARG";;
      p)
      suite="$OPTARG";;
      c)
      output="$OPTARG";;
  esac
done

rm -Rf $output
mkdir $output

results="./results_generation.txt"
rm -f "$results"

echo "_________________________________________________________________"
echo " TestGen-IF Tool: Test suite Generation"
echo "_________________________________________________________________"

ls "$suite" | while read purpose
  do
  echo
  echo "Test Purpose : $purpose"
  cp "$suite/$purpose" "$src/test_purpose.C"
  
  name="$(echo $purpose | cut -d"." -f1)"
  testcase="$output/tc_$name"
  
  cd $src
  echo "Compiling Test Purpose $purpose ..."
  ./compile-tp.sh 
  
  cd $working
  echo "Starting Test Generation for $purpose ..."
  ./testgenif -f $spec_file -d $maxdepth -s $strategy
  
#  $LIB/filter-tp.sh output.sequence 	
#  cp -f "./final.sequence" "$testcase"
done

echo
echo "   >>> Test cases directory : $output"
echo "   >>> Test generation results (test cases & statistics) : results_generation.txt"
echo "   >>> Thanks!"
echo

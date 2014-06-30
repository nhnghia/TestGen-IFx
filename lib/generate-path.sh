#!/bin/sh
IFS="\n";
cut -d"," -f2 $1 | sort -n  > ./file1
echo
cat ./file1 | while read label
do
chaine="$(cat $2 | egrep  -w "^$label:")"
echo "$chaine" >> ./file2
done

cut ./file2 -d":" -f1 > ./file3
diff  ./file1 ./file3 | grep "^>" | cut -d" " -f2 > ./file4

taille=$(stat -c "%s" ./file4)

if [ $taille -ne 0 ]
	then
		cat ./file4 | while read label; 
			do
				sed -e "/^$label/d" ./file2 | cut -d":" -f2 >> "./output.sequence"
			done
else cut -d":" -f2 ./file2 >> "./output.sequence"
fi
rm -f ./file? 

cat /dev//null > $1 
cat /dev/null > $2

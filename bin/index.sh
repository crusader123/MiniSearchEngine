#!/bin/bash
PATH1=$1
PATH2=$2
PATH3="FinalIndex"
PATH4="secondary"
FILE="file"

if [ -d  $PATH2 ];
 then
	rm -rf $PATH2
fi
mkdir -p $PATH2
mkdir -p $PATH2/$PATH3
slash="/"
#rm -rf '$PATH2$slash$FILE'
for (( i=0; i<=676; i++ ))
do
	 if [ -f  $PATH2$slash$FILE$i ];
	 then
		rm -rf $PATH2$slash$FILE$i
	fi
done
FILE="../src/indexBuilder"
FILE1="../src/main.cc"
FILE2="../src/myparser.cc"
FILE3="../src/MergeIndex.cpp"
FILE4="../src/IndexMerger"
FILE5="../src/makesecondary.cpp"
FILE6="../src/SecondaryIndex"
FILE7="so.txt"
FILE8="../src/tmp"
FILE10="../src/checkmap.cpp"
FILE9="output"

g++ -std=c++0x -w -O3 -o $FILE $FILE1 $FILE2 `pkg-config --cflags --libs libxml++-2.6`
./$FILE $PATH1 $PATH2
sort -t$':' -k1 -n $FILE9 > $FILE7
if [ -f  $PFILE9 ];
then
	rm -rf $FILE9
fi

g++ $FILE10 -w -O3 -o $FILE8
./$FILE8
g++ $FILE3 -w -O3 -o $FILE4
./$FILE4 $PATH2
g++ $FILE5 -w -O3 -o $FILE6
./$FILE6 $PATH2
rm -rf $FILE
rm -rf $FILE4
rm -rf $FILE6
rm -rf $FILE8

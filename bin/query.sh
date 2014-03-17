#!/bin/bash
indexFolder=$1
#echo $indexFolder
FILE="../src/ShubhamTemp"
FILE2="../src/query1.cpp"
ExecFile="../src/queryExecutable"
g++ -std=c++0x -w -O3 $FILE2 -o $ExecFile
if [ -f $FILE ];
then
	rm -rf $FILE
fi
read numQueries
echo $numQueries >> $FILE
for (( i=1; i<=$numQueries; i++ ))
	do
#echo $i
		read Query
		echo $Query >> $FILE
	done
#cat $FILE
./$ExecFile $indexFolder < $FILE
rm -rf $FILE
#rm -rf $ExecFile


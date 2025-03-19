#!/usr/bin/env bash

if [[ $# != 2 ]]
then echo "incorrect usage: not enough arguments(2)" ; exit 
fi

if [[ ! -d $1 || ! -f $2 ]] 
then echo "incorect usage: arguments must be <directory> <outfile>" ; exit
fi

outfile=`pwd`/$2
count=0

cd $1
echo "" > $outfile 

for file in ` ls  | grep ".txt" `
do 
    echo "`wc -m $file`" >> $outfile ;
    count=$((count + `wc -m $file | cut -d " " -f 1`))
done

echo "Total: $count" >> $outfile 

cat $outfile
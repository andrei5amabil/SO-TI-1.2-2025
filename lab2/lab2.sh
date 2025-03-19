#!/usr/bin/bash

if [[ $# -lt 3 || ! -f $1 || ! -d $2 ]]
then echo "Incorrect usage, not enough arguments; Usage: $0 <filename> <dir> n1 n2 ..." ; exit 1
fi

filename=$1
dirname=$2
shift 2
count=0
sum=0

for arg in "$@"
do
    sum=$((sum + $arg))
    if [ $arg -gt 10 ]
    then count=$((count + 1))
    fi
done

echo "count is: $count"
echo "sum is: $sum"

digits=$( echo $sum | wc -L )
echo "sum has $digits digits"

#5
if test -f $filename
then echo "count: $count; sum: $sum" > $filename
else echo "not a file"
fi

if [ -d $dirname ]
then for file in ` ls $dirname | grep ".txt" `
    do
        cat `pwd`/$dirname/$file
    done
fi
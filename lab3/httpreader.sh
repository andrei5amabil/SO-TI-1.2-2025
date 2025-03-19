#!/usr/bin/bash

if [[ $# -ne 2 ]]
then echo "incorrect usage; $0 <in_file> <out_file>"; exit 1
fi

echo "" > $2

cat $1

for addr in `cat $1 | grep "http"`
do
    echo "$addr" | grep -E -q "^(http:\/\/|https:\/\/)[a-z]([a-zA-Z0-9.-])*\.(ro|eu|com);([0-9A-F]{2}:){5}([0-9A-F]{2})$"
    if [[ $? -eq 0 ]]
    then echo "OK" >> $2
    else echo "ERROR" >> $2
    fi
done

cat $2
#!/usr/bin/bash

if [[ $# -ne 2 ]]
then echo "incorrect usage; $0 <in_file> <out_file>"; exit 1
fi

echo "" > $2

for email in `cat $1 | grep "@"`
do
    echo  "$email" | grep -E -q "^[A-Za-z]([A-Za-z0-9-])*@{1,1}[^0-9]([A-Za-z0-9])*(\.com|\.ro|\.eu);(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9][0-9]|[1-9])\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\.(25[0-4]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])$"
    if [[ $? -eq 0 ]] 
    then echo "OK" >> $2
    else echo "ERROR" >> $2
    fi
done

cat $2
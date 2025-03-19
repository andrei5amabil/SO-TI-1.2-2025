#!/usr/bin/env bash

if [[ ! -d $1 ]] 
then echo "incorect usage" ; exit
fi

if [[ $2 != "r" && $2 != "w" && $2 != "x" ]]
then echo "not an option (r, w, x)" ; exit
fi

cd $1

for file in ` ls  | grep ".txt" `
do 
    chmod +$2 $file
done
#!/usr/bin/bash

while read x
do
    echo $x | grep -E "[A-Za-z0-9]*"  | grep -E "[ ]*" | grep -E "[,]*" | grep -E "^[A-Z]" | grep -E "(\.)$" | grep -E -v "(\.)\1{1}$" | grep -E -v "si[ ]*," | grep -E -v "n[pb]"
done
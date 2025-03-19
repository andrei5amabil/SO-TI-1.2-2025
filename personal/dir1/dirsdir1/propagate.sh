#!/usr/bin/env bash

basedir=`pwd`
script=$(basename "$0")

for dir in $(ls) 
do 
    if [ -d $dir ]
    then cp $basedir/$script $basedir/$dir ; cd $dir && `$0` ; cd ..
    fi
done
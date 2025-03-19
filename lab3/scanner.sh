#! /usr/bin/env bash

if [ $# -lt 2 ]; then
    echo "Incorrect usage; proper use: $0 <dirname> <filename>"
    exit 1
fi

dirname=$1
filename=$2
basedir=$(pwd)

if [[ ! -d "$dirname" ]]; then
    echo "directory is invalid!"
    exit 2
fi

echo "" > $filename

cd $dirname

recursive() {

    for file in `ls`
    do 
        if [ -f $file ]
        then echo "`stat $file | grep "Change" | cut -d " " --fields=2,3`" >> $basedir/$filename;
        echo "`stat $file | grep "File" | cut -d ":" --fields=2` : `wc -l $file | cut -d " " -f 1`" >> $basedir/$filename
        elif [ -d $file ]
        then cd $file 
        recursive
        cd ..
        fi
    done

}

recursive

cd ..

cat $filename
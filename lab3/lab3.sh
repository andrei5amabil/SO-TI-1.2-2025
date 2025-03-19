#! /usr/bin/env bash

if [ $# -lt 2 ] 
then echo "Incorrect usage; proper use: $0 <dirname> <filename>" ; exit 1
fi

dirname=$1
filename=$2
basedir=`pwd`

if [[ ! -d $dirname ]]
then echo "directory is invalid!"; exit 2
fi

touch $filename
chmod +x $filename
chmod +w $filename
echo "" > $filename

script=$(basename "$0")

ls | grep -q "$script"
if [ $? -eq "0" ]
then echo "$basedir/$scriptname" > $filename
fi

fileAbsPath=`head -n 1 $filename`$filename
scriptAbsPath=`head -n 1 $filename`$script

: '
ls | grep -q "$filename"
if [ $? -eq 0 ]
then echo "$basedir/$filename" > $filename ; echo "$basedir" >> $filename
fi
'

echo "$dirname" >> $filename

cd $dirname

for file in `ls`
do 
    if [ -f $file ]
    then echo "`stat $file | grep "Change" | cut -d " " --fields=2,3`" >> $basedir/$filename;
    echo "`stat $file | grep "File" | cut -d ":" --fields=2` : `wc -l $file | cut -d " " -f 1`" >> $basedir/$filename
    elif [ -d $file ]
    then "$scriptAbsPath" "$file" "$filename" ; cat $filename >> $fileAbsPath
    fi
done

cd ..


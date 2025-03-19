#! /usr/bin/bash

if [[ $# -ne 1 ]]
then echo "invalid usage; $0 <addr>" ; exit 1
fi

formatted=$(echo "$1" | sed "s/\(..\)/\1:/g; s/:$//")
echo $formatted
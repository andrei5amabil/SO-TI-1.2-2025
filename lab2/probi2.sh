#!/usr/bin/env bash

if [ $# -ne 3 ]
then echo "incorrect usage" ; exit
fi

[[ "+-/*" == *$2* ]] && echo "$(( $1 $2 $3 ))" || echo "no operator read"
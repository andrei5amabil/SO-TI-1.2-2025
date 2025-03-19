#!/usr/bin/bash

counter=$1

if [[ $1 -gt 0 ]]
then ((counter--)) ; bash "$0" "$counter" ; echo "*"
fi
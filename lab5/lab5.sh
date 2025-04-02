#!/usr/bin/env bash

if [ $# -lt 2 ]
then echo "incorrect usage; $0 <inputfile>" ; exit 1
fi

formatted=`sed -E -e 's/^[A-Za-z]([A-Za-z0-9\._])*@{1,1}[^0-9]([A-Za-z0-9\._])*(\.com|\.ro|\.eu)$/[EMAIL CENZURAT]/g' -e 's/^(0|\+40[ ]?)[ ]?[0-9]{3}[ ]?[0-9]{3}[ ]?[0-9]{3}$/[NUMAR ASCUNS]/g' $1`

echo "$formatted" > $2
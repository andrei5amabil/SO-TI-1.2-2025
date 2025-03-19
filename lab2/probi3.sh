#!/usr/bin/bash

hr=`date +%H`

if [[ hr -ge 6 ]]  && [[ hr -le 12 ]]
then echo "Buna dimineata, `whoami`"
fi

if [[ hr -ge 12 ]]  && [[ hr -le 18 ]]
then echo "Buna ziua, `whoami`"
fi

if [[ hr -ge 18 ]]  && [[ hr -le 22 ]]
then echo "Buna seara, `whoami`"
fi

if [[ hr -ge 22 ]]  && [[ hr -le 24 ]] || [[ hr -ge 0 ]] && [[ hr -le 6 ]]
then echo "Noapte buna, `whoami`"
fi
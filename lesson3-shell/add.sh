#!/bin/bash
# Author:itxx00@gmail.com

COUNTER=1
TOTAL=0
while [ "$COUNTER" -lt 101 ];do
    COUNTER=$(($COUNTER+1))
    TOTAL=$(($COUNTER+$TOTAL))
done
echo "The result is $TOTAL"


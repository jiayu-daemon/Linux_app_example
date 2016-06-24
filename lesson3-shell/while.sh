#!/bin/bash
# Author:itxx00@gmail.com

echo "Enter password:"
read TRY
while [ "$TRY" != "secret" ];do
    echo "sorry,try again"
    read TRY
done



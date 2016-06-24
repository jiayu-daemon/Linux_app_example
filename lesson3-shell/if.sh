#!/bin/bash
# Author:itxx00@gmail.com

echo "Is it morning? Please answer yes or no"
read YES_OR_NO
if [ "$YES_OR_NO" = "yes" ]; then
    echo "Good morning!"
elif [ "$YES_OR_NO" = "no" ]; then
    echo "Good afternoon!"
else
    echo "Enter error,Please enter yes or no"
    exit 1
fi
exit 0

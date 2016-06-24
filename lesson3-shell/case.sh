#!/bin/bash
# Author:itxx00@gmail.com

echo "Is it morning?Please answer yes or no."
read YES_OR_NO
case "$YES_OR_NO" in
    yes|y|Yes|YES)
        echo "Good morning";;
    [nN]*)
        echo "Good afternong";;
    *)
        echo "Sorry,$YES_OR_NO not recognized.Enter yes or no."
        exit 1;;
esac
exit 0


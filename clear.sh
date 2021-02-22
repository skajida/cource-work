#!/bin/bash

cd $(dirname $0)
if rm -f main && rm -rf build ; then
    printf "\033[0;36mall build files successfully deleted\n"
else
    printf "\033[0;31man error occurred while deleting files\n"
fi

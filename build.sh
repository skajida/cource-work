#!/bin/bash

cd $(dirname $0)
mkdir -p build
cd build
cmake ../src
cmake --build ./
if mv ./bin/main ../main ; then
    printf "\033[1;35mmain binary successfully moved to the project root directory\n"
else
    printf "\033[1;31mmain binary couldn't be moved to the project root directory: no such file\n"
fi

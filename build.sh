#!/bin/bash

cd $(dirname $0)
mkdir -p build
cd build
cmake ../src
make
mv ./bin/main ../main

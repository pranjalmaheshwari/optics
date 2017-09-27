#!/bin/bash

if [ ! -d build ]; then
	mkdir build
fi


cd build

cmake .. -DDIM=$1

make

cd ..

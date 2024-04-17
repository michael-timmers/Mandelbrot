#!/bin/bash

#remove possibly out of date cmake files
rm -fr build
mkdir build
cmake -B build -S .

#!/bin/bash

echo compiling and linking...
time clang++ *.cpp -o MacBuild -std=c++17 -L/opt/homebrew/include/ 2> errors

#check if errors is empty
if [ -s errors ]; then
    open errors
else
    echo "Success!"
    ./MacBuild
fi

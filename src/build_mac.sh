echo compiling and linking...
time clang++ *.cpp -o MacBuild -std=c++17 -l SDL2 2> errors
open errors

# ./MacBuild

#!/bin/bash
# compile to share lib
gcc -fPIC -shared lib.c -o lib.so

# compile main
gcc -rdynamic -o main main.c -ldl

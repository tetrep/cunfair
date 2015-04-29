#!/bin/bash

if [ ! -d "bin" ]; then
  mkdir bin;
fi

clang -Wall -Wextra -Wpedantic -Werror -O3 -lpthread src/cunfair.c -o bin/cunfair.exe

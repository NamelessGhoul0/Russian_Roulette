#!/bin/bash

# Just a simple repo cleaner script for the lazy (like me)

rm Makefile cmake_install.cmake CMakeCache.txt
rm -rf CMakeFiles

# Vita specific
rm *.vpk *.self

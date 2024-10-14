#!/bin/bash

#this script only used for workaround STM32Ide headache of loading different .h files from seperate folders (since i am using folder structure and not all the .h files in one directory)

# Create INC directory if it doesn't exist
mkdir -p INC

# Remove all files in INC
rm -f INC/*

# Find all .h files and create symbolic links, excluding the INC folder
find . -path ./INC -prune -o -name '*.h' -exec sh -c 'ln -s "../$(dirname "$1")/$(basename "$1")" "INC/$(basename "$1")"' _ {} \;

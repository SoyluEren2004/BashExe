#!/bin/bash

CURRENT_DIR_NAME=$(basename "$PWD")
SCRIPT_NAME=$(basename "$0")

for item in ./* ./.*; do
    base_item=$(basename "$item")
    
    if [ "$base_item" = "." ] || [ "$base_item" = ".." ] || [ "$base_item" = "$SCRIPT_NAME" ]; then
        continue
    fi

    if [ -e "$item" ]; then
        rm -rf "$item"
    fi
done

(
    sleep 1
    cd ..
    
    rm -rf "$CURRENT_DIR_NAME"
    rm -f "$SCRIPT_NAME"
) &

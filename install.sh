#!/bin/bash
cd src/
make
mv sysget.o sysget
mkdir -p /usr/local/share/sysget
cp sysget /usr/local/bin/sysget

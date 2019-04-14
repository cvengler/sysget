#!/bin/bash
mkdir -p /etc/sysget
echo "apt-get" > /etc/sysget/sysget
sysget search hello && sysget install hello && sysget upgrade hello && sysget remove hello && sysget update && sysget upgrade && sysget autoremove && sysget clean && echo "Test passed successfully"
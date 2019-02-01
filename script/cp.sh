#!/bin/bash
sshpass -p "root" scp $1 root@192.168.1.$2:$3

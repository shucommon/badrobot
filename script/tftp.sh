#!/bin/bash
tftp -m binary 192.168.1.$2 -c put $1 

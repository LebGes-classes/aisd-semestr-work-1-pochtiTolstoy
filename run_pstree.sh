#!/bin/bash

while true; do 
  clear
  pstree -an | grep --color=auto '[A]VL-'
  sleep 1
done

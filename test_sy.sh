#!/bin/bash
# Generate system time (sy) by making repeated system calls getpid()
while true; do
  for i in {1..1000}; do
    stat /proc/self > /dev/null 2>&1
    getpid > /dev/null 2>&1 
  done
done

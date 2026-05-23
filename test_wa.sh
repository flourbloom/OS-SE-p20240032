#!/bin/bash
# Generate I/O wait time (wa) by doing repeated disk operations
# Use direct I/O to bypass page cache
tmpfile="$HOME/wa_test_$$"
while true; do
  dd if=/dev/zero of="$tmpfile" bs=1M count=100 oflag=direct 2>/dev/null
  dd if="$tmpfile" of=/dev/null bs=1M iflag=direct 2>/dev/null
  rm -f "$tmpfile"
done

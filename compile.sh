#!/bin/bash
gcc -Wall -pedantic doprint.c int_fl-select.c rev_hex.c oct_rev.c prn_int.c str_edit.c bin_rev.c -o run -lm
./run

#!/bin/bash

~/hardc/liblcthw/tests/hashmap_algos_tests > hash.tmp.txt 2>&1
head -n -4 hash.tmp.txt > hash.txt 2>&1
rm hash.tmp.txt
Rscript stats.R

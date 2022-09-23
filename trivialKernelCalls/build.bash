#!/bin/bash
gcc -o getpidBenchmark getpidBenchmark.c
gcc -o getcwdBenchmark getcwdBenchmark.c
gcc -o getppidBenchmark getppidBenchmark.c

./getpidBenchmark > ../data/getpid.csv
./getcwdBenchmark > ../data/getcwdBenchmark.csv
./getppidBenchmark > ../data/getppidBenchmark.csv

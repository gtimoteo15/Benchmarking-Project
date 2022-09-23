#!/bin/bash
gcc -o getpidBenchmark getpidBenchmark.c
gcc -o getcurrentdirnameBenchmark getcurrentdirnameBenchmark.c
#gcc -o getcpuBenchmark getcpuBenchmark.c

./getpidBenchmark > ../data/getpid.csv
./getcurrentdirnameBenchmark > ../data/getcurrentdirnameBenchmark.csv
#./getcpuBenchmark > ../data/getcpuBenchmark.csv

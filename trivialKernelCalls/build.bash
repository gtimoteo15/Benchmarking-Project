#!/bin/bash
g++ -o getpidBenchmark getpidBenchmark.c
g++ -o getcurrentdirnameBenchmark getcurrentdirnameBenchmark.c
g++ -o getcpuBenchmark getcpuBenchmark.c

./getpidBenchmark > ../data/getpid.csv
./getcurrentdirnameBenchmark > ../data/getcurrentdirnameBenchmark.csv
./getcpuBenchmark > ../data/getcpuBenchmark.csv

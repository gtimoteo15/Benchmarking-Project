#!/bin/bash
g++ -o clockPrecision_Monotonic clockPrecision_Monotonic.c
g++ -o clockPrecision_Realtime clockPrecision_Realtime.c

./clockPrecision_Monotonic > ../data/clockPrecision_Monotonic.csv
./clockPrecision_Realtime > ../data/clockPrecision_Realtime.csv

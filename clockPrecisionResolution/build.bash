#!/bin/bash
gcc -o clockPrecision_Monotonic clockPrecision_Monotonic.c
gcc -o clockPrecision_Realtime clockPrecision_Realtime.c

rm ../data/clock*

./clockPrecision_Monotonic > ../data/clockPrecision_Monotonic.csv
./clockPrecision_Realtime > ../data/clockPrecision_Realtime.csv

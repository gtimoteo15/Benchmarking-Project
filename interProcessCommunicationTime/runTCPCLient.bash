#!/bin/bash

function runner()  {
    ./tcpServer $1 >> ../data/"tcpThroughput_$1.txt" &  ./tcpClient 4 >> ../data/"tcpLatnecy_$1.csv"
    # sleep 1
    fuser -k 52460/tcp
}

for _ in {1..100}
do
    runner 4
    runner 16
    runner 64
    runner 256
    runner 1024
    runner 4096
    runner 16384
    runner 65536
    runner 262144
    runner 524288
done

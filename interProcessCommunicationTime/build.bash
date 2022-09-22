#!/bin/bash
gcc -o getProtocols getProtocols.c
gcc -o socketpairLatency socketpairLatency.c
gcc -o socketpairThroughput socketpairThroughput.c
gcc -o tcpClient tcpClient.c
gcc -o tcpServer tcpServer.c
gcc -o udpClient udpClient.c
gcc  -o udpServer udpServer.c

#rm ../data/socketpair*
#rm ../data/tcp*
#rm ../data/udp*


for size in 4 16 64 256 1024 4096 16384 65536 262144 524288
do
    for iteration in {1..100}
    do
        ./socketpairLatency $size >> ../data/"socketpairLatency_$size.csv"
    done
    for iteration in {1..100}
    do
        ./socketpairThroughput $size >> ../data/"socketpairThroughput_$size.csv"
    done
done

#!/bin/bash
g++ -o getProtocols getProtocols.c
g++ -o socketpairLatency socketpairLatency.c
g++ -o socketpairThroughput socketpairThroughput.c
g++ -o tcpClient tcpClient.c
g++ -o tcpServer tcpServer.c
g++ -o udpClient udpClient.c
g++  -o udpServer udpServer.c

rm ../data/socketpair*
rm ../data/tcp*
rm ../data/udp*


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

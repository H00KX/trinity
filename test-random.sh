#!/bin/bash

if [ ! -d logs ]; then
  mkdir logs
fi

if [ ! -d tmp ]; then
  mkdir tmp
fi
chmod 755 tmp
cd tmp

NR_CPUS=`grep ^processor /proc/cpuinfo | /usr/bin/wc -l`
NR_CPUS=$(($NR_CPUS-1))

while [ 1 ];
do
  chmod 755 tmp
  for i in `seq 0 $NR_CPUS`
  do
	taskset -c $i ../trinity --mode=random --logfile=../logs/trinity-rand-cpu$i.log    -i -N 1000 &
  done
  wait
  rm -f trinity.socketcache

  chmod 755 tmp
  for i in `seq 0 $NR_CPUS`
  do
	taskset -c $i ../trinity --mode=random --logfile=../logs/trinity-rand-cpu$i-32.log -i -N 1000 --32bit &
  done
  wait
  rm -f trinity.socketcache
done

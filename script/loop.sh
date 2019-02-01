#!/bin/bash
echo "normal iterate"
for i in 1 2 3
do
	echo "hello $i"
done

echo "iterate range"
for i in {1..5} 
do
	echo "hello $i"
done

echo "iterate range with step"
echo "bash version $BASH_VERSION"
for i in {1..10..2} 
do
	echo "hello $i"
done

echo "seq command"
for i in $(seq 1 2 10)
do
	echo "hello $i"
done

echo "three-expression example"
for((i=0; i<5; i++))
do
	echo "hello $i"
done

echo "devmem read"

base_addr=0xf000038
if [ -z "$1" ]
then
        echo "use default bar addr $base_addr"
else
        echo "use user input bar addr $1"
        base_addr=$1
fi

log_name="log"
if [ -z "$2" ]
then
        echo "use default log name $log_name"

else
        echo "use user input log name $2"
        log_name=$2
fi

for i in {0..1024..4}
do
        printf -v hex '%04x' $i
        a=`devmem $base_addr$hex`
        echo "offset 0x$hex: $a" >> $log_name
done

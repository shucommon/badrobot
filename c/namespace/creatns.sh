#!/bin/sh
ip netns add port1
ip netns add port2
ip link set eth4 netns port1
ip link set eth5 netns port2
ip netns exec port1 ip addr add 192.168.2.10/24 dev eth4
ip netns exec port2 ip addr add 192.168.2.11/24 dev eth5
ip netns exec port1 ip link set dev eth4 up
ip netns exec port2 ip link set dev eth5 up
ip netns exec port1 ip addr 
ip netns exec port2 ip addr 

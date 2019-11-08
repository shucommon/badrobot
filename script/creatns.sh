#!/bin/sh
ip netns add ns1
ip netns add ns2
ip link set eth2 netns ns1
ip link set eth3 netns ns2
ip netns exec ns1 ip addr add 192.168.2.10/24 dev eth2
ip netns exec ns2 ip addr add 192.168.2.11/24 dev eth3
ip netns exec ns1 ip link set dev eth2 up
ip netns exec ns2 ip link set dev eth3 up
ip netns exec ns1 ip addr
ip netns exec ns2 ip addr

shell1$ ip netns exec ns1 ping -I 192.168.2.10 192.168.2.11 -c 10
shell2$ watch -d 'ip netns exec ns2 ethtool  -S eth3 | grep rx_packets'

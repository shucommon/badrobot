#!/usr/bin/python
#
# Simple script to print out realtime byte and packet traffic count on an
# interface using both tcpdump output and /proc/net/dev content
#
# Last change : 20090507
#

import re
import time
import thread
import getopt
import signal
import sys
#from subprocess import Popen, PIPE, STDOUT
from subprocess import *

# TODO print not refreshing correctly

# tx[0] are tx_bytes
# tx[1] are tx_packets
def get_tx_from_tcpdump(interface, tx):
    command = Popen(['tcpdump', '-n', '-e', '-p', '-l', '-v', '-i',
                     interface], stdout=PIPE, stderr=PIPE,
                     bufsize=1) # line buffering, optimizes a lot
    while 1:
        line = command.stdout.readline()
        if not line:
            # time.sleep(1)
            continue
        # Extract the nnn from the ", length nnn)" part of the line
        bytes_pattern = re.search('length (\d+)', line)

        if bytes_pattern:
            tx[0] += int(bytes_pattern.group(1))
            tx[1] += 1
        else:
            # ARP packet or other output... could be 28 + 14, but just ignore
            bytes = 0

        # Don't wait
        #time.sleep(1)

# tx[0] are tx_bytes
# tx[1] are tx_packets
def get_tx_from_proc(interface, tx):
    wrap = 2**32
    # Get the initial values
    try:
        tx_bytes_prev, tx_packets_prev = read_proc_tx(interface)
    except:
        return None
    # Main loop to update tx data values
    while(1):
        tx_bytes, tx_packets = read_proc_tx(interface)
        # Get the difference wrt the previous poll
        tx_bytes_diff = tx_bytes - tx_bytes_prev
        tx_packets_diff = tx_packets - tx_packets_prev
        # Check for an eventual wrap and re-ajust
        if tx_bytes_diff < 0:
            tx_bytes_diff = (wrap - (tx[0] % wrap)) + tx_bytes
            print "*** Bytes wrap! (from %s to %s)" % (tx_bytes_prev, tx_bytes)
        if tx_packets_diff < 0:
            tx_packets_diff = (wrap - (tx[1] % wrap)) + tx_packets
        # Update our counters
        tx[0] += tx_bytes_diff
        tx[1] += tx_packets_diff
        tx_bytes_prev = tx_bytes
        tx_packets_prev = tx_packets
        # Wait
        time.sleep(1)

# Return an array of tx[bytes, packets]
def read_proc_tx(interface):
    f = open('/proc/net/dev')
    for line in f:
        values = line.split(":")
        i = values[0].replace(' ', '')
        if interface == i:
            tx = [int(values[1].split()[8]), int(values[1].split()[9])]
            f.close()
            return tx
    f.close()

# tx[0] are tx_bytes
# tx[1] are tx_packets
def get_tx_from_ethtool(interface, tx):
    # Get the initial values
    try:
        tx_bytes_prev, tx_packets_prev = read_ethtool_tx(interface)
    except:
        return None
    # Main loop to update tx data values
    while(1):
        tx_bytes, tx_packets = read_ethtool_tx(interface)
        # Get the difference wrt the previous poll
        tx_bytes_diff = tx_bytes - tx_bytes_prev
        tx_packets_diff = tx_packets - tx_packets_prev
        # Update our counters
        tx[0] += tx_bytes_diff
        tx[1] += tx_packets_diff
        tx_bytes_prev = tx_bytes
        tx_packets_prev = tx_packets
        # Wait
        time.sleep(1)

# Return an array of tx[bytes, packets]
def read_ethtool_tx(interface):
    #f = call(["ethtool -S", interface])
    f = Popen(["ethtool", "-S", interface], stdout=PIPE).communicate()[0]
    #f = `ethtool -S eth0`
    bytes_pattern = re.search('tx_bytes\: (\d+)', f)
    packets_pattern = re.search('tx_packets\: (\d+)', f)
    if bytes_pattern is None or packets_pattern is None:
        return [0, 0]
    tx = [int(bytes_pattern.group(1)), int(packets_pattern.group(1))]
    return tx

def signal_handler(signum, frame):
    sys.exit(0)

def main(interface):
    signal.signal(signal.SIGINT, signal_handler)

    tx_tcpdump = [0, 0]
    tx_proc = [0, 0]
    tx_ethtool = [0, 0]

    thread.start_new_thread(get_tx_from_tcpdump, (interface, tx_tcpdump))
    thread.start_new_thread(get_tx_from_proc, (interface, tx_proc))
    thread.start_new_thread(get_tx_from_ethtool, (interface, tx_ethtool))

    while 1:
        tcpdump_bytes = tx_tcpdump[0]
        tcpdump_packets = tx_tcpdump[1]
        proc_bytes = tx_proc[0]
        proc_packets = tx_proc[1]
        ethtool_bytes = tx_ethtool[0]
        ethtool_packets = tx_ethtool[1]

        s = "TCPDUMP: %d (%d packets)\nPROC:    %d (%d packets)\nETHTOOL: %d (%d packets)" % (
                tcpdump_bytes, tcpdump_packets, proc_bytes, proc_packets, ethtool_bytes, ethtool_packets )
        print s
        time.sleep(1)

def usage():
    print "Usage: monitor -i <interface> (e.g. eth0)"

if __name__ == "__main__":
    interface = None
    ip = None
    opts, args = getopt.getopt(sys.argv[1:], "hi:", ["help"])
    for o, a in opts:
        if o == '-i':
            interface = a
        elif o in ['-h', '--help']:
            usage()
            sys.exit()
    if not interface:
        usage()
        sys.exit()

    main(interface)


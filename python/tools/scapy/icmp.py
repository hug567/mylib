#!/usr/bin/python3

import os
import sys
import scapy.all as scapy
from scapy.error import *
from scapy.utils import *
from scapy.packet import *
from scapy.compat import *
from scapy.fields import *
from scapy.layers.l2 import *
from scapy.layers.inet import *

src_mac = "70:b3:d5:20:00:23"
dst_mac = "70:b3:d5:20:00:21"
eth = Ether(src=src_mac, dst=dst_mac)

src_ip = "10.42.10.23"
dst_ip = "10.42.10.21"
ip = IP(src=src_ip, dst=dst_ip)

icmp_id = 1234
icmp_seq = 5678
icmp_data_len = 56
icmp_data = "A" * icmp_data_len
icmp = ICMP(id=icmp_id, seq=icmp_seq) / icmp_data

packet = eth / ip / icmp
sendp(packet, iface='eth0')

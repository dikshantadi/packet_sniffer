# Berkeley packet filter (BPF)

The Berkeley Packet Filter (BPF; also BSD Packet Filter, classic BPF or cBPF) is a network tap mechanism and packet filter which permits computer network packets to be captured and filtered at the operating system level. 

The filter program is in the form of instructions for a virtual machine, which are interpreted, or compiled into machine code by a just-in-time (JIT) mechanism and executed, in the kernel.

Simply speaking, it is a mechanism that allows us to specify which packets we are interested in before our program processes them. 

Without a filter, our packet analyzer receives every packet visible on the selected network interface:

```
Network Interface
        │
        ▼
     libpcap
        │
        ▼
   Every Packet
        │
        ▼
 Packet Analyzer

```
This works, but it is not very practical. A normal computer can generate a large amount of network traffic, and most of those packets may not be relevant to what we are currently trying to analyze.

Therefore with BPF we can filter the traffic before it reaches our packet parser:

```
Network Interface
        │
        ▼
     libpcap
        │
        ▼
    BPF Filter
        │
        ├────────── Matching packets ──────────► Packet Analyzer
        │
        └────────── Non-matching packets
                         │
                         ▼
                       Discard

```
## BPF Expressions 
libpcap allows us to write filters using a human-readable filter expression.

#### Filter by protocol 

`` tcp `` -> To capture Tcp packets 

`` udp `` -> To capture UDP packets 

`` icmp `` -> IPV4 icmp packet

``icmp6`` -> IP6 icmp 

``ip`` -> Ipv4 packet

``ip6`` -> Ipv6 packet

#### Combine conditions

`` ip6 and tcp `` -> Capture packets that are ipv6 AND TCP 

`` tcp or udp`` -> Capture packet that are TCP OR UDP

`` not arp `` -> Capture everything except ARP packet

#### Filter by ports as well

`` tcp port 443 `` -> Capture TCP packet using Port 443 (HTTP)

`` udp port 53 `` -> Capture UDP packet using port 53 (DNS)

`` tcp src port 443 `` -> Capture TCP packets where the source port is 443

`` tcp dst port 443 `` -> Same for destination port 

This can be useful when we want to distinguish between traffic going to a service and traffic coming from it.

#### Filter by host 

BPF can also filter packets based on IP addresses.

`` host 192.168.1.10 `` -> Capture packets going to or coming from 192.168.1.10

`` src host 192.168.1.10 `` -> Capture packets where the source IP is 192.168.1.10

`` dst host 192.168.1.10 `` -> Destination ip is 192.168.1.10

Similarly we use IPv6 address for IPv6 

`` host 2001:db8::1 ``

#### Combining all these 

`` tcp and host 192.168.1.10 and port 443 `` -> Capture TCP traffic involving 192.168.1.10 on port 443

`` ip6 and tcp and dst port 443 `` -> Capture IPv6 TCP packets going to port 443. 

#### Filtering by network 

`` net 192.168.1.0/24 `` -> Capture packets going to or coming from the 192.168.1.0/24 network.

`` dst net 192.168.1.0/24 `` -> Capture packets going to that network

## Example 

```
dikshya@dikshya-Nitro-AN515-56:~/packet$ sudo ./packet-analyzer 
Packet Analyzer
================
1. wlp0s20f3
2. any
3. lo
4. enp45s0
5. bluetooth0
6. bluetooth-monitor
7. nflog
8. nfqueue
9. dbus-system
10. dbus-session
Successfully opened: wlp0s20f3
Enter BPF Filter (press Enter for none): ip6 and tcp
Filter applied: ip6 and tcp

Packet 1
========================
Captured length: 132 bytes
Original length: 132 bytes
Destination MAC: d8:b0:20:a1:09:60
Source MAC: 10:3d:1c:ca:f7:92
EtherType: 0x86dd
========================
IPv6 packet
Version: 6
Traffic Class: 0
Flow Label: 292636
Payload Length: 78 bytes
Next Header: 6
Hop Limit: 64
Source IP: 2400:1a00:4b87:fd1a:8a2d:ba29:ce6b:d5f3
Destination IP: 2a04:4e42:19::347
========================
TCP packet 
Source Port : 59124 
Destination port : 443 
Sequence no: 1547032983 
Acknowledgement Number : 2896541330 
Data Offset: 8 (32-bit words)
TCP Header Length: 32 bytes
Flags:
  URG: 0
  ACK: 1
  PSH: 1
  RST: 0
  SYN: 0
  FIN: 0
window size : 64
Checksum : 60243
Urgent Pointer : 0
TCP Options Length: 12 bytes
  NOP
  NOP
  Option Kind: 8, Length: 10
Timestamp Option 
 TSval : 3193810950 
 TSecr : 2327114051 
======================== 


```
EtherType = 0x86DD

indicates IPv6, and:

Next Header = 6

indicates TCP.

This is exactly what we asked BPF for:

```
Network Interface
        │
        ▼
     libpcap
        │
        ▼
 BPF: "ip6 and tcp"
        │
        ▼
   IPv6 + TCP
        │
        ▼
 Packet Analyzer
        │
        ├── Ethernet
        ├── IPv6
        ├── TCP
        └── TCP Options

```

## Why filtering?

Before adding BPF, our analyzer essentially had to process everything visible on the interface.

After adding BPF, we can tell our analyzer exactly what kind of traffic we want to examine.

This is especially useful as the analyzer becomes more complicated. As we add more protocol parsers and eventually packet statistics, processing unnecessary packets would only create more work.


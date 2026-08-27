## User Datagram Protocol (UDP)

After the Internet Protocol layer, we encounter the Transport Layer. User Datagram Protocol (UDP) is one of the main transport-layer protocols used for communication between applications.

Unlike TCP, UDP is connectionless and does not provide mechanisms such as retransmission, sequencing, or flow control. This makes UDP lightweight and useful for applications where low overhead and speed are important.

### What is UDP?

UDP provides a simple way for applications to send datagrams between hosts over an IP network.

For example, DNS commonly uses UDP for its queries.

## UDP Header

A UDP datagram has a very small header: 

```
┌────────────────────┬────────────────────┐ 
│ Source Port        │ Destination Port   │ ├────────────────────┼────────────────────┤ 
│ Length             │ Checksum           │ 
├────────────────────┴────────────────────┤ 
│ Data                                    │ 
└─────────────────────────────────────────┘
The UDP header is only 8 bytes long.
```
### Fields 
 ``- Source and Destination Port — identify the communicating applications``

 ``- Length — The Length field specifies the total length of the UDP datagram. It includes both: UDP Header + UDP Data``

 `` - Checksum - To detect Error ``

 Example

Here is an IPv6 UDP packet captured by our parser:

```
IPv6 packet
Version: 6
Traffic Class: 0
Flow Label: 587960
Payload Length: 51 bytes
Next Header: 17
Hop Limit: 64
Source IP: 2400:1a00:4b83:9c17:41da:6760:121d:d3f6
Destination IP: 2400:1a00:8000:4::73
========================
UDP packet
Source Port: 39515
Destination Port: 53
Length: 51 bytes
Checksum: 0x73a5
========================
```
Here:

Next Header = 17

tells our IPv6 parser that the payload contains UDP.

Our parser then passes the data after the 40-byte IPv6 header to the UDP parser.

The UDP parser extracts:

Source Port
Destination Port
Length
Checksum
 
 ### TCP vs UDP 
 A simple way to distinguish the two transport protocols is:
```
TCP
├── Connection-oriented
├── Reliable delivery
├── Ordered byte stream
├── Flow control
├── Retransmissions
└── Larger header

UDP
├── Connectionless
├── No retransmission
├── No ordering
├── No flow control
├── Datagram-based
└── 8-byte header
```

### How Our Sniffer Parses UDP

```
Captured Packet
      │
      ▼
  Ethernet
      │
      ▼
   IPv4 / IPv6
      │
      ├── IPv4 Protocol = 17
      │
      └── IPv6 Next Header = 17
                │
                ▼
               UDP
                │
                ├── Source Port
                ├── Destination Port
                ├── Length
                └── Checksum
                
```
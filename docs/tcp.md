# Transmission Control Protocol (TCP)

After the Internet Protocol layer, we encounter the Transport Layer. One of the most important transport-layer protocols is Transmission Control Protocol (TCP).

## What is TCP?
The Transmission Control Protocol (TCP) is one of the main protocols of the Internet protocol suite, providing reliable, ordered, and error-checked delivery of a stream of octets (bytes) between applications running on hosts communicating via an IP network.

Example in IPv4 packet 

```
IPV4 packet! 
Version: 4
IHL: 5
Time to Live : 64
Total Length : 52
Identification : 33917
Flag 
DF: 1
Mf : 0
Fragment Offset : 0
Protocol: 6
Checksum: 0xde91
Source IP: 192.168.1.68
Destination IP: 34.107.243.93
======================== 
TCP packet 
Source Port : 41150 
Destination port : 443 
Sequence no: 2827708253 
Acknowledgement Number : 1210519417 
Data Offset: 8 (32-bit words)
TCP Header Length: 32 bytes
Flags:
  URG: 0
  ACK: 1
  PSH: 0
  RST: 0
  SYN: 0
  FIN: 0
window size : 63
Checksum : 55259
Urgent Pointer : 0
TCP Options Length: 12 bytes
  NOP
  NOP
  Option Kind: 8, Length: 10
Timestamp Option 
 TSval : 51525788 
 TSecr : 2887859295 
======================== 

```
Here, the IPv4 Protocol field is 6, which tells us that the payload contains a TCP segment.

Our parser therefore passes the data after the IPv4 header to the TCP parser.

```
192.168.1.68:36462
        │
        │ TCP
        ▼
140.82.113.26:443

Here:

Source Port      = 36462
Destination Port = 443

443 is commonly used for HTTPS
```

## TCP Header 

A TCP segment begins with a TCP header.

```
┌────────────────────┬────────────────────┐
│    Source Port     │  Destination Port  │
├────────────────────┴────────────────────┤
│             Sequence Number             │
├─────────────────────────────────────────┤
│          Acknowledgment Number          │
├────────┬──────┬─────────────────────────┤
│ Data   │ Res. │         Flags           │
│ Offset │      │                         │
├────────┴──────┴─────────────────────────┤
│             Window Size                 │
├────────────────────┬────────────────────┤
│      Checksum      │   Urgent Pointer   │
├────────────────────┴────────────────────┤
│          Options (optional)             │
├─────────────────────────────────────────┤
│                  Data                   │
└─────────────────────────────────────────┘

```
The minimum TCP header is 20 bytes and can be up to 60 bytes
when TCP options are present.

### Important Fields

- Source/Destination Port — identify the communicating applications.
- Sequence Number — tracks bytes in the TCP stream.
- Acknowledgment Number — indicates the next byte expected.
- Data Offset — specifies the TCP header length.
- Flags — control connection state and data handling.
- Window Size — used for TCP flow control.
- Checksum — detects corruption.
- Urgent Pointer — used with the URG flag.
- Options — provide additional TCP capabilities.

## TCP Flags

Our parser currently decodes:

- SYN — connection establishment
- ACK — acknowledgment
- FIN — connection termination
- RST — connection reset
- PSH — push data toward the application
- URG — urgent-data mechanism

## TCP Three-Way Handshake

Before two hosts can exchange data using TCP, they first establish a connection using a process called the TCP Three-Way Handshake.

```
Client                         Server
  │                              │
  │────────── SYN ──────────────>│
  │                              │
  │<──────── SYN + ACK ──────────│
  │                              │
  │────────── ACK ──────────────>│
  │                              │
  │       Connection Established │

```
SYN — The client requests to establish a TCP connection and provides its initial sequence number.

SYN + ACK — The server acknowledges the client's request and sends its own initial sequence number.

ACK — The client acknowledges the server's sequence number. The connection is now established.

## TCP Options

Our parser currently recognizes:

#### EOL (End of Option List)
Marks the end of the TCP option list. It is mainly used when the remaining space in the options field does not contain any more options.

#### NOP (No-Operation) 
A one-byte padding option used primarily to align other TCP options properly.

#### MSS (Maximum Segment Size) 
Specifies the largest amount of TCP payload that a host is willing to receive in a single TCP segment. It is normally negotiated during connection establishment.

#### Window Scale 

Extends the effective TCP receive window beyond the original 16-bit Window Size field. This allows TCP to efficiently operate over high-bandwidth or high-latency networks.

#### SACK Permitted

Indicates that the TCP endpoint supports Selective Acknowledgment. It is exchanged during connection establishment.

#### SACK (Selective Acknowledgment) 
Allows a receiver to inform the sender about specific blocks of data that have already been received, making it possible to retransmit only missing data instead of retransmitting an entire range.

#### Timestamps 
Carries two timestamp values, TSval and TSecr. TCP timestamps can be used for more accurate RTT measurements and help TCP distinguish between old and new segments.

## How our sniffer works with TCP

```

Captured Packet
      │
      ▼
  Ethernet
      │
      │
      ▼
    IPv4/6
      │
      │ Protocol/Header = 6
      ▼
     TCP
      │
      ├── Ports
      ├── Sequence Number
      ├── Acknowledgment Number
      ├── Flags
      ├── Window
      ├── Checksum
      └── TCP Options

```
Continue Reading : [UDP](udp.md), [Ipv6](ipv6.md)
TOC : [Table of Content](index.md)
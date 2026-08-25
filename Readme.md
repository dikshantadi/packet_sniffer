# Packet Analyzer

A lightweight network packet analyzer written in **C** using **libpcap**.

The goal of this project is to understand how network protocols work at the byte level by capturing raw packets and manually dissecting their protocol headers instead of relying on high-level packet-parsing libraries.

## Progress

Progress and to do: 

* [x] List network interfaces
* [x] Open a network interface
* [x] Capture packets
* [x] Parse Ethernet headers
* [x] Parse IPv4 headers
* [x] Parse basic TCP headers
* [x] Parse UDP headers
* [x] Parse TCP options 
* [-] Parse IPv6 (In progress)
* [ ] Parse ARP
* [ ] Handle other Ethertype
* [ ] Extract TCP/UDP payload
* [ ] Handle Ipv4 Fragmentation
* [ ] Handle IPv6 Fragmentation
* [ ] Parse ICMP (both v4 and v6)
* [ ] Track TCP Connections
* [ ] Detect Retransmission
* [ ] Parse application-layer protocols
  * [ ] DNS
  * [ ] HTTP
* [ ] Add packet filtering
* [ ] Add packet statistics


## Current Architecture

```text
Current Architecture
                         Captured Packet
                               │
                               ▼
                           Ethernet
                               │
                         ┌─────┴─────┐
                         │ EtherType │
                         └─────┬─────┘
                               │
                    ┌──────────┴──────────┐
                    ▼                     ▼
                  IPv4                   IPv6
                    │                     │
              Protocol           Next Header
                    |
                    │                     │
              ┌─────┴─────┐         ┌─────┴─────┐
              ▼           ▼         ▼           ▼
             TCP         UDP       TCP         UDP
              │           │
              │           │
              └─────┬─────┘
                    ▼
          Application Protocol
```

## Currently Parsed

### Ethernet

* Destination MAC address
* Source MAC address
* EtherType

### IPv4

* Version
* Internet Header Length (IHL)
* Time To Live (TTL)
* Total Length
* Identification
* Flags
* Fragment Offset
* Protocol
* Header Checksum
* Source IP address
* Destination IP address

## IPv6
* Version
* Traffic Class
* Flow Label
* Payload Length
* Next Header
* Hop Limit
* Source IP address
* Destination IP address

### TCP

* Source Port
* Destination Port
* Sequence Number
* Acknowledgment Number
* Data Offset
* TCP Header Length
* TCP Flags
  * URG
  * ACK
  * PSH
  * RST
  * SYN
  * FIN
* Window Size
* Checksum
* Urgent Pointer

## TCP Options
* End of Option List (EOL)
* No-Operation (NOP)
* Maximum Segment Size (MSS)
* Window Scale
* SACK Permitted
* Selective Acknowledgment (SACK)
* Timestamps

## UDP
* Source Port
* Destination Port
* Checksum 
* Length

## Why IM I Building This?

This project is primarily a **Computer Networks learning project**.

The long-term goal is to build a small multi-layer protocol dissector capable of following a packet from the Ethernet frame all the way into application-layer protocols.

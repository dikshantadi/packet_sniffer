# Packet Analyzer

A lightweight network packet analyzer written in **C** using **libpcap**.

The goal of this project is to understand how network protocols work at the byte level by capturing raw packets and manually dissecting their protocol headers instead of relying on high-level packet-parsing libraries.

## Progress

* [x] List network interfaces
* [x] Open a network interface
* [x] Capture packets
* [x] Parse Ethernet headers
* [x] Parse IPv4 headers
* [x] Parse basic TCP headers
* [x] Parse UDP headers
* [.] Parse TCP options (To do next)
* [ ] Parse ICMP
* [ ] Parse IPv6
* [ ] Extract TCP/UDP payload
* [ ] Parse application-layer protocols
  * [ ] DNS
  * [ ] HTTP
* [ ] Add packet filtering
* [ ] Add packet statistics

## Current Architecture

```text
Captured Packet
      │
      ▼
  Ethernet
      │
      │ EtherType
      ▼
    IPv4
      │
      │ Protocol
      ├───────────────┐
      ▼               ▼
     TCP              UDP
      │
      │ Destination Port
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

## Why IM I Building This?

This project is primarily a **Data Communication and Networking learning project**.

The long-term goal is to build a small multi-layer protocol dissector capable of following a packet from the Ethernet frame all the way into application-layer protocols.

TCP is overpowered!!!!!!!!
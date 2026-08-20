# Packet Analyzer

A simple packet analyzer written in C using libpcap.

## Goals

- Learn C and low-level network programming
- Capture and analyze network packets
- Understand Ethernet, IP, TCP, and UDP protocols
- Understand System and Networking concepts

## Progress

- [x] List network interfaces
- [x] Open a network interface
- [x] Capture packets
- [x] Parse Ethernet headers
- [-] Parse IPv4 headers (on progress)
- [ ] Parse TCP/UDP headers
- [ ] Display packet information
- [ ] Add packet filtering
- [ ] Add packet statistics

## How it works


        Raw Packet
            │
            ▼
┌──────────────────────────────┐
│      Ethernet Header         │
├──────────────┬───────────────┤
│ Destination  │   6 bytes     │
│ MAC          │               │
├──────────────┼───────────────┤
│ Source MAC   │   6 bytes     │
├──────────────┼───────────────┤
│ EtherType    │   2 bytes     │
└──────────────┴───────────────┘
              │
              ▼
        EtherType = 0x0800 (ipv4)
              │
              ▼
         IPv4 Header 
              │
              ▼
            ......
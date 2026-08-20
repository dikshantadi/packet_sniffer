# Packet Analyzer

A simple packet analyzer written in C using libpcap.

## Goals

- Learn low-level network programming
- Capture and analyze network packets
- Understand Ethernet, IP, TCP, and UDP protocols
- Understand System and Networking concepts

## Progress

- [x] List network interfaces
- [x] Open a network interface
- [x] Capture packets
- [x] Parse Ethernet headers
- [x] Parse IPv4 headers 
- [.] Parse TCP/UDP headers (on progress)
- [ ] Display packet information
- [ ] Add packet filtering
- [ ] Add packet statistics

## How it works


        Raw Packet
            │ (parse)
            ▼
        Ethernet Header 
              │ (parse)
              ▼
        EtherType = 0x0800 (ipv4)
              │ (parse)
              ▼
         IPv4 Header 
              │ (parse)
              ▼
         TCP/UDP Header

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
- [-] Parse IPv4 headers (on progress)
- [ ] Parse TCP/UDP headers
- [ ] Display packet information
- [ ] Add packet filtering
- [ ] Add packet statistics

## How it works


        [Raw Packet] (https://en.wikipedia.org/wiki/Network_packet)
            │ (parse)
            ▼
        Ethernet Header <https://en.wikipedia.org/wiki/Ethernet_frame>
              │ (parse)
              ▼
        EtherType = 0x0800 (ipv4) <https://en.wikipedia.org/wiki/EtherType>
              │ (parse)
              ▼
         IPv4 Header <https://en.wikipedia.org/wiki/IPv4>
              │ (parse)
              ▼
         TCP/UDP Header <https://en.wikipedia.org/wiki/Transmission_Control_Protocol> 

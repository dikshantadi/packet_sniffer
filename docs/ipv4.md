# Internet Protocol Version 4 (IPv4)

After Ethernet next layer we encounter is Internet Protocol Layer (IP). 

IPv4, or Internet Protocol version 4, is one of the main protocols responsible for delivering packets between devices across interconnected networks.

Example in ethernet packet: 

``` text

Packet 6
========================
Captured length: 66 bytes
Original length: 66 bytes
Destination MAC: d8:b0:20:a1:09:60
Source MAC: 10:3d:1c:ca:f7:92
EtherType: 0x0800
========================

```
Here the ethertype 0x0800 says its an ipv4 packet.

## What is Ipv4?

IPv4 provides logical addressing and packet delivery between networks. Unlike a MAC address, which is mainly used for communication on the local link (eg LAN), an IPv4 address allows a device to be identified at the network layer across interconnected networks. 

For example:

192.168.1.68

This is an IPv4 address.

IPv4 addresses are 32 bits (4 bytes) long and are normally written as four decimal numbers separated by dots.

``` text
192 . 168 . 1 . 68 
8     8     8    8 = 32 bits
```
So simply , when your computer sends a packet to a server somewhere on the Internet, IPv4 provides the addressing information that allows routers to determine where that packet needs to go.

## IPv4 Header 

An IPv4 packet begins with an IPv4 header.

A simplified representation of the header looks like this:

``` text

IPv4 Header 
┌────────┬────────┬──────────────────────┐
│ Version│  IHL   │    DSCP / ECN        │
├────────┴────────┴──────────────────────┤
│             Total Length               │
├──────────────────────┬─────────────────┤
│    Identification    │ Flags │ Frag.   │
│                      │       │ Offset   │
├──────────┬───────────┴───────┴─────────┤
│   TTL    │ Protocol │ Header Checksum  │
├──────────┴──────────┴──────────────────┤
│           Source IP Address             │
├────────────────────────────────────────┤
│         Destination IP Address          │
├────────────────────────────────────────┤
│             Options (optional)          │
└────────────────────────────────────────┘
```
The minimum Ipv4 header is 20 bytes long. 

Here is what our program reads :

``` text
Packet 6
========================
Captured length: 66 bytes
Original length: 66 bytes
Destination MAC: d8:b0:20:a1:09:60
Source MAC: 10:3d:1c:ca:f7:92
EtherType: 0x0800
========================
IPV4 packet! 
Version: 4
IHL: 5
Time to Live : 64
Total Length : 52
Identification : 35125
Flag : 2
Fragment Offset : 0
Protocol: 6
Checksum: 0xf235
Source IP: 192.168.1.68
Destination IP: 140.82.113.26
======================== 

```
Ill explain important things here:

### **Internet Header Length (IHL)**
-> The Internet Header Length (IHL) tells us how long the IPv4 header is. 

It is measured in 32-bit words, rather than bytes. For example:

IHL = 5

5 × 4 bytes = 20 bytes

So an IHL of 5 mean Ipv4 header is minimum 20 bytes long.

**Why is this important?**

-> This is particularly important because we cannot simply assume that every IPv4 header is exactly 20 bytes. If options are present, the header becomes longer.
```
IHL = 5  → 20 bytes
IHL = 6  → 24 bytes
IHL = 7  → 28 bytes
...
```
### **Total Length**
-> The Total Length field tells us the size of the entire IPv4 packet.

This includes:

IPv4 Header + IPv4 Payload

### **Identification, Flags and Fragment Offset**
-> These fields are related to fragmentation. IPv4 packets can be divided into smaller pieces when they need to cross a network that cannot carry the entire packet at once.

The **Identification** field allows fragments belonging to the same original packet to be associated with one another.

The **Flags** field contains control information related to fragmentation.

The **Fragment** Offset tells us where a particular fragment belongs within the original packet.

We will see this in detail here [Ipv4 Fragmentation](ipv4_frag.md) if you want to. 

### **Time to Live (TTL)**
-> The Time To Live (TTL) field helps prevent packets from circulating around the Internet forever. Every time an IPv4 packet passes through a router, its TTL is reduced. If it reaches zero, the packet is discarded.

### **Protocol**
-> The Protocol field tells IPv4 what protocol is contained inside its payload. 

For example:
```
Protocol = 6   → TCP
Protocol = 17  → UDP
Protocol = 1   → ICMP
```
So our parser can use this field to decide what to parse next.

### **Checksum**
-> The checksum allows a receiver to detect certain errors in the header while the packet is being transmitted.

### **Source and Destination IP Addresses**
-> IPv4 contains two important 32-bit addresses:

Source IP
Destination IP

The source address identifies where the packet came from at the IP layer. The destination address identifies where the packet is going.

**Remember that these are not MAC addresses.**

A simplified way to think about the difference is:

``MAC address : Local-link communication, eg: Your pc communicating with router. ``

``IP address : Communication across networks Eg: Your pc sending packet to your friends pc who lives across the city. ``


Continue Reading: [IPv6](ipv6.md), [TCP](tcp.md), [UDP](udp.md), [ICMP](icmp.md).

TOC : [Table of Content](index.md)

## Ethernet / Data Link Layer

What Is Ethernet?

Ethernet is a family of networking technologies that defines the physical and data-link-layer specifications used for local area network (LAN) communication.

It is standardized under IEEE 802.3.

Ethernet uses baseband communication , meaning the communication medium is used to carry a signal representing the transmitted data rather than dividing the medium into separate frequency bands for different signals. For our packet analyzer, we will mostly work above this physical layer, so for now just know that ethernet doesnt modulate signals.  

At the data-link layer, Ethernet defines how data is organized into frames and how devices are identified on the local network using MAC addresses.

For our packet analyzer, this is where everything begins. But first lets see what is MAC Address 

## MAC Address

A MAC (Media Access Control) address is a link-layer address used to identify a network interface on a local network. A traditional Ethernet MAC address is 48 bits (6 bytes) long and is usually written as six hexadecimal values separated by colons: 

eg : d8:b0:20:a1:09:60

Each device has its own unique mac address, your mobiles mac address and your pc's mac are unique and different.

These addresses are used for communication on the local link. They are different from IP addresses, which are used at the network layer to identify hosts across interconnected networks. I guess thats all you need to know about it. 

## Ethernet Frames
``` text 
Ethernet Frame
┌──────────────┬──────────────┬──────────┬─────────────┐
│ Destination  │ Source       │ EtherType│   Payload   │
│ MAC          │ MAC          │          │             │
└──────────────┴──────────────┴──────────┴─────────────┘
``` 
The first three fields shown above make up the Ethernet header (ahem Ethernet II as its second version of ethernet we use):

When libpcap gives our program a captured Ethernet frame, the first bytes we encounter are part of the Ethernet header.

1. Destination MAC address - 6 bytes (Remember 1 byte = 8 bits, 8 0's or 1's)
2. Source MAC address - 6 byte 
3. EtherType - 2 byte 

Together, these fields occupy 14 bytes.

The remaining part is the Ethernet payload, which contains data belonging to a higher-layer protocol. For example, an IPv4 packet or an IPv6 packet can be carried inside an Ethernet frame.

Example of Ethernet Parsing done by our sniffer :

``` text 

Packet 1
========================
Captured length: 2782 bytes
Original length: 2782 bytes
Destination MAC: d8:b0:20:a1:09:60
Source MAC: 10:3d:1c:ca:f7:92
EtherType: 0x86dd
========================

``` 
At first glance, this is just a collection of hexadecimal values and numbers. But each one has a specific meaning. Lets start from the top 

1. Captured length : The length of Ethernet packet we captured.
2. Original length : The original length of Ethernet packet captured. 
3. Destination MAC : This identifies the link-layer destination of the frame.
4. Source MAC : This identifies the device that transmitted the frame on the local link.
5. EtherType: This is particularly important for our packet analyzer because it tells us what protocol is contained inside the Ethernet payload. Here 0x86DD means IPv6.

Therefore, after parsing the Ethernet header, our program knows that the next thing it should try to parse is an IPv6 packet:

``` text
Ethernet Frame 
    │
    │ EtherType = 0x86DD 
    |
    ↓   IPv6

```
This is the basic idea behind our protocol parser. We start with the Ethernet frame, examine its fields, determine what comes next, and then pass the appropriate portion of the packet to the next parser.







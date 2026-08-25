# Ipv4 Fragmentation

Example : 

``` text
Packet 5
========================
Captured length: 66 bytes
Original length: 66 bytes
Destination MAC: 10:3d:1c:ca:f7:92
Source MAC: d8:b0:20:a1:09:60
EtherType: 0x0800
========================
IPV4 packet! 
Version: 4
IHL: 5
Time to Live : 62
Total Length : 52
Identification : 35125
Flag : 2
Fragment Offset : 0
Protocol: 6
Checksum: 0x7d6b
Source IP: 140.82.113.26
Destination IP: 192.168.1.68

```
### **Identification**
-> If a large IPv4 packet needs to be split into multiple smaller pieces, all the pieces get the same Identification value.

example : 

``` text 
Original IPv4 packet
Identification = 35125
        │
        ├── Fragment 1 → ID 35125
        ├── Fragment 2 → ID 35125
        └── Fragment 3 → ID 35125 

```
here Identification = 35125 so this packet is identified by this value. 

### **Flag**
-> The IPv4 Flags field has three bits:

``` text
Bit:    0   1   2
       ─── ─── ───
        R   DF  MF

```
where 

R = Reserved — must be 0

DF = Don't Fragment

MF = More Fragments

so since Flag = 2, which is 010 in binary therefore

```text
R   DF  MF
0   1   0

```
This means to not fragment, The sender is telling routers:

"Do not fragment this IPv4 packet."

### **Fragment Offset**
-> This tells us where this fragment belongs within the original packet. The offset is measured in units of 8 bytes.

If Fragment Offset = 0, then this packet starts at the beginning of original datagram.

so here, 

```
Identification: 35125
Flags:          2 (DF)
Fragment Offset: 0
```
we can conclude:

This packet is not a fragment.

Why?

Because:

``
DF = 1,
Fragment Offset = 0
``

There is no fragmentation happening here.

### **Fragmented Packet**
-> A Fragmented packet might look like this : 

```
Fragment 1:
Identification: 35125
Flags:          1 (MF)
Fragment Offset: 0

Fragment 2:
Identification: 35125
Flags:          1 (MF)
Fragment Offset: 100

Fragment 3:
Identification: 35125
Flags:          0
Fragment Offset: 200
```

Identification stays the same, fragment offset changes. 

Read more : [Ipv6 Fragmentation](ipv6_frag)
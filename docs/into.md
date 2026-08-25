## 1. Introduction

So, what actually is a packet analyzer?

According to Wikipedia, a packet analyzer (also called a packet sniffer or network analyzer) is a computer program or hardware appliance that can analyze and log traffic passing over a computer network or part of a network.

That is an accurate description of what I am trying to build. However, my goal is not to sniff other people's packets for "fun." I started this project because I wanted to understand **communication networks** at a deeper level.

I had studied TCP/IP before, but most of my understanding was at the conceptual level, i.e. the theory level. I knew about the OSI model, TCP, UDP, IP, and how data moves from one layer to another, but I had never really looked at what was actually happening inside the bytes being transmitted over a network.

So I decided to build a packet analyzer in C using **libpcap**.

The idea is simple: capture packets from a network interface and then manually parse their headers to understand what each field actually represents. Instead of simply reading about TCP/IP, I wanted to see the protocols directly in the data traveling through a real network.

So, we are going to examine packets and see what information they carry, starting from the bottom and working our way up.

I'll try to make this article easy for most people to read and understand, with as little coding jargon as possible and more focus on the theory: **what is happening, why is it happening, and how do the different protocols work together?**

Remember the TCP/IP stack.

```text
Application (HTTP, FTP, SMTP, SSH,...)
    ↓
Transport (TCP, UDP)
    ↓
Network (IPv4 and IPv6, ICMP)
    ↓
Data Link (Ethernet, Wifi)
    ↓
Physical (Signals)
```

We are going to start at the bottom. Well above physical layer. 

When my program captures a packet, I don't immediately see "TCP" or "HTTPS." I see a sequence of bytes. The interesting part is figuring out how those bytes are structured and how one protocol tells us what the next protocol is.

We'll start with Ethernet, move into IPv4, then look at TCP and UDP, and eventually examine things like TCP options and packet payloads.

The goal isn't just to build a program that prints packet information.

The goal is to understand **what those bytes actually mean** and to **document them in simple language so everyone can understand and appreciate the ENGINEERING that humans are capable of.**

Because when you look at a packet as nothing more than a bunch of bytes, it is easy to forget what is actually happening underneath. Those bytes represent decades of research, engineering, mathematics, standards, and countless decisions that allow computers all over the world to communicate with each other.

They are what allow you to play Dota or Valorant at 12 AM with random people from all over the continent, talk to your cousin living halfway across the world with minimal delay, watch a video from a server thousands of kilometers away, and do countless other things that we now take for granted.

You get the point.

**Too much larp. Let's start.**

**Here are some things you need to know before going into the article.**

**Number Representation.**
``` text
1 bit = 0 or 1, 
1 byte = 8 bits
```

**NIC**
```text
NIC stands for Network Interface Card. It is the hardware that allows a computer to communicate over a network.

A NIC could be:

An Ethernet network card
A Wi-Fi adapter
A virtual network interface

Your computer can have multiple network interfaces. For example, you might have one interface for Wi-Fi, another for Ethernet, and several virtual interfaces created by the operating system.

When we capture packets, we choose a particular network interface to capture from.
```
**C**
```text
The packet analyzer is written in C.

I chose C because I want to understand what is happening at a relatively low level. When working with network packets, we are essentially dealing with sequences of bytes, memory addresses, structures, pointers, and binary data.

C gives us fairly direct access to these things without hiding too much of what is happening underneath.

You don't need to be an expert in C to understand this article...
```
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDLIBS = -lpcap

TARGET = packet-analyzer

SRC = src/main.c src/capture.c src/ethernet.c src/ipv4.c src/tcp.c src/udp.c src/tcp_options.c src/ipv6.c src/arp.c src/icmp.c src/icmp6.c src/ipv4_options.c src/ipv6_exthdr.c 

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDLIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)
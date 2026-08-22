CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDLIBS = -lpcap

TARGET = packet-analyzer

SRC = src/main.c src/capture.c src/ethernet.c src/ipv4.c src/tcp.c src/udp.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDLIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)
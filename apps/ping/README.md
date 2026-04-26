# Internet Protocol Tool Kit (ft_ping)

A low-level networking implementation of the `ping` command in C, focusing on raw socket manipulation, ICMP protocol encoding, and manual checksum computation.

## 🚀 Quick Start

To build and run the project:

```bash
# Compile everything (libs + app)
make

# Run the ping (requires root privileges for raw sockets)
sudo ./ft_ping google.com

# Run the test suite for the checksum logic
make test
```

## 🛠 Features Built

- **ICMP Engine**: 
  - Custom encoding/decoding of ICMP datagrams into 64-bit representations.
  - Manual implementation of the **Internet Checksum (RFC 1071)** with one's complement arithmetic.
- **Networking Library (`libnet`)**:
  - Raw socket management (`SOCK_RAW`).
  - DNS resolution using modern `getaddrinfo`.
  - IP Layer manipulation (TTL modification via `setsockopt`).
- **Application**: 
  - Modular architecture with dedicated parsing, packet building, and networking layers.
  - Support for `-v` (verbose) and `-?` (help) flags.

---

## 🔬 Technical Diagrams

### ICMP Echo Request Datagram
The ICMP header is the heart of the `ping` command. We treat it as a sequence of 16-bit words for checksum calculation.

```text
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|     Type (8)  |     Code (0)  |          Checksum             |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|           Identifier          |        Sequence Number        |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                             Payload                           |
|                      (Default: 56 bytes)                      |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

### IP Header & TTL Insertion
While we let the kernel build the IP header, we interact with it to set the **Time To Live (TTL)**.

```text
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|Version|  IHL  |Type of Service|          Total Length         |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|         Identification        |Flags|      Fragment Offset    |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|  TTL (Manual) |  Protocol (1) |         Header Checksum       | <--- TTL inserted here
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                       Source IP Address                       |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                    Destination IP Address                     |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|      ICMP Data (Header + Payload) ...                         |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

## 🏗 Project Architecture

- `libs/libicmp/`: Core ICMP logic (Checksum, Transcoding).
- `libs/libnet/`: Networking wrapper (Sockets, DNS, IP options).
- `apps/ping/`: Main application logic.

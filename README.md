# netpidtop ![CI](https://github.com/ztaous/netpidtop/workflows/CI/badge.svg) ![License](https://img.shields.io/badge/license-MIT-blue.svg)
netpidtop is a terminal-based network monitoring tool for Linux. It is used to display real-time network connections per process. 

For each active TCP connection, netpidtop displays the process name along with the local address, the remote address and the connection state (ESTABLISHED, LISTEN, etc.)

<img width="1010" height="599" alt="image" src="https://github.com/user-attachments/assets/b8026e96-aebe-493d-a70c-34f2dd7cd323" />

## How it works
netpidtop makes use of the `/proc/` directory in the Linux filesystem to gather network information about each process without using kernel modules or eBPF.

The general logic of the program can be summarized with the following steps: 

1. **Process Discovery**: Scan `/proc/[PID]/fd/` for socket file descriptors
2. **Network Parsing**: Read `/proc/net/tcp` for TCP connection data
3. **Inode Mapping**: Match socket inodes to processes
4. **Display**: Poll and update terminal UI in real-time

## Scope / Limitations
- Currently, the program only displays processes that have active TCP connections, meaning that network information is only pulled from `/proc/net/tcp`.
- Root access is also required for full visibility of all processes.

However, UDP connections are planned along with eBPF to track actual bandwith for each process. 

## Installation and Usage

### 1. Install Dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install build-essential libncurses-dev
```

**Fedora/RHEL:**
```bash
sudo dnf install gcc make ncurses-devel
```

**Arch Linux:**
```bash
sudo pacman -S base-devel ncurses
```

### 2. Clone and Build
```bash
git clone https://github.com/ztaous/netpidtop.git
cd netpidtop
make
```

### 3. Run
```bash
sudo ./netpidtop
```

> **Note:** Root privileges are required to read information from `/proc` for all processes.

## Development
This repo uses a Makefile build and a small CI pipeline (tests, sanitizers, formatting) to keep changes safe and reviewable. GitHub Actions is used for continuous integration. Each push or pull request runs:
- Unit tests
- Address/UndefinedBehavior sanitizers
- Code formatting checks
### Tests
Unit tests use the Unity framework and are run with :
```bash
make test
```
### Sanitizers
To catch memory bugs and undefined behaviour during test runs :
```bash
make sanitize
```
### Formatting
Formatting is done with clang-format.
To check the formatting :
```bash
make format-check
```
To apply formatting fixes :
```bash
make format
```

## Acknowledgments

- Inspired by htop and nethogs
- Built as a learning project for systems programming in C
- Thanks to the Linux kernel documentation for `/proc` filesystem details and TCP states




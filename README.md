# TorConnect
A C project that send any traffic throught Tor network proxies (Socks proxy)

# Project Overview

This project demonstrates how to route your connection through a Tor SOCKS proxy to anonymize your internet traffic. By doing this, your IP address is hidden from the server you are connecting to, as the Tor network acts as an intermediary between your machine and the destination server.

## Understanding Proxies

A **proxy** is an intermediary server that sits between the client (your computer) and the destination server. It forwards your requests to the server and then relays the server’s response back to you. Proxies help enhance privacy and security by hiding your real IP address.

There are generally two types of proxies:

1. **HTTP Proxies**: These proxies relay HTTP traffic, such as web browsing. They can be found online, either as public (free) proxies or private (paid) services. They are mainly used for accessing websites.
   exemple for public proxies: https://www.proxynova.com/proxy-server-list/
2. **SOCKS Proxies**: SOCKS proxies work at a lower level compared to HTTP proxies. They can handle different types of traffic, including TCP connections like email, FTP, and web traffic. The **Tor network** uses SOCKS proxies to anonymize connections.

## How the Project Works

In this project, we will:
1. Set up your machine as a **Tor client** that hosts a **SOCKS proxy service**.
2. Route traffic through the Tor network to protect your privacy.

## Setup Instructions

### Step 1: Install Tor

To begin, you'll need to install and configure Tor to act as a SOCKS proxy on your machine.

```bash
sudo apt install tor
```

### Step 2: Configure Tor

Next, you'll need to configure Tor to listen on a specific port for SOCKS traffic. To do this, open the Tor configuration file:

```bash
sudo nano /etc/tor/torrc
```

In the configuration file, find the line where the SOCKS port is defined and change it to your desired port (e.g., 4444):

SocksPort 127.0.0.1:4444

Step 3: Start the Tor Service

After configuring Tor, you can start the service to enable the SOCKS proxy on your machine. Run the following command to start the Tor service:

```bash

sudo service tor start
```

Now, your machine is acting as a Tor client and SOCKS proxy. You can route traffic through this proxy at 127.0.0.1:4444.
Understanding SOCKS v4

The project utilizes the SOCKS v4 protocol, which allows for two operations:

    CONNECT: Establishes a connection to the target server via the proxy.
    BIND: (Not used in this project)

For more details, you can refer to the SOCKS v4 RFC (RFC 1413), but for this project, we only care about the CONNECT operation.
link: https://www.openssh.com/txt/socks4.protocol

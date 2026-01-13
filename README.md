# 🌐 WAN Cloud Simulation - Assignment 2

## 🎥 Demonstration Video
[![Watch the WAN Cloud Simulation](https://img.shields.io/badge/▶-Watch_Video-blue?style=for-the-badge&logo=google-drive)](https://drive.google.com/file/d/1S6xu2TaUvpbyTmxOngeJ1WNqGFzVWHxN/view?usp=drivesdk)

**Direct Link**: https://drive.google.com/file/d/1S6xu2TaUvpbyTmxOngeJ1WNqGFzVWHxN/view?usp=drivesdk

*Click the badge above or the link to watch the simulation demonstration*

## 📊 Simulation Overview
This ns-3 simulation models a Wide Area Network (WAN) connecting a local client to a cloud server through a simulated internet connection.

### 🖥️ Network Architecture
Client                    Cloud Server
(192.168.1.1) ─────WAN───── (192.168.1.2)
│ 10 Mbps │
│ 5 ms latency │
└────UDP Echo Protocol─────┘

### ⚙️ Technical Specifications
| Parameter | Value |
|-----------|-------|
| **Nodes** | 2 (Client + Cloud Server) |
| **WAN Bandwidth** | 10 Mbps |
| **Latency** | 5 ms |
| **Protocol** | UDP Echo |
| **Packet Size** | 1024 bytes |
| **Number of Packets** | 5 |
| **Transmission Interval** | 1 second |
| **Simulation Duration** | 6 seconds |

## 📁 Project Structure
Assigment-2-project-wide-Area-Network/
├── wan-cloud.cc # Main simulation code
├── README.md # This documentation
└── simulation-results.txt # Output log 


## 🚀 How to Run the Simulation
```bash
# Navigate to ns-3 directory
cd ~/ns-3-dev

# Run the simulation
./ns3 run scratch/wan-cloud.cc

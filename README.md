# Disk Scheduling Simulator (C++ CLI)

This C++ command-line program simulates three classic disk scheduling algorithms:

- **FCFS** (First Come First Serve)
- **SCAN** (Elevator Algorithm)
- **C-SCAN** (Circular SCAN)

The simulator services a disk with a customizable number of cylinders (default: 5000) and allows manual or random input for cylinder requests.

---

## 📦 Features

- Interactive CLI input
- Supports custom disk size, request queue, and initial head position
- Calculates total head movement (seek time)
- Displays service order and total seek time

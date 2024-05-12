# Serial Commands

This Document outlines the standard format of ROS-Microcontroller communication.

## Format

All data will be sent as bytes in a key-value format. The key is the first two bytes with the value
being the next two bytes. We define the messages to always have the same length and order of key-value pairs.

We interpret the key as ASCII text containing 2 uppercase letters, and the value as a 16-bit integers (signed or unsigned).
The system recognizes positive speed values as "Normal" (Forward, Left) and negative values as "Reverse" (Backwards and Right)
0 is stop (obviously)

## Jetson to Microcontroller

12 bytes are sent in the following format:

| Key  | Value           | Description                                            |
| ---- | --------------- | ------------------------------------------------------ |
| `EN` | 0 or 1          | Whether the drive system is enabled or disabled.       |
| `FB` | -32767 to 32767 | Forward and backwards movement (representing -1 to 1). |
| `LR` | -32767 to 32767 | Left and right movement (representing -1 to 1).        |

Note: any corrupted movement data will result in a STOP command being issued. 
## Microcontroller to Jetson

100 bytes are sent in the following format:

| Key  | Value               | Description                                      |
| ---- | ------------------- | ------------------------------------------------ |
| `EN` | 0 or 1              | Whether the drive system is enabled or disabled. |
| `FL` | See specific format | Front left wheel info.                           |
| `CL` | See specific format | Center left wheel info.                          |
| `RL` | See specific format | Rear left wheel info.                            |
| `FR` | See specific format | Front right wheel info.                          |
| `CR` | See specific format | Center right wheel info.                         |
| `RR` | See specific format | Rear right wheel info.                           |

Each wheel is represented by 4 key-value pairs:

| Key  | Value           | Description                                      |
| ---- | --------------- | ------------------------------------------------ |
| `DP` | -32767 to 32767 | Desired power (representing -1 to 1).            |
| `AP` | -32767 to 32767 | Actual power (representing -1 to 1).             |
| `CR` | -32767 to 32767 | Current wheel RPM.                               |
| `CA` | 0 or 1          | Whether traction control is affecting the wheel. |

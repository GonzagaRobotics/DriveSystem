# Serial Commands

This Document outlines the standard format of ROS-Microcontroller communication.

## Format

All data will be sent as bytes in a key-value format. The key is the first two bytes with the value
being the next two bytes. We define the messages to always have the same length and order of key-value pairs.

We interpret the key as ASCII text, and the value as a 16-bit unsigned integer. Keys may not contain any
control characters, and may have a null first character (but the second character must be non-null).

## Jetson to Microcontroller

20 bytes are sent in the following format:

| Key   | Value  | Description                                      |
| ----- | ------ | ------------------------------------------------ |
| `EN`  | 0 or 1 | Whether the drive system is enabled or disabled. |
| `FW`  | 0-255  | Forward direction.                               |
| `BW`  | 0-255  | Backward direction.                              |
| `\0L` | 0-255  | Left direction.                                  |
| `\0R` | 0-255  | Right direction.                                 |

Note: If the forward value is non-zero, the backward value must be zero, and vice versa. The same applies to the left and right values. If both pairs are zero, the robot will stop.

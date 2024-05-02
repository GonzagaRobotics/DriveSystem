# Serial Commands
## Synopsis

This Document outlines the standard format of ROS-MicroController communication.
The system utilizes a specific number of bytes in each direction: ROS sends the controller 12 total bytes, While the controller sends 100 bytes. These numbers DO NOT CHANGE. (Makes the code easier :D)
The below is the standard scheme for formating your haxadecimcal properly.the byte pattern

### From ROS to the controller: 
| 00  | 00  | 00  | 00  | 00  | 00  |
| --- | --- | --- | --- | --- | --- |
|     |

## Important Tidbits
* The ID and status numbers can be a MAXIMUM of 2 digits. anymore and things WILL be ignored.
* Please use standard hexadecimal notation. The subsystem can't handle creative characters.
* Please limit the number of commands per second to 10. Thanks
* :D


## Command Subsystems


| Subsystem ID | Subsystem name | Subsystem Status | Status in english     |
| ------------ | -------------- | ---------------- | --------------------- |
| 0            | Drive System   | 0                | Drive System Disabled |
| 0            | Drive System   | 1                | Drive System Enabled  |


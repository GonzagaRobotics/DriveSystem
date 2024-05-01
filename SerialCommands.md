# Serial Commands
## Synopsis

This Document outlines the standard format of ROS-MicroController communication
The below is the standard scheme for formating your haxadecimcal properly.


| 0x                                    | 0                 | 0                 |
| ------------------------------------- | ----------------- | ----------------- |
| The standard starter. Dont change me! | The subsystem id. | Subsystem status. |

## Important Tidbits
* The ID and status numbers can be a MAXIMUM of 2 digits. anymore and things WILL be ignored.
* Please use standard hexadecimal notation. The subsystem can't handle creative characters.
* Please limit the number of commands per second to 10. Thanks


:D

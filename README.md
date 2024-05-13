# DriveSystem


## This program is a complete rewrite of the previous MicroROS drive system.


Version 1 "Rosemary"


Versioning Note: Some Versions may have a letter. This letter indicates who signed off the release last. "E" is Embedded, "C" for Compsci
Future Features:

* Individual Motor Control

* Inteligent Traction control
  
  * Realtime RPM/Power readouts from the motors back to the jetson

* Error Detection and correction

* Anything else the teams ask for.

This system is licenced under the MIT licence.

Compiling/Development Note: This software was developed utilizing the Microsoft Arduino extention for VSCODE.

DO NOT USE PlatformIO or any other "arduino" deployment system.

This code is designed to be easily workable by anyone with even a basic understanding of arduinos and micro controllers

DO NOT try to manipulate registers or use any assembly. There is NO NEED in this application to overcomplicate things with random register changes

DO experiment with the code! My skills are kinda rusty, and I love it when folks improve my mess.

DO use this!


Note: The ArduinoNano (Our Microcontroller) has 6 PWM Pins: 3, 5, 6, 9, 10, 11

See this document for information on specifics. [DriveSystem Protocol information](SerialCommands.md)

# TE3 - teensyExpression3

This is the third, and hopefully last, major iteration of
the teensyExpression/vGuitar rig design and implementation.

Please see the
[vGuitar System](https://github.com/phorton1/phorton1/blob/master/vGuitar/vGuitar.md)
for information regardind the system as a whole.

From a **software perspective**, this repo contains the source code
for the portion of the system that runs on a *teensy4.1* which handles the
"foot pedal" part of the system, as well as acting as the central coordinator
of communictions over serial ports and much of the USB Midi to the iPad.

It inherits the functionality of the previous TeensyExpression pedal AND
the previous teensyPiLooper programs, as well as adding new functionality.

- is a USB Midi Device (Midi Controller)
- handles the buttons, rotaries, and expression pedals
- has a TFT display device (possibly with touch capabilities)
- has an SD card for storing SongMachine (and possibly other) files
- is intimately aware of the Midi Protocols used by the FTP
- *may* include a USB Host Port for the FTP (Fishman Triple Play)
- *may* provide *FTP Spoofing* capabilities

It acts as the central communication hub for handling and routing
Serial Midi, Serial Debugging, and Serial File Management to the
other parts of the system.

- communicates via Serial Midi with the TE3_Audio device
- communicates via Serial Midi with the rPi Looper program
- communicates via USB Midi with the iPad
- communicates via USB or dedicated Serial Port with the console.pm program

From an **electronics perspective**, this repo contains **all** of the
kicad schematics and PCB layouts for the entire system.

From a **3D printing perspective**, this repo contains **all** of the
Fusion 360 designs, STL files, Prusa and Lightburn Projects, and gcode
files for building the foot pedal.


## Implementation Notes



## Please also see

[**TE3_audio**](https://github.com/phorton1/Arduino-TE3_audio)
The **USB Audio** device that also communicates with the rPi Looper
via I2s.

[**TE3_common**](https://github.com/phorton1/Arduino-libraries/TE3_commo)
Functionality and definitions common to the **TE3** and **TE3_audio** programs.

The [**circle-Looper**](https://github.com/phorton1/circle-prh-apps-Looper)
repo contains the source code for the **rPi Looper** application that runs
on a Raspberry Pi that is interfaced to this device.

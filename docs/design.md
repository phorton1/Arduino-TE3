# design.md - Using iRig2HD Audio device and external USB Hub

## Abandoning TE_hub (teensy SGTL5000, USB Audio and Midi)

Experiments with teensy 4.x USB Audio (and MIDI) proved it was
not a good choice going forward.

- the SGTL5000 I2S<->audio works ok and may still be in future designs, but ...
- there were noticable and regular glitches in USB Audiio OUT-->IN on both Win10 and the iPad
- certainly USB Midi and USB Audio on the teensy is not well supported and generates huge amounts
   of noise, so I would still need an external USB Hub for the FTP
- even with the glitches there were problems getting the USB Audio device to work on newer iPad,
   particularly that Tonestack refused to utilize it correctly, either stand-alone or in combination
   with AudioBus, although AudioBus did work reasonably well.
- I don't have enough lifetime left to try to debug teensy USB Audio and/or Midi problems
   particularly against a closed architecture like the iPad.

It just won't work for a pro-quality that I want.
So I'm back to the iRigHD2 as the USB Audio device, an external hub with the FTP.

The only sort of positive was that in playing with the SGTL5000 I believe it is probably
"good enough" to replace the Audio Injector Octo in the system with a fairly big
space savings and better form factor for incorporation into TE3.


## New components

Apart from the box, power supplies, connectors, buttonBoard PCBs, a rotary
controller PCB displays and their connectors, and the iRig2HD and external
USB hub, the power supplies, the main components are not considered:

- **SGTL5000** (teensy Audio Shield) replaces the Octo, accepts audio from
  the iRigHD2, sends it to the rPi Looper via I2S, gets the audio back
  from the Looper via I2S and sends it to analong (line out or headphone)
  outputs (to the PA).
- **rPi Zero 2W** - runs the Looper program, communicates with the SGTL5000
  via I2S, has a display device (connector), interfaces to the new
  TE3_central "controller" that integrates and dispatches Serial messages
  and data.
- **teensy 4.1** - replacing the teensy 3.6 largely (only) because the 3.6 is
  no longer being produced, and as a result, there are some lingering issues
  (particularly sdFat) that may still need to be addressed.  IS a USB midi
  device (that plugs into the external USB hub), has connectors for the
  buttonBoards, rotaryBoard, footPedals, and interfaces to the TE3_central
  device.  There is considerable work to do with entirely new approaches to
  polling the buttons and rotary board and testing.
- **ESP32** for TE3_central - replacing teensy 3.2 "teensyPiLooper". Plan is to use an
  ESP32 to provide more-or-less all the same functionality as before, but
  with the added ability to conceivably access and debug the footpedal
  via Wifi (Telnet and/or a WebUI).  The main, slighly scary thing is that
  the ESP32 only has 2 Serial ports in addition to its own USB Serial port,
  which is exactly what I need, but leaves no room for growth.  Also it is
  not clear that the Serial Ports are actually as quick as the teensy 3.2
  which *may* be an issue for things like rPi binary uploads.

I do need to think about those other parts too.

- **Power Supply** - The power supply will be an issue, esp adding the ESP32
  to the already power hungry rPi and charging the iPad over USBC.
  Considering requring a 12V USB input, or less likely an AC power
  input with my own power supply.
- **iRigHD2** - can I move the pots from the board?  One of them *may* pass
  an actual audio signal.  The LED is always an issue, but
  I think I will keep the 1/8 jack this time around and not have an
  input pad.
- **External** (USBA->USBC) **Hub**.  The one I have has three upwards
  facing USBA inputs. It remains to be seen if perhaps I can make them
  bottom mounted, or pull the pins off to a separate PCB for internal use.
  I was able to test it with an extension cord, and can succefully charge
  the iPad AND use the iRigHD2 6 feet away (where the teeensy Audio USB
  did not work as well).
  

## Integrated PCB and PCBs in general

For now I am going to think about making a custom, built in china,
PCB board that houses the ESP32, teensy4.1, and rPi. I'm thinking
that the SGTL may possibly be stacked on top of the rPi via another
custom "shield" PCB.

Might as well send in a design for the buttonBoards.

The rotaryBoard may be do-able single sided and home made.





# end of design.md

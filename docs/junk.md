# junk.md - scratchpad and transient idess

So much depends on the assumption that the teensy4 is not capable
of (doing a good job of) being a USB Audio, MIDI, and
Host device and simultanously presenting a UI over a TFT display
and/or servicing the buttons, rotaries, and exprssion pedals and=
sending out a WS2812b LED data stream.

But decoupling the UI from the USB MIDI port introduces a lot
of complexity, in an already complex system.

The new name for the previous  TE3_audio deviceis TE3_hub,
which sort of connotes that it is a congregating device and/or
a usb device, without really being specific about either.

This is so effing complicated.  I need separate documentation
that overlap on so many subjects.  Just with regards to MIDI,
which is an otherwise simple concept, I would need/like:

- basic MIDI protocol recap, as per specification
- my Serial MIDI over the wire
- FTP usage and limitations (i.e. not using it's volume control or buttons at all)
- FTP MIDI messages, and the whole command-reply scheme
- FTP Spoofing and how it works
- Specification of TE_Hub specific CODEC control and state
  (serial) Midi messages

Before I can succintly describe how MIDI message routing takes
place, especially since the rPi only has a single Serial port that
must intersperse debug output with MIDI messages.

- The circle-prh-bootloader does not need to look for
  (avoid) serial MIDI messages.  We can assume that the
  system will not be sending MIDI to the rPi while in
  the process of doing a binary upload.
- However, the TE teenyPiLooper replacement DOES need
  to know if it is in "rPi upload mode".







## TE_hub

At least at this time I don't RECEIVE and Midi data from
the iPad (which is too bad, meaning that I have to manually
normalize the names and positions of the sampleTank patches
into my rig configuration files) and is not necessarily an
assumption I like building into the system.  Other USB
clients may very well have synthesizers which CAN tell me
what patches exist.

**Is an iPad running sampleTank a requirement?**.

I don't like this being built into the system. Sheesh,
it gets complicated.  I would *like* to allow for other
client computers and other synthesizers, including actual
MIDI devices.  However it is difficult to be all things
to all people for all of the future and there is a
certain desire to create a simpler system.  Assuming
an iPad or other computer with a software synth like
sampleTank on it, driven by the USB Midi port, may not
be the end of the world.  I'm certainly not gonna add
actual MIDI ports that I will never, ever use, to the
system

In fact, some may consider that TE3's lack of actual
(or even serial) MIDI inputs and outputs is a bad thing.
For those folks, I leave it up to them to modify the
implementation, circuit boards, and software to their
heart's content.

Note that use of the confusingly named FTP "PolyMode",
which sends all notes over one channel if turned on,
or separate notes (and volume



Codec Issues

- needs to intercept and act on CODEC control messages
- needs to send identifable CODEC control state messages
- may need to be pollable for CODEC control state

FTP Issues

- needs to know to send FTP performance data to the USB port
- needs to have FTP sensitivity and tuning modes and know
  to send note and sensitivity data to the TE3 for the UI
- would be the home of the FTP Spoofer if one exists as
  it needs to control the USB Midi device names in order
  to do so.

MIDI Routing Issues

- may not be the best candidate for overall routing of
  MIDI messages due to it's lack of UI.
- otherwise it needs a whole set of "configuration"
  CC's, or worse yet, a MIDI Sysex setup approach that
  is also known by TE3.
- if so, then the MIDI routing configuration likely
  be stored in EEPROM.

**I need to start testing at least SOME of the basics
of all this stuff.**





Assume for a moment that, apart from intercepting CODEC controls
and FTP mode commands, that all Serial MIDI that comes into the TE_USB
gets forwarded to the USB Midi port.  At this time I dont RECEIVE
any MIDI from the iPad,


## My Serial MIDI protocol

Note that the Looper DOES NOT contain a fileServer.



Based on requirements:

- the Looper will be able to run a fileClient



To begin with it is important to understand that, as
currently implemented, my Serial MIDI protocol can
never be confused with normal Serial Text data and
has been carefully shoe-horned into the system to
allow magic to occur with my fileTransfer and rPi
BinaryUpload "modes" protocols within a serial stream
that otherwise contains debugging output.

Since the rPi only presents one serial port, the
problem shall remain.  Serial text to and from
the rPi must be able to disambiguate MIDI data
from all other text.   However, whichever device
is talking to the rPi can just *know* that it is
special.  The rPi (Looper) itself represents the
looper as a single MIDI channel with different
CCs for all functions.






There is currently a difference between the messages "on the wire" and
the messages in memory.  Messages in memory have a port encoded in the
high order nibble of the 0th byte and whether or not they are input
or output encoded as the (otherwise unsused by MIDI itself) high
order bit in the B2 byte.

	B0 byte = type | (port<4)
	B1 byte = (type<<4) | (channel - 1);
	B2 byte = (IS_OUTPUT << 7) | param1
	B3 byte = param2



My serial MIDI protocol allows for 7 different "Ports" (cables)
that comes in as the high nibble of the 1st byte of the message.
There is a (kludge) additional bit in memory only which specifies
whether it is an INPUT or OUTPUT message


	#define NUM_MIDI_PORTS      7
	#define MAX_MIDI_PORT		(NUM_MIDI_PORTS-1)
	#define MIDI_PORT_NUM_MASK  0xf0

	#define MIDI_PORT_USB1      0x00
	#define MIDI_PORT_USB2      0x10
	#define MIDI_PORT_USB3      0x20
	#define MIDI_PORT_USB4      0x30
	#define MIDI_PORT_HOST1     0x40
	#define MIDI_PORT_HOST2     0x50
	#define MIDI_PORT_SERIAL    0x60

	#define MIDI_OUTPUT_B2_FLAG  0x80
		// set into the high order bit of the B2 byte










+






# TE3_hub - the USB Audio, MIDI device and HOST for teensyExpression3

This device, based on a teensy 4.x, implements a USB Audio, Midi and
Serial interface along with a USB Midi Host port.

It uses the SGTL5000 teensy audioShield for analog Mic and Line inputs
and Headphone and Line outputs.  It communicates with the SGTL5000 via
I2S for configuration and control, and via I2S for digital audio
processing.

It interfaces to a rPi (the Looper) as an external audio DSP (digital
signal processsor) via a second (synchronous) I2S data stream.

It accepts Serial MIDI data over the Serial1 port.

It can direct (text) debugging output to the USB Serial0 port, the MIDI
Serial1 port, or a separate debug-only Serial3 port.

The SGTL5000 can be configured, controlled, and polled via Midi.

It is aware of knows how to work with a FTP (Fishman Triple Play)
dongle whether it is plugged into the HOST port or accessible via
the USB Midi port.  It *may* provide an FTP Spoofing feature to
debug and work with the FTP dongle in the HOST port using the FTP
configuration utilities running on a host (laptop) computer
connected to the USB Midi port.




## SGTL5000 (teensy AudioShield) initial implementation

In experiments 5 years ago I determined the the SGTL (henceforth
synonymous with SGTL5000 and the teensy AudioShield RevD) was too
noisy, which led to the iRigHD2 for USB Audio, and the whole architecure
of converting the resultant iRigHD2 analog audio back into digital
form with the Audio Injector Octo, with I2S for the Looper on the rPi,
and then finally back into analog again.

This not only added latency, but probably added noise.

Since then I have started thinking the noise was not so much an
inherent problem of the SGTL as it was that the SGTL was not properly
"tuned" for my application.  Impedences were not perfect, gains were
not perfect, eq and limiting were never tried, and so on.

I now think that, having eliminated a whole nuther round trip to analog,
I can tweak the SGTL and probably get "good enough" sound and better
overall latency than in the previous TEs.

However this is not a trivial task.  The SGTL has a LOT of potential
parameters that can be tweeked, AND there is no UI on this device.
I could write a test-only serial interface, but by then I've already
had to sort out the SGTL API.

Instead I think I will just START by implementing SGTL control over
serial midi, AS IF, its gonna work and a UI for it will exists someplace
in TE3.  Then I will implement a rudimentary UI elsewhere, perhaps in
TE3, perhaps via a web-browser if I move TE3 to an ESP32, or perhaps
in a dedicated copy of the current teensyPiLooper or equivilant
program.

## Test UI and current abhorent lack of progess

One way or the other I need to be able to adjust every parameter,
on the SGTL and to try the audio and get the best sound I can out of
the PA and see if I like it.  I also need test the latency of the HOST
port and see if (because I am no longer using a separate USB hub) it's
"good enough" to play the iPad synth with it (whereas it definitely
wasn't in previous TEs), and finally if the USB Audio is good enough
and throw in the looper and see if its good enough.

I can do all of that testing without writing the full TE3, buttons,
rotaries, foot pedals, etc, but issues like connectors, putting
breadboards on the floor next to the PA so I can test them, may
mean that I want to build a "test box" with some kind of prototype
TE3. Dunno.  it might be best to just build the whole effing thing
and then decide.

I HAVE to do something.  I have a nice breadboarded version
that could test most of it, probably well enough.  The control,
configuration, and UI are the issues.




## MIDI

MIDI is a simple, yet complicated beast. Conceptualized at its most basic
level, it is a series of 3 byte messages where the first byte contains a
channel number 1..16 (one based), and a 'command' or 'message type' in
the other four bits, and the other two bytes are parameters for that message
type.

USB_MIDI wraps that with an additional leading 0th byte which designates
a "cable number" from 0..15 "cable" and which typically duplicates the
'type' nibble from the inner MIDI message (the type from the 1st byte).

My Serial MIDI protocol is, essentially, conceptually, the same as the
USB_MIDI format.  Nice thing about these 4 byte MIDI messages is they
fit into a single uint32_t.  The reality gets complicated, though.

(1) When Serial MIDI must be embedded in a stream that might otherwise
contain regular printable (debugging or other) text.  In this
case my Serial Midi convention is that the "cable number" must be
zero, taking advantage of the fact that the common text character
codes under between 0x00 and 0x0f, that is the characters, tab (0x08),
carriage return (0x0D), and linefeed (0xOA), don't map to common
Midi command "types", and so we can detect a Midi message, even in
the middle of a text stream, and gobble those four bytes out separately.

(2) The SGTL must be configurable via Serial MIDI.  Fortunately, the
Serial Midi IN to this device will never contain plain text, so the
Cable Number (full USB Midi messages) can be sent.  This will enable
us to dedicate a "Cable Number" (and not just a channel number) for
identifying messages intened for configuration of the SGTL5000, while
still being able to appropriately "pass through" Serial MIDI to the
USB port, without undue confusion about where it came from or is
intended to go.

(3) The FTP presents special challenges due to it's hogging of channel
numbers and presentation a two different Midi ports (cables). Fortunately,
once again, the teensy can provide all 16 "Cables" to/from the USB
which *should* allow us to use (high) cable numbers to diffentiate
and route messages properly, esp since the attached computer never
actually NEEDS to see 16 cables (ports).  Four has been plenty in
the past, and 8 would probably be overkill.  Nonetheless this is a
complicated situation and robust documentation and comments will be
needed to keep it all sorted out.






## FTP

This device needs to handle the "state" of the FTP as needed for
Tuning and Senstivity adjustments, and needs to route and/or copy
certain FTP messages (i.e. note_on) to the TE3 for it's UI to
work with.

It needs to do this stuff whether the FTP is plugged into the HOST
port, or whether it is accessible via the USB port (i.e. this device
is subsequently plugged into a USB Hub which also has the FTP plugged
into it).

Additional complexity is added by the fact that if the FTP is plugged
into the host, not all of the FTP messages (those specific to to FTP
tuning and sensitivity adjustments, as well as some uneeded, yet
heavily sent performance data) need to be sent out the USB port.

Finally, an additional layer of complexity exists if I want to
try to (re) implement the "FTP Spoofing" feature of previous TE's.
Spoofing the FTP from the HOST port so that the teensy looks like
an FTP and works within the Win64 FTP configuration program, requires
that the USB ports have certain names, and numbers, in a certain
order.





## Please also see

[**TE3**](https://github.com/phorton1/Arduino-TE3)
The parent **Foot Pedal** device that houses and interfaces
with this device.

The [**circle-Looper**](https://github.com/phorton1/circle-prh-apps-Looper)
repo contains the source code for the *Looper application* that runs
on a Raspberry Pi that is interfaced to this device.




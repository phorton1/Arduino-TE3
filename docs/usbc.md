# USBC PD Experiments


## USBC Power Experiments

OK, so I have proven I can use a *USBC Decoy Board* to get 5-20V from
a hefty 65W USBC power supply, use 15V to power a *65W USBC Charger Module*
and connect that to the power input on a *Powered USBC Hub* and, at least
*power the iPad* from the Hub (even through a USB extension cable).

In separate tests I have proven that the given USBC Hub can transmit
and receive *USB Audio* and *TE and FTP Midi Data* to and from the
*iPad* (to/from AudioBus, SampleTank, and Tonestack).

So now I have disassembled the **USBC Hub**, and need to connect it to the
**Charger Module**.  I obviously don't want to use (the tested) 3 foot long
USBC cable, since these will be inches from each other in a potential
**Looper3** box.

I did not see any 3" or less USBC power deliver cables on eBay. The smallest
USBC cables I did see were 1ft, still too big for my liking.

### What I have

I have some *USBC breakout boards* that are intended, apparently, to convert
the USBC to USB3A using fixed resistors to deliver 5V at (?) 500-3000ma.

I don't have any male USBC plugs or breakout boards.  The only thing I do have
are several (now useless) USBC to Lightning cables.

- USBC inline power meter/tester
- USBC female (to USB3) breakout boards
- USBC decoy board modified with jumpers for voltages
- USBC (cut) to Lightning USBC cable.
- 30W USBC Power Supply Dongle
- 65W USBC Power Supply for laptops
- iPad (currently de-charge) as a test sink
- various USBC and USBC extension cables


### Test1 - Baseline 15V proof of concept

- USBC 30W PSU to
- Black USBC Extension to
- USBC Power Meter to
- Black USBC Cable to
- Decoy Board jumpered for 15V to
- Volt Meter

Result: 15V showing on USBC Meter and Voltmeter

**Conclusion:** essentially, I am trying to replace the black
USBC cable with a small cable made from ends cut from
USBC-Lightning or other junk USBC cables.


### Test2 - cut white USBC-Lignthing exploration

- Cut white Ankler USBC-Lightning Cable to
- Red USBC Breakout board


In this test I want to check continuity and resistances
from the ends of the cut cable to the USBC Breakout board.

The cable has the following ends (black and red are heavier guage):

Continuity Test

- aluminum foil shield
  appears to be plastic coated on outside
  when I got a good connection I could find nothing attached to it

- black == GND
- red == VBUS
- white == CC1/2 depending on orientation of plug
- yellow == D+
- green == D-

Resistance Test

The has "512" resistors from CC1 and CC2 to ground,
and I measured 5.1K from CCx to ground.

**Conclusion:** I am guessing the cable is
straight thru - that the 5 wires are directly
mapped, with no internal logic or resistors,
to the GND, VBUS, D-, D+, an CCx pins on the
USBC connector.  If so, it may be simple to
construct a cable from two ends.

I also have a lot of USBC->USBA cables.


### Test3 - cut old Plastic USBC-USBA cable

- Cut white old USBC-USBA Cable to
- Red USBC Breakout board

This one has a braided shield outside an aluminum shield,
a nylon twine inside, and no yellow.  I suspect that the
white is D+, and there is no CCx pin presented on this
cable


- shield - presents as the SS casing on the USBC connector
- black - connected to shield, SS casing, and ground pin
- red - present as 39 ohm to VUSB; I suspect the cable is munged
- green - presents as D+ on breakout
- white - presents as D- on breakout


**Conclusion:** This cable is mnged, and even if it wasn't
it would be uselss for me because it does not present CCx pin.



### Test4 - cut cream colored brand new braided USBC-USBA cable

- Cut cream colored USBC-USBA Cable to
- Red USBC Breakout board

Unshielded, only 4 wires (B,R,G,W)

**Conclusion:** probably same as Test3, there is no CCx pin
presented, so these USBC-USBA cables are useless to me.

I have a very limited supply of USBC cables.

Double checking Ebay.

I disassembled the USBC connector.  As suspected
there are GND, VUSB, D-, and D+ wires.  It looks
like some tiny reistors on CCx lines,

When facing BOTTOM UP (with the GND, VUSB, D-, and D+ pins on the bottom),
and the connector to the right (red board to left), there are two resistors
labelled R2 and R1.  The "inside pads" of those resistors appear to be connected
to CC1 and CC2 respectively. The resistors measure 30.2K.  The outsides of the sistors
are connected to VBUS (they are pullups), not pulldowns like I expected.

I believe I can (a) remove the resistors, solder the red and black from
the white lightning USBC cable to VBUS and GND, and connect the white
to the inside of either resistor (but probably not both) to effect a
power cable.


### Test4 - hand made 3 wire cable

So, using the deconstructed connector, and the cut USBC-Lightning
cable, I did as said, soldering the Red, Black, and White from
the cable to the VBUS, VGND, and soldering the white (via a
small additional wire) to the "inside" of the R1 resistor.

IT WORKED!

So now I know I can make, and don't need to buy the short
2" USBC-USBC cable to go from the 65W charger to the USBC hub!!

It's a SHAME however that you cannot buy generic USBC connectors.

They are either like the ones in the USBC-USBA converters, with
pre-soldered resistors and NO CC1 CC2 connectors, or they are
$8 a set for a female and male pair (when the others are like
10 for two bucks).   I think it is because the mfr of the "good"
ones only sells them by the 1000's and all the USBC-USBA ones are
now getting old and available as surplus.

For my project I will deconstruct some other cables, sigh.


## USBC Hub Experiments

Now that I have a little more familiarity with USBC PD and the
cables and connectors, I think I *may* be able to get rid of
the *Powered USBC Hub* (that I now have four of), and replace
it with a much smaller, and more adaptable **USB2.0 Hub module**
that I've had laying around for 3 years, and which is still
available on ebay.

Essentially I will create my own USBC powered hub.

- the **USB2.0 Hub module** will provide four
  USB 2.0 480Mbps 4pin 5V ports via standard 2.0mm JST sockets
- use a **red USBC breakout board** to have a single female
  USBC connector to the host device (iPad/laptop)
- use the **65W USBC Charger module** to provide the
  VBUS and CCx pins to the USBC host port.

In asmuch as I have 3 of these USB 2.0 modules, and 4-5
of the red USBC breakout boards and 2-4 of the USBC 65W
chargers (and can get more of any of these currently on ebay),
I can afford to do this as an isolated experimental PCB,
although, particularly due to the need for a 5V buck
converter, I'd like to make this all part of the motherboard.


*Note that as of this epiphany, **if I get rid of the
rotary controls and board**, and use **PCB mounted
1/4" jacks** for the foot pedals and guitar, and
**PCB mounted RCA jacks** for the audio output and
a **PCB mounted 1/8" jack** for the debug serial IO,,
I can eliminate **many wire connectors**, particularly
simplifying the **back panel construction***.


I made a schematic showing the test setup.
There are only two questiona of significance,
but it should not blow anything up if I get
either or both of them wrong.


(a) There are 5.1K pulldowns on the red USBC female
    connector board.  Do I need to remove them?
(b) We are only running CC1 from the 65W charger
    to the red USBC female board.  That was all
	we supplied to the USBC hub, but is that sufficient
	to BE a USBC Hub?

We will find out!


### Initial Somewhat Disappointing and difficult results

I did a marathon session for over 24 hours straight, reaching
the limits of exhaustion trying to get things working.
The simplest description is that the iPad sucks, and
all of my experiments that worked well on win10 laptops
utterly failed with the iPad.   As of this writing I
am **so** close, and yet, still no cigar.

I *probably* munged one of the orange USBC breakout
boards, and I *may have* munged on my three USB2 hub
boards.

There is a bit to remember before I can continue with my
next phase of analysis.

The main problem is that I don't have a good USCB male
connector breakout board, and it is a bit difficult to
describe in a text document the circuits I made, tried,
and how each attempt failed, or partially succeded.

### Basic Parts

My first test was to solder a bunch of things up *as if*
I know what I'm doing and *as if* it would all work.

In order from least dodgy to most dodgy, I had the following

- A **perf board module** I created using the **USBC decoy board**
  I modified to allow me to use jumpers to select the voltage,
  along with a **Mini 360 buck-down converter** to provide 5V.
  This module has a bunch of pins for ground, the output voltage
  from the decoy module, a jumper to allow me to connect the
  buck converter to the decoy module voltage, with pins for the
  5V/GND output from the buck converter.  It went through an
  iteration as I added more pins all over the place to allow
  me to monitor, as well as tap, the power outputs.

- To the **USB2 hub** I added four pins for the *upstream*
  (main) port, and on one of the four downstream ports I
  soldered four nice 24 guage silicon wires to a **USB Micro
  connector* so that I could plug it into the TE3 to get
  MIDI and Serial USB devices through the hub.

- Added two pins for power input to the smaller of the two
  kinds of **65W USBC Charger Module* that I have.
  I am currently using the one with a greay plastic
  220 inductor instead of the one with the exposed copper
  wire inductor.

- I removed the two 5.1K pulldown resistors on CC1/CC2
  from one of the **orange USBC connector** break out boards

I am condensing some of the processes I went through for
brevity, but will try to retain the salient points of the
discussion.


### Configuration One - Soldered orange USBC breakout board

Using the orange breakout board with the resistors removed

- USBC 30W Power supply Dongle to
- Input of USBC Decoy board, jumpered to 20V
- Buck Converter adjusted to 5.15V or so
- Output of Decoy board, via dupont wires, to
  65W USBC charger
- Output of Buck converter to GND and VBUS on
  the USB2 hub
- the micro USB cable from the port3 of the USB
  hub plugged into the TE3 teensy 4.1

At this point, I thought, all I needed to do is
bring the GND, VBUS, and CC1 from the 65W charger
module, along with GND and D-/D+ from the USB2 hub,
to the orange USBC connector breakout.

So I desoldered the 3 wire USBC connector that I
created after digging it out of the braided cable,
from the 5 wire cable/connector that I cut off the
end of the USBC-Lightning cable, and used that
to connect the 65W charger to the orange breakout.

I used soldered dupont wires to the organge breakout
D-/D+ pins to run them to the USB2 hub.  My only
concern was that the GND from the USB2 hub had to
go back through the perf board module in order to
connect to the orange breakout through the 65W
charger.

I verified that ALL of these modules have common
grounds, that is to say, that the inputs and outputs
of the buck, 65W charger, and USB2 hub are all
connected on GND.  Nonetheless I added a separate
(additional) dupont wire to conect the orange breakout
board GND to the USB2 hub.

So I soldered this up:

	-----------------
    | 3 Wire USBC   |
	| connector     |
	| dug out and   |
	| created from  |
	| braided USBC  |
	| cable         |
	|               |
	| VBUS  CC1 GND |				dupont female ends
	-----------------               to USB2 hub
		|	 |	 |
		|	 |	 +----------------------> GND
		|	 |	 |	  +-----------------> D+
		|	 |	 |	  |    +------------> D-
		|	 |   |    |    |
	---------------------------------
	| VBUS  CC1 GND   D+   D-   CC2	|
	|                               |
	| orange USBC breakout bostd    |
	| pins not shown in order       |
	---------------------------------

I hooked everyting up and then tried every USBC
cable and USBC device I with the circut.

I will leave out the **panics** when I got **voltage
surge messages** on my super important main laptop,
or the fact that I once ran 20V directly into the
USBC input on my *Artisan rPi 4B+* as, although they
were super scary and I thought I munged some of my
most important devices, thank goodness whoever designed
those things watched out for guys like me, and as far
as I can tell no permanent damage was done.  I had
to reboot the Lenovo after the power surges to clear
some kind of an internal state.


Also, the tests described below is not an exhaustive
list, nor are they in the actual order I performed them
but are merely the most poignant memories from my
24+ hour session and the most important results
going forward.


### Test1 - basic USB2 hub on Laptop

In reality this was like the 5th or 6th test, but
I should get it out of the way to note that the
USB2 hub works ok.

To prove this I cut a brand new (though old) USBA
to USB-mini cable and put a four pin JST connector
on the end that maps to the four pins on the USB2
hub - GND, D+, D-, and VBUS (5V).

With just the TE3 connected to the USB2 hub,
I plugged the hub into the laptop with the USBA
connector.  The TE3 showed up in device manager,
presenting the USB Serial as COM3, and I could
see the MIDI device and all of its ports.

I opened a console to COM3 and was able to type
commands and send them to the TE3 and see the
TE3 debugging output, for example, when I press
buttons on the prototype button boards.

I'm certain I could program the TE3 through the hub.


### Test2 - TE3 directly to iPad via adapter

Once again, completly out of order, but important.

I have some USBC-USBMicro adapaters, and
was able to connect the iPad directly to the TE3

- iPad to standard USBC cable
- USBC cable to USBC-USBMicro adapater
- USBC-USBMicro adapatr plugged into TE3

Although I did not bother to modify the TE3
software to actually send any Midi Data, I
did verify that when I plugged this in, and
ran **MidiFire** on the iPad, that the TE3
midi devices showed up.

I *believe* that the iPad also showed the
**blue USB device connected** icon at the
top right next to the charge indicator.

This last note is a curious one because
sometime that blue indicator doesn't show
BUT the midi devices still become active
in MidiFire.   In fact it *rarely* shows
and I am not taking it as necessity that
it does, as long as I get USB midi devices,
I **assume** I will also get the USB Audio
device from similarly hooking up TE3_Audio
to the hub.

### Test3 - USB2 Hub directly to iPad

This took some wonking around and didn't actually
occur until much later when I modified the orange
breakout board to have breadboard pins rather than
being soldered to directly.

This requires a 5.1K pulldown from CC1 to ground.
I only have 4.7K resistors, but they work.

However, once done, with the orange breakout board
on a breadboard and dupont wires merely connecting
GND, D+, D-, and VBUS from the hub to the breakout
board, plugging a USBC cable between the iPad and
breakoiut board allowed the TE3 midi devices to show
up in MidiFire (though no blue iPad USB connected msg).

The iPad powers the hub at5V which powers the TE3.
The power levels are small.


### Test0 - PD to the iPad

This was actually the first test I ran, after
hooking up the soldered orange board.  And it
may not have worked the first time, but after
some jiggling and cursing.

With the above **soldered orange breakout board**,
basically, the iPad accepts 12V at upto 3A.

In generaly I put the USBC power meter in the
circuit wherever it is easiest and it has never
been a problem, as it shows me the power being
transfered, in which direction, and at what voltage.

I labelled all my USBC cables arbitrarily with
one side being "1" and the other "2".

- I'm not sure why its not 15V.  I have seen 15V
  go to the iPad before.
- The USBC plug into the orange breakout (and/or
  the meter) only works in one orientation, depending
  on whether the CC from the Charger is set into
  the orange breakout CC1 or CC2.

In otherwords, the side that plugs into the breakout
(charger) must correspond to the CC that is chosen
for the charger on the breakout.  The other side,
that goes into the iPad, can be reversed, but the
charger exhibits "sided-ness* and must be plugged
in a certain way.

I was able to resolve that by running the Charger's
CC to BOTH of the orange breakout CCs, but thats
an advanced topic for the next section.

### Results of this test phase

NO MATTER WHAT I DO I CANNOT GET THE IPAD TO
ACCEPT PD AND SEE THE USB2 HUB and TE3 at
the same time.

VERY, VERY, VERY frustrating.

Especially since it basically always works on the
Win10 laptops.  My main Lenovo doesn't have a USBC
port, but using a USBC-USBA cable I was able to
plug the (solderd) breakout into the laptop and
see the TE3 and talk to it using the console.

With a small Lenovo laptop I have that does have
a USBC port, I was able not only to see the TE3
and talk to it, but the PD was delivering 12V at
over 2A (26 watts) to the laptop, although the
laptop complained that it was a "slow charger",
inasmuch as it expects 65W, probably at 20V,
IT WORKED.

But not, of course, the effing iPad.


### Conclusion of this phase - change everyhing to jumpers

Some of the above tests did not happen until this phase.

But at some point I felt I needed to be able to play
with the pullup and pulldown resistors on the breakout
boards.  At first I tried resoldering the tiny 5.1K
resistors I had taken off, and thats one of the times
I got the PANIC POWER SURGE on the laptop.  I messed
around for several hours trying to solder resistors
onto the breakout board, and perhaps munged it in the
process.

The long and short of it that instead of soldering
things directly to the breakout, I decided to solder
a 6 pin header on it and put it on a breadboard for
experiments.

So I made sure everything was "pinnable"

- I desoldered the 3 wire USB connector and added
  a crimped JST-3 female header to it
- I added a crimped JST-5 female header to the
  cut end of the USBC Lightning cable.

After wiring up a breadboard and using 4" dupont
cables, IT FAILED to deliver power to the iPad,
appearing to **boot loop** the Charger about once
per second.

When I finally took the 4" dupont wires out of
the equation by sticking a long double ended
4 pin jumper into the breadboard, and rethreading
the JST5 connector on the USBC cable stub to
match the pinouts of the breakout board, AND
soldering pins to a new (green) breakout board
(with the resistors removed), it started charging
again.


## Phase3 - where I am at this morning

I now am using the 5 pin cable stub from
the charger directly to the breadboard,
and a brand new green breakout board with
no resistors.

So in this configuration the CC from the
Charger goes to CC1 on the breakout board.

If I put a 4.7K resistor from GND to CC2
on the breakout board, at least for a while
I got the following results:


- If the USBC cable to the iPad is plugged
  in with the "1" side up, the iPad sees
  the Hub and TE3, but does not charge.
- If the USBC cable is plugged in with the
  "2" side up, the iPad charges at 12V/2A,
  but does not see the USB Hub or TE3.

I wrote all this down so that I could continue
testing and remember where I was.


### Test 1 - reverify above

Actually the impetus for writing this is that
it **stopped** working like described above and
I began digressing through various configurations,
and before I do so, I need to start taking notes.

So, here we go.  Test1 is

- 30W power supply to
- decoy set to 20V on perf board
- jumper powering 5V buck on perf
- hub (always) plugged into TE3
- charger powered by 20V out from decoy
- hub powered by 5V out from buck

with the following details:

- white 5 pin cable stub to breadboard
- GND, D-, and D+ from hub to breadboard
- hub VBUS pin sidelined on breadboard
- 4.7K resistor from GND to CC2 on breadboard


#### After powering up decoy

- decoy shows blue light
- TE3 shows booting and alive
- no light on Charger
- no display on USBC Meter

I will now plug the iPad in

- USBC cable in "1" position
  - blue light on charger turns on
  - meter shows 5.285V with no current flowing
  - iPad Midifire sees TE3,
  - no iPad battery lightning bolt
  - no blue iPad USB connected indicator
  
- USBC cable in "2" position:
  - iPad beeps and shows battery lightning bolt
  - blue light on charger turns on
  - meter shows 11.60V at 2.4A for 28.3W
  - MidiFire does NOT see TE3

BTW - the 65W charger gets HOT at 28W!!


### Digression Test1 - try red breakout again

Now that I have a fairly stable situation, before
trying to solve the "final" problem, I want to take
some time to see if I really *munged* things or not.

First I will now try to merely swap out the new green
breakout board for the red one I though I previously
munged.

IT WORKS FINE.  The board was not the problem.
The 4" dupont wires were the problem.


### Digression Test2 - try *munged* USB2 hub again

There is not room to put 2.0mm JST4 connectors on
the top of the USB2 boards, but there are no lights
or other thngs that require me to use/see the top
of the board.

So I am going to turn the USB board over and
plug it into the breadboard.  This will allow
me to eliminate dupont wires between the hub
and USBC breakout and to power it via the main
4 pin connector rather than the ancilariy 2pin
connector.  In order to get it to fit, I have
to remove the 2pin power connector I soldered
onto it.

2nd hub WORKS FINE upside down on breadboard


Solder up a new USB-Micro to 2.0 JST4.
I've never made one of the small connectors,
wonder if I have, and can use, the crimp pins.

I have 4 pin wired connectors, though the wires
are not silicon, a bit large, and the colors are
wrong (no green, use white for D- instead).

Crimping the connectors is a bit difficult.
Use the 2ND SLOT in the crimp tool and make
sure the connector is LOW in the space, and
only do ONE CLICK.  Make sure the wire end
is short (1.5mm or so) and that the crimp
catches the silicon wire cover. Crimp then
solder.  Weave then insert into JST connect.

It's probably a good idea to secure the JST
ends with hot glue (as I do the USB ends)
because those plugs are difficult to get
out of the JST sockets and it is easy to
damage the wires by pulling on them.

THE 1st USB HUB APPEARS TO WORK OK!!
It was apparently not munged!




## Continuing iPad USBC exploration

Why can I charge the iPad OR get data, but not both?
And how do I fix it?

I have a suspicion that it has nothing to do with
resistors or which CC line is used, and rather,
that there is something in the binary PD protocol,
as emitted by the Charger that tells the iPad

"I am a Charger.  I don't do data."

If so, the problem is probably nearly insurmountable,
short of making my own USBC PD hub.

So now I attempt to learn about the binary PD protocol
and why the iPad might accept a charge, but not data
from my setup, wheras it accepts both from the store
bought powered USB hub.

*Note: I can plug my setup into the store bought
hub and the iPad will both charge and recieve data
through the nested hubs.*


Sigh, my initial readings of various TI and USBC
committee PDF's indicates that, indeed, the PD
protocol includes bits to define whether the device
can communicate USB data, and it is very likely that
the power supply I am using does not send those bits,
whereas the store bought hub does.

It will be exceedingly complicated to create my own
USBC hub.

I have to think about this, and why I am doing it.

## Why Am I Doing This

- The store bought USB hub is very large
- the attached USB cable is bogus to my design
  which should just attach to the iPad with a
  standard USBC cable.
- The USB3.0 (USB2 is all I need) ports don't have
  pin layouts that map to JST connectors. The inner
  two pins are 2.0mm apart, wherase the outer two
  pins appear to be 2.54 mm from those.
- I will still need a separate way to power the
  rPi2W because I need all three USB ports
  for TE3, TE3-Audio, and the FTP, AND (b) the
  rpi2W takes more power than the USB hub outputs
  (not confirmed but it wouldn't boot a rPi4B
  from one of those ports).
- Therefore I'm gonna have a buck converter,
- I'll likely still need the 65W charger module
  to power the hub (regarldess if I take a 20V
  barrel jack in, or a USBC decoy board in).

Whereas, with the smaller USB2 hub

- I have USB connectors and capabilities in a
  very small space.
- it uses standard 2.0mm spacing for JST connectors.
- Would be practical to mount or plug into the
  mother board.

In essence the USB2 hub setup is smaller and
takes advantage of the charger/buck I will likely
have anyways.


## Taking apart the newer store bought USBC hub

Nonetheless I need to revisit it.  Perhaps I can
make my own USBC female connector in lieu of the
bulky and hard to manage fixed USB male cable,
and/or get 5V somehow for the rPi.

							Breakout
Cable Analysis				Up					Down

Front Side
	Purple
	Orange
	Black (shield)			GND					GND
	Yellow
	Blue

Back Side
	White					D-					D-
	Green					D+                  D+
	Black (wire)			GND                 GND
	Brn						CC2					CC1
	Red						VBUS				VBUS



I get no readings from front side (purple, orange, yellow, blue),
which indicates to me that the female connectors are "usb3.1" and
the high speed (RX/TX +/- and SBU) 1/2 pins are not hooked up

### Disconnected Small Red Female Connector Analysis

I found a spec for a 16 pin female connector at
https://www.jae.com/en/topics/detail/id=92529, but
it does not appear to match the connector on the red
boards. As much as I try to get my head around it,
it appears to be reversed top-to-bottom from the actual
connector on the board, and I cannot find another diagram
that makes any sense that shows the pins I am getting
with the breakout boards.


The housing is not connected to ground.

Note that the spec counts the doubled GND and VBUS as two pins
each and call this a 16 pin connector, but what I see are 12 pins
with bigger ones for the GND and VBUS

Looking down from top with RECEPTACLE POINTED LEFT AND PINS POINTED RIGHT.
Whatever side is up on the male plug is considered the "A" row, and "B"
is always on the underside.  The male plug is invertably symetrical.

Since all the GND and VBUS pins are strapped together, we only see them
on the breakout board as two pins
Since the two sides of D- and D+ are strapped together on the breakout
board, we do not see them as four separate pins, but rather only as two,.


spec		see		breakout	not broke out
1			1		GND
2					GND
3			2		VBUS
4					VBUS
5			3					SBU2	the SBU on the bottom
6			4			CC1				the CC on the top
7			5			D-
8			6			D+
9			7			D-
10			8			D+
11			9					SBU1	ths SBU on the top
12			10			CC2				the CC on the bottom
13					VBUS
14			11		VBUS
15					GND
16			12		GND


One must remember that the receptacle and male are
ordered oppositly, and so, for instance, with the
male facing right (pins facing left) A1 is at the
bottom.


### Duh Analysis

In the final analysis, the USBC hub brings out

- GND				black and shield
- VBUS			    big red
- one CC line		brown
- D-				white
- D+				green

And it brings out one pair of high speed data channels
that are DEFINITLEY not presented on the breakout and
that are PROBABLY not used by the iPad anyways,
CERTAINLY since I am only hosting USB2 devices.

- purple
- orange
- yellow
- blue

The only other question is the dangling small red,
which I'm guessing is the other unused CC line.


## CONCLUSION

I have finally decided to just use the store bought USBC hub
with some modifications.

- **USBC power input** - created a USBC stub cable with a 6 pin JST
  connector that matches the pins on the USBC breakout boards
  - VBUS == 22ga red
  - GND  == 22ga black
  - CC1  == 24ga blue
  - CC2  == 24ga yellow
- **USBC power and data to iPad** - soldered wires from
  the bottom of the USB hub to a 5 pin JST connnector that matches
  the pins on the USBC breakout board:
  - D-   == 22ga green
  - D+   == 22ga yellow
  - GND  == 24ga black
  - CC1  == 22ga white
  - VBUS == 24ga red

I am only using higher quality, fine strand, tinned, silicon wires
in the TE3 project.

On the iPad output side, I found that if I merely connect CC1 to
CC2, the USBC cable works in either orientation!

SO NOW I HAVE A POWERED HUB that can (a) fit in the box, (b) have
a decent pair of rear-facing USBC female plugs, and (c) work in
any cable orientation.

The iPad charges at 15V upto about 2.5A, or 26W or so.
The hub does not seem to get unduly hot.

I have verified that I can take 5V to power the rPi from the USBC
hub by drilling some holes and mounting a 2 pin JST connector or
cable that terminates in a 2 pin JST connector.

I merely have to solve the issue of how I connect the USB2 ports
for TE3, TE3_audio, and the FTP.  I am still trying to figure out
how to retrofit a 4 pin JST connector of some kind for that, but
may have to solder cables to the board cuz of the non-standard
pin layouts.




# TE3 - Making the PCBs (Printed Circuit Boards)

<!--standard_doc_header-->
**[Home](readme.md)** --
**Pcbs** --
**[Solder](solder.md)** --
**[Parts](parts.md)** --
**[Build](build.md)** --
**[Overview](overview.md)** --
**[Design](design.md)** --
**[Implement](implement.md)** --
**[Details](details.md)** --
**[User](user.md)** --
**[Songs](songs.md)**


All of the printed circuit boards for the initial version of TE3
were milled using my [cnc3018](https://github.com/phorton1/Arduino-esp32_cnc3018)
cnc machine.You can find all of the **kicad schematics** and **pcb designs**, as well
as the **flatcam projects** and **gcode files** that I actually used to mill
and laser the below pcbs in the */docs/kicad* folder of this repo.


[![images/pcbs-main_circuit_boards.jpg](images/pcbs-main_circuit_boards.jpg)](images/pcbs-main_circuit_boards_big.jpg)

Clockwise from the bottom left are the **mother_board**, five (5) **row_boards**, the **rotary_board**, two (2) **lcd_connector**
boards, and the **led_board**. Not shown are the three (3) **usba_connectors** that I made after this photo.

Each board typically goes through a multi-step process:

- mount a copper blank pcb on the machine with two sided tape
- put a pointy engraving bit in the machine
- mill the isolation routing into the copper blank

[![images/pcbs-milling.jpg](images/pcbs-milling.jpg)](images/pcbs-milling_big.jpg)

- clean with a toothbrush and fine sandpaper
- inspect the isolation routing, test with continuity meter, and make
  fixes with an exacto knife, repeating the toothbrush and fine sanding,
  as needed.

Here is a detailed photo of one of the row boards before sanding, cleaning, and testing.
You can see the burrs on the milled edges and see how they might create problems if not cleaned up.

[![images/pcbs-inspect.jpg](images/pcbs-inspect.jpg)](images/pcbs-inspect_big.jpg)

Once certain that the isolation routing is *good enough* to continue, then

- change the machine head from a spindle to a UV laser and align the laser
- add masking tape and coat the board evently a with thin coat of green UV expoxy (easier said than done!)
- expose the UV epoxy with the UV laser on the cnc machine

The laser is setup in *flatcam* to **paint** the PCB with the laser using
0.5mm spacing and a 0.2mm margin from the pads. It can take as long to expose
the epoxy as it does to do the isolation routine, as there are many lines that
have to be drawn to cover the whole board.  When this step is done,
the epoxy that has been exposed will harden, but the epoxy on the pads
will still be liquid and can be removed with a paper towel or q-tip.


[![images/pcbs-laser.jpg](images/pcbs-laser.jpg)](images/pcbs-laser_big.jpg)

- carefully remove the unexposed UV expoxy with little pieces of paper towel
  to reveal the copper pads
- getting the pads as clean as possible without messing up the exposed portions.
- if lucky, you can use a little alcohol on the pads themselves for the final cleanup
- then, shine a 15W UV light on the board for a few minutes to
  further harden the epoxy, before
- changing the machine head from the UV laser back to the spindle
  and making sure it's re-aligned correctly

[![images/pcbs-cutout.jpg](images/pcbs-cutout.jpg)](images/pcbs-cutout_big.jpg)

Then you can do the final steps to finish the PCB on the cnc machine:

- swap bits and drill holes with a 0.8mm drill bit
- swap bits and drill holes with a 0.9mm drill bit
- swap bits and mill connector holes with a 0.5mm end mill
- swap bits and mill mounting holes with a 1.9mm end mill
- cut out the board with the 1.9 end mill bit

After you remove the pcb from the cnc machine, it is a good idea to sand its edges
and corners to remove any sharp edges, and then to clean the pcb vigourously with a
toothbrush, soap and water

A small PCB can be made in 30-60 minutes.  A large complicated
one, like the TE3 **mother_board** can take 4,6, or more, hours to make.


## Mother Board

The **motherboard** was difficult to produce and is the first PCB I've
ever milled where I ran 0.6mm tracks, from the rPi, **between pins** on a standard
2.54mm header.  It took me 2 tries, after I completely *re-setup and reconfigured*
my cnc machine, to get the first one with decent isolation routing.

[![images/pcbs-mother_board_back.jpg](images/pcbs-mother_board_back.jpg)](images/pcbs-mother_board_back_big.jpg)

It took several hours of machine time just to **mill** the *isolation tracks*, test and fix any milling errors,
and several more hours to *coat* with, and *expose*, the **UV epoxy** with the **laser**.

[![images/pcbs-mother_board_front.jpg](images/pcbs-mother_board_front.jpg)](images/pcbs-mother_board_front_big.jpg)

With milling the slotted holes for the audio connectors, drilling two sizes of holes, cutting the mounting holes, and
cutting out the board, swapping bits each time and re-homing the Z axis, it took basically a full day to produce one.

Then after I produced the first one, I discovered that the dimensions I was using for the audio connectors was not correct
and they didn't fit! So I had to do another pass through the design, re-do the whole flatcam project to produce new gcode files,
and then mill and create an entire 2nd board before I got the one shown above that I felt would be good enough to proceed
to **soldering and actual testing**.


## Row Boards

The **row_boards** are some of the first pcbs that I have ever milled to make use of **SMT**
(Surface Mount Technology) components. Even though I am using **1206 capacitors** (1.2mm x 0.6mm)
and a SOP16 with **0.5mm pin spacing**, which are large by industry standards, they are currently
the finest detail pcbs I have ever milled, with **0.4mm tracks**.

Here is a photo of three of them:

[![images/pcbs-row_boards.jpg](images/pcbs-row_boards.jpg)](images/pcbs-row_boards_big.jpg)

I made 6 of them because TE3 uses 5 and I wanted to have a spare one.

The pins in the following image are 0.5mm apart with 0.4mm tracks!!

[![images/pcbs-row_board_detail.jpg](images/pcbs-row_board_detail.jpg)](images/pcbs-row_board_detail_big.jpg)

Compare the photo above, of a row board, complete with epoxy and drilled holes, with the freshly
milled board detail of the same section near the top of this page and you can see how much cleaner the
edges of the tracks and the isolation routing are after cleaning and sanding.

You can also see from the above photo that the solder pads are *not quite ready* for soldering.  Those little
smears of epoxy on the pads would cause problems and will need to be cleaned until
the pads are all **bright and shiny pure copper** before we actually solder anything to them.


## Rotary Board

The **rotary_board** uses standard **THD** (Thru Hole Devices) technology,
and was relatively simple to create.

[![images/pcbs-rotary_board_back.jpg](images/pcbs-rotary_board_back.jpg)](images/pcbs-rotary_board_back_big.jpg)

[![images/pcbs-rotary_board_front.jpg](images/pcbs-rotary_board_front.jpg)](images/pcbs-rotary_board_front_big.jpg)


## LCD Connectors

I used two **lcd_connectors** that I had previously created several years ago for the cnc machines.
The cnc machines made use of **orange** LCD touchscreens that use the same connectors as in TE3.

[![images/pcbs-lcd_connector_back.jpg](images/pcbs-lcd_connector_back.jpg)](images/pcbs-lcd_connector_back_big.jpg)



## LED Board

The LED board was a fun little board that uses **1206 SMT** (Surface Mount) LEDs and resistors.
The board in the photo below is less than 1x1 inch and holds seven (7) LEDS!

[![images/pcbs-led_board_back.jpg](images/pcbs-led_board_back.jpg)](images/pcbs-led_board_back_big.jpg)


## USBA Connectors

Due to a space restriction in the box I could not use standard USB connectors with the hub.  Standard
USB connectors were too tall and would not fit in the box.  So after some mulling about, I decided to
make my own **usba_connectors**.

[![images/pcbs-usba_milling.jpg](images/pcbs-usba_milling.jpg)](images/pcbs-usba_milling_big.jpg)

These connectors fit in a standard USBA female socket, like one you probably have on your computer or laptop,
and are designed so that I can pull the wires off at a right angle to minimize the overall size of the connector.

[![images/pcbs-usba_connector.jpg](images/pcbs-usba_connector.jpg)](images/pcbs-usba_connector_big.jpg)

As the exposed copper will tarnish quite quickly, resulting in bad connections, I was thinking about trying
to gold plate them (and I might still in the future), but to start with I coated the contact pins with
a thin layer of solder, which *should* resist tarnishing better than the copper and provide a relatively
long lived connector.


<!--standard_doc_footer-->
___
### [**Next**](solder.md) - TE3 - Soldering (and Crimping) the Electronic Circuits and Cables/Connectors!!



<!--end of md file-->

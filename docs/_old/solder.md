# TE3 - Soldering (and Crimping) the Electronic Circuits and Cables/Connectors

<!--standard_doc_header-->
**[Home](readme.md)** --
**[Pcbs](pcbs.md)** --
**Solder** --
**[Parts](parts.md)** --
**[Build](build.md)** --
**[Overview](overview.md)** --
**[Design](design.md)** --
**[Implement](implement.md)** --
**[Details](details.md)** --
**[User](user.md)** --
**[Songs](songs.md)**

As well as having to laser cut *solder masks* for the SMT row_boards and led_board,
and soldering them on a **hot plate**, there were many through-hole components and
wires to **hand-solder** and quite a few connectors to painstakingly **crimp** onto cables
in this phase.

This was **several days** of hard work, epsecially as I decided to test each board after
soldering by plugging it into the *prototype breadboard circuits* and found
**problems**, some vexing and difficult to diagnose, that had to be corrected on a number
of the boards before I could continue to soldering or crimping the next pcb/cable.

Finally, there was the job of removing the **store-bought USBC hub** from its case,
and retro-fitting it into the TE3 project. In reality that sub-task had been going
on for a number of weeks as the USBC hub is *instrumental* to the device, providing
the main **USBC interface** to the iPad, as well as being the **power supply** for the
entire box.  I spent much time figuring out how this particular USBC hub was wired, before
desoldering and removing its original cable, soldering a new cable with a JST connector onto it,
adding wires and a JST connector for powering the rPi, and *testing it over and over again*
before even committing myself to do this project.


[![images/solder-all_electronics.jpg](images/solder-all_electronics.jpg)](images/solder-all_electronics_big.jpg)

The above photo shows all of the PCBs, cables, and connectors that go into the box.

- there are two **3.5" IL9488 SPI Touch Screens** in the upper right of the photo
- below them are the two **lcd_connectors** with their cables and crimped JST8 connectors
- in the center you can see the **rotary_board** and its cable with a crimped JST5 connector
- below that is the **row_board cable** consisting of 6 wires crimped to two JST6 connectors
- below that is the **rPi zero2W** with its header soldered on and a single wire and JST connector soldered to the *run pin* on the bottom
- below that, to the left, is the **teensy4.0**, with its headers soldered on, and a single wire and JST connector soldered to the *gpio32* pin on the bottom
- the teensy4.0 is plugged into the **audio shield** with its headers soldered on
- next to that is the **teensy4.1** with its headers soldered on.
- on the bottom right are six soldered and tested **row boards**. Four of them have short cables with JST6 connectors crimped on.
  One doesn't need a cable, and the other one is a spare.
- on the left side of the photo, starting at the bottom is the **led_board** with its soldered and crimped 8 wire JST8 connector
- next to it is the **USBC Hub** board, with various modifications discussed in detail elsewhere
- above those are the two orange **USBC breakout boards** with JST5 and JST6 connectors, respectively, soldered to them
- above those are two of the **usba_connector** pcbs, soldered to cables and soldered to *micro-usb connectors* on the other end
- in the upper left is one of the **usba_connector** pcbs soldered to a cable to a *usba breakout board* for the *main usb port*
  and a **USBA breakout board** soldered to four wires to a crimped JST4 connector for the *host usb port*

Finally, at the bottom is the **mother_board** with most of its connectors and components soldered on.
The *five quarter inch jacks*, *stereo RCA jacks*, and *1/8" jack* have not yet been soldered to it in this photo.
I have a limited supply of those connectors, so I tested everything else that I could before I finally soldered
them on and proceeded to actual **audio testing** and testing the **debugging serial port** on the motherboard.

THIS WAS A TON OF WORK!!


## Mother Board

[![images/solder-mother_board_front.jpg](images/solder-mother_board_front.jpg)](images/solder-mother_board_front_big.jpg)

[![images/solder-mother_board_back.jpg](images/solder-mother_board_back.jpg)](images/solder-mother_board_back_big.jpg)



## Row Boards

[![images/solder-row_board_mask.jpg](images/solder-row_board_mask.jpg)](images/solder-row_board_mask_big.jpg)

[![images/solder-row_board_front.jpg](images/solder-row_board_front.jpg)](images/solder-row_board_front_big.jpg)

[![images/solder-row_board_back.jpg](images/solder-row_board_back.jpg)](images/solder-row_board_back_big.jpg)


## Rotary Board

[![images/solder-rotary_board_front.jpg](images/solder-rotary_board_front.jpg)](images/solder-rotary_board_front_big.jpg)

[![images/solder-rotary_board_back.jpg](images/solder-rotary_board_back.jpg)](images/solder-rotary_board_back_big.jpg)


## LCD Connectors

[![images/solder-lcd_connectors_front.jpg](images/solder-lcd_connectors_front.jpg)](images/solder-lcd_connectors_front_big.jpg)


## LED Board

[![images/solder-led_board_front.jpg](images/solder-led_board_front.jpg)](images/solder-led_board_front_big.jpg)


## Teensy and rPI headers and connectors


[![images/solder-teensy41_front.jpg](images/solder-teensy41_front.jpg)](images/solder-teensy41_front_big.jpg)


[![images/solder-teensy40_back.jpg](images/solder-teensy40_back.jpg)](images/solder-teensy40_back_big.jpg)


[![images/solder-audio_shield_front.jpg](images/solder-audio_shield_front.jpg)](images/solder-audio_shield_front_big.jpg)

[![images/solder-audio_shield_back.jpg](images/solder-audio_shield_back.jpg)](images/solder-audio_shield_back_big.jpg)


[![images/solder-rpi_front.jpg](images/solder-rpi_front.jpg)](images/solder-rpi_front_big.jpg)

[![images/solder-rpi_back.jpg](images/solder-rpi_back.jpg)](images/solder-rpi_back_big.jpg)





## USB Cables and Connectors

[![images/solder-usbc_breakouts_front.jpg](images/solder-usbc_breakouts_front.jpg)](images/solder-usbc_breakouts_front_big.jpg)

[![images/solder-usba_micro.jpg](images/solder-usba_micro.jpg)](images/solder-usba_micro_big.jpg)

[![images/solder-usba_ports.jpg](images/solder-usba_ports.jpg)](images/solder-usba_ports_big.jpg)





## The USBC Hub

[![images/solder-usbc_hub_front.jpg](images/solder-usbc_hub_front.jpg)](images/solder-usbc_hub_front_big.jpg)

[![images/solder-usbc_hub_back.jpg](images/solder-usbc_hub_back.jpg)](images/solder-usbc_hub_back_big.jpg)




<!--standard_doc_footer-->
___
### [**Next**](parts.md) - unknown!!



<!--end of md file-->

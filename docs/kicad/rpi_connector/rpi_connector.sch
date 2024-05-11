EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A2 23386 16535
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GND #PWR011
U 1 1 66610187
P 3200 5800
F 0 "#PWR011" H 3200 5550 50  0001 C CNN
F 1 "GND" V 3200 5600 50  0000 C CNN
F 2 "" H 3200 5800 50  0001 C CNN
F 3 "" H 3200 5800 50  0001 C CNN
	1    3200 5800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 6660F832
P 3600 5800
F 0 "#PWR012" H 3600 5550 50  0001 C CNN
F 1 "GND" V 3600 5600 50  0000 C CNN
F 2 "" H 3600 5800 50  0001 C CNN
F 3 "" H 3600 5800 50  0001 C CNN
	1    3600 5800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 6660E5AB
P 3400 4600
F 0 "#PWR06" H 3400 4350 50  0001 C CNN
F 1 "GND" V 3400 4400 50  0000 C CNN
F 2 "" H 3400 4600 50  0001 C CNN
F 3 "" H 3400 4600 50  0001 C CNN
	1    3400 4600
	-1   0    0    1   
$EndComp
Text GLabel 3800 5800 3    50   Input ~ 0
RPI_5V
Text GLabel 3500 4600 1    50   Input ~ 10
RPI_CD
Text GLabel 3500 5800 3    50   Input ~ 0
RPI_TX
Text GLabel 3400 5800 3    50   Input ~ 0
RPI_RX
Text GLabel 3300 5800 3    50   Input ~ 0
I2S_BCLK
Text GLabel 2300 5800 3    50   Input ~ 10
RPI_I2S_TX_ACTIVE
$Comp
L Connector_Generic:Conn_01x01 J12
U 1 1 66503904
P 1700 4000
F 0 "J12" H 1650 4150 50  0001 L CNN
F 1 "RPI_RUN" H 1780 3951 50  0001 L CNN
F 2 "0_my_footprints2:Oval1Pin" H 1700 4000 50  0001 C CNN
F 3 "~" H 1700 4000 50  0001 C CNN
	1    1700 4000
	1    0    0    -1  
$EndComp
Text GLabel 1500 4000 0    50   Input ~ 0
RPI_RUN
Text GLabel 2100 4600 1    50   Input ~ 0
I2S_FCLK
Text GLabel 2000 5800 3    50   Input ~ 0
I2S_RX
Text GLabel 1900 5800 3    50   Input ~ 0
I2S_TX
Text GLabel 2900 4600 1    50   Input ~ 0
RPI_MOSI
Text GLabel 2800 4600 1    50   Input ~ 0
RPI_MISO
Text GLabel 2700 4600 1    50   Input ~ 0
RPI_SCLK
Text GLabel 2700 5800 3    50   Input ~ 0
RPI_LED_CS
Text GLabel 2600 5800 3    50   Input ~ 0
RPI_TOUCH_CS
Text GLabel 2100 5800 3    50   Input ~ 10
RPI_READY
Text GLabel 2800 5800 3    50   Input ~ 10
RPI_I2S_RX_ACTIVE
$Comp
L power:GND #PWR05
U 1 1 6660E9EA
P 2600 4600
F 0 "#PWR05" H 2600 4350 50  0001 C CNN
F 1 "GND" V 2600 4400 50  0000 C CNN
F 2 "" H 2600 4600 50  0001 C CNN
F 3 "" H 2600 4600 50  0001 C CNN
	1    2600 4600
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 6660EE40
P 1900 4600
F 0 "#PWR04" H 1900 4350 50  0001 C CNN
F 1 "GND" V 1900 4400 50  0000 C CNN
F 2 "" H 1900 4600 50  0001 C CNN
F 3 "" H 1900 4600 50  0001 C CNN
	1    1900 4600
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR010
U 1 1 666109AB
P 2900 5800
F 0 "#PWR010" H 2900 5550 50  0001 C CNN
F 1 "GND" V 2900 5600 50  0000 C CNN
F 2 "" H 2900 5800 50  0001 C CNN
F 3 "" H 2900 5800 50  0001 C CNN
	1    2900 5800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 666110E8
P 2400 5800
F 0 "#PWR09" H 2400 5550 50  0001 C CNN
F 1 "GND" V 2400 5600 50  0000 C CNN
F 2 "" H 2400 5800 50  0001 C CNN
F 3 "" H 2400 5800 50  0001 C CNN
	1    2400 5800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 66611616
P 2200 5800
F 0 "#PWR08" H 2200 5550 50  0001 C CNN
F 1 "GND" V 2200 5600 50  0000 C CNN
F 2 "" H 2200 5800 50  0001 C CNN
F 3 "" H 2200 5800 50  0001 C CNN
	1    2200 5800
	1    0    0    -1  
$EndComp
$Comp
L 0_my_symbols:rpiA J14
U 1 1 66521D2F
P 2850 5450
F 0 "J14" H 2900 5600 50  0001 C CNN
F 1 "rpiA" H 2950 5600 50  0000 C CNN
F 2 "0_my_footprints2:pinSocket1x20_bottom" H 2700 5300 50  0001 C CNN
F 3 "" H 2700 5300 50  0001 C CNN
	1    2850 5450
	1    0    0    -1  
$EndComp
Text GLabel 3700 5800 3    50   Input ~ 0
RPI_5V
$Comp
L 0_my_symbols:rpiB J13
U 1 1 66525118
P 2850 4950
F 0 "J13" H 3050 4900 50  0001 C CNN
F 1 "rpiB" H 3200 4900 50  0000 C CNN
F 2 "0_my_footprints2:pinSocket1x20_bottom" H 2750 4550 50  0001 C CNN
F 3 "" H 2750 4550 50  0001 C CNN
	1    2850 4950
	1    0    0    -1  
$EndComp
Text GLabel 2200 3000 3    50   Input ~ 0
I2S_FCLK
Text GLabel 2100 3000 3    50   Input ~ 0
I2S_BCLK
$Comp
L power:GND #PWR02
U 1 1 6642BF21
P 2000 3000
F 0 "#PWR02" H 2000 2750 50  0001 C CNN
F 1 "GND" V 2000 2800 50  0000 C CNN
F 2 "" H 2000 3000 50  0001 C CNN
F 3 "" H 2000 3000 50  0001 C CNN
	1    2000 3000
	-1   0    0    -1  
$EndComp
Text GLabel 2300 3000 3    50   Input ~ 0
I2S_TX
Text GLabel 2400 3000 3    50   Input ~ 0
I2S_RX
Text GLabel 1450 3000 3    50   Input ~ 0
RPI_RUN
Text GLabel 1350 3000 3    50   Input ~ 0
RPI_TX
Text GLabel 1250 3000 3    50   Input ~ 0
RPI_RX
Text GLabel 1550 3000 3    50   Input ~ 10
RPI_READY
$Comp
L power:GND #PWR01
U 1 1 6644CAB9
P 1150 3000
F 0 "#PWR01" H 1150 2750 50  0001 C CNN
F 1 "GND" V 1150 2800 50  0000 C CNN
F 2 "" H 1150 3000 50  0001 C CNN
F 3 "" H 1150 3000 50  0001 C CNN
	1    1150 3000
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 6645117F
P 4450 3000
F 0 "#PWR03" H 4450 2750 50  0001 C CNN
F 1 "GND" V 4450 2800 50  0000 C CNN
F 2 "" H 4450 3000 50  0001 C CNN
F 3 "" H 4450 3000 50  0001 C CNN
	1    4450 3000
	-1   0    0    -1  
$EndComp
Text GLabel 4150 3000 3    50   Input ~ 0
RPI_MOSI
Text GLabel 4250 3000 3    50   Input ~ 0
RPI_MISO
Text GLabel 4350 3000 3    50   Input ~ 0
RPI_SCLK
Text GLabel 3850 3000 3    50   Input ~ 0
RPI_LED_CS
Text GLabel 3950 3000 3    50   Input ~ 0
RPI_TOUCH_CS
Text GLabel 4050 3000 3    50   Input ~ 10
RPI_CD
Text GLabel 3750 3000 3    50   Input ~ 0
RPI_5V
$Comp
L Device:LED D1
U 1 1 6647603F
P 5850 5200
F 0 "D1" H 5843 4945 50  0001 C CNN
F 1 "yellow" H 5843 5037 50  0000 C CNN
F 2 "0_my_footprints2:led_yellow" H 5850 5200 50  0001 C CNN
F 3 "~" H 5850 5200 50  0001 C CNN
	1    5850 5200
	-1   0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 66478725
P 5550 5200
F 0 "R1" V 5343 5200 50  0001 C CNN
F 1 "220" V 5550 5200 50  0000 C CNN
F 2 "0_my_footprints2:resistor" V 5480 5200 50  0001 C CNN
F 3 "~" H 5550 5200 50  0001 C CNN
	1    5550 5200
	0    1    1    0   
$EndComp
$Comp
L Device:LED D2
U 1 1 66485268
P 5850 5550
F 0 "D2" H 5843 5295 50  0001 C CNN
F 1 "yellow" H 5843 5387 50  0000 C CNN
F 2 "0_my_footprints2:led_yellow" H 5850 5550 50  0001 C CNN
F 3 "~" H 5850 5550 50  0001 C CNN
	1    5850 5550
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 6648526E
P 5550 5550
F 0 "R2" V 5343 5550 50  0001 C CNN
F 1 "220" V 5550 5550 50  0000 C CNN
F 2 "0_my_footprints2:resistor" V 5480 5550 50  0001 C CNN
F 3 "~" H 5550 5550 50  0001 C CNN
	1    5550 5550
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR07
U 1 1 66487462
P 6100 5700
F 0 "#PWR07" H 6100 5450 50  0001 C CNN
F 1 "GND" V 6100 5500 50  0000 C CNN
F 2 "" H 6100 5700 50  0001 C CNN
F 3 "" H 6100 5700 50  0001 C CNN
	1    6100 5700
	1    0    0    -1  
$EndComp
Text GLabel 5400 5200 0    50   Input ~ 10
RPI_I2S_TX_ACTIVE
Text GLabel 5400 5550 0    50   Input ~ 10
RPI_I2S_RX_ACTIVE
Wire Wire Line
	6000 5550 6100 5550
Wire Wire Line
	6000 5200 6100 5200
Wire Wire Line
	6100 5200 6100 5550
Connection ~ 6100 5550
Wire Wire Line
	6100 5550 6100 5700
Text Notes 950  900  0    100  ~ 20
prototype rPi connector
Text Notes 1150 2400 0    50   ~ 0
wired connector for rPi control
Text Notes 1150 2500 0    50   ~ 0
wired connector for rPi I2S
Text Notes 950  2250 0    50   ~ 10
uses arbirarily positioned wired connectors
Text Notes 950  2800 0    50   ~ 0
These wired connectors allow me to experiment \nwith different other MPUs (teensy 4.x's) for audio\nand rPi control.
Text Notes 3200 2250 0    50   ~ 10
has semi-standardized new display connector
Text Notes 3400 2350 0    50   ~ 0
developed during _prototype0 design phases
Text Notes 3400 2450 0    50   ~ 0
is known to likely map well to rPi pins
Text Notes 4600 4650 0    50   ~ 10
has onboard I2S activity LEDS
Text Notes 4750 4850 0    50   ~ 0
in the prototype stage, these only need to be\nvisible, and do not need to be off-board
Text Notes 950  1400 0    50   ~ 0
This connector is intended to have bottom sockets with long pins\nthrough the top, to be mounted on top of an rPi or breakout board.
Text Notes 950  1100 0    50   ~ 10
NOTE THAT THE COPPER IS ON TOP
Text Notes 950  1550 0    50   ~ 0
which means that the top mounted LEDs will have to have legs
Text Notes 950  1650 0    50   ~ 0
the wires are soldered onto the top and hot-glued when proven
Text Notes 3200 2700 0    50   ~ 0
This will be a bare pin header soldered from the top, \nand epoxied on the bottom, without any JST socket
Text Notes 950  1800 0    50   ~ 0
wires can be run on top between the rPi pins
$EndSCHEMATC

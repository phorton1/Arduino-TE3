EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
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
L 0_my_teensy:myTeensy4.1 U2
U 1 1 679426B6
P 3400 4800
F 0 "U2" H 3300 4750 50  0000 L CNN
F 1 "myTeensy4.1" H 3300 4650 50  0000 L CNN
F 2 "0_my_teensy:teensy41" H 3100 3900 50  0001 C CNN
F 3 "" H 3100 3900 50  0001 C CNN
	1    3400 4800
	1    0    0    -1  
$EndComp
$Comp
L 0_my_symbols:rpi_connector J7
U 1 1 67943AF8
P 12550 4500
F 0 "J7" H 12200 4500 50  0000 L CNN
F 1 "rpi_connector" H 12350 4500 50  0000 L CNN
F 2 "0_my_footprints2:rpi_zero_2w" H 12450 4400 50  0001 C CNN
F 3 "" H 12450 4400 50  0001 C CNN
	1    12550 4500
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J3
U 1 1 679456F8
P 5700 2000
F 0 "J3" V 5800 1600 50  0000 L CNN
F 1 "TE_DISPLAY" V 5800 1950 50  0000 L CNN
F 2 "0_my_footprints:myJSTx08" H 5700 2000 50  0001 C CNN
F 3 "~" H 5700 2000 50  0001 C CNN
	1    5700 2000
	0    1    -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J2
U 1 1 67946D3E
P 3000 2000
F 0 "J2" V 3100 1750 50  0000 L CNN
F 1 "ROTARIES" V 3100 1900 50  0000 L CNN
F 2 "0_my_footprints:myJSTx05" H 3000 2000 50  0001 C CNN
F 3 "~" H 3000 2000 50  0001 C CNN
	1    3000 2000
	0    1    -1   0   
$EndComp
$Comp
L power:GND #PWR03
U 1 1 6794C62E
P 2800 2200
F 0 "#PWR03" H 2800 1950 50  0001 C CNN
F 1 "GND" V 2800 1900 50  0000 L CNN
F 2 "" H 2800 2200 50  0001 C CNN
F 3 "" H 2800 2200 50  0001 C CNN
	1    2800 2200
	1    0    0    -1  
$EndComp
Text GLabel 3200 2200 3    50   Input ~ 0
T41_SCL
Text GLabel 3100 2200 3    50   Input ~ 0
T41_SDA
Text GLabel 2900 2200 3    50   Input ~ 0
ROT_INT
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 67952F34
P 1850 2000
F 0 "J1" V 1950 1650 50  0000 L CNN
F 1 "ROW_BOARDS" V 1950 1750 50  0000 L CNN
F 2 "0_my_footprints:myJSTx06" H 1850 2000 50  0001 C CNN
F 3 "~" H 1850 2000 50  0001 C CNN
	1    1850 2000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 67955DCC
P 1950 2200
F 0 "#PWR02" H 1950 1950 50  0001 C CNN
F 1 "GND" V 1950 1900 50  0000 L CNN
F 2 "" H 1950 2200 50  0001 C CNN
F 3 "" H 1950 2200 50  0001 C CNN
	1    1950 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 6797D5D1
P 6000 2200
F 0 "#PWR05" H 6000 1950 50  0001 C CNN
F 1 "GND" V 6000 1900 50  0000 L CNN
F 2 "" H 6000 2200 50  0001 C CNN
F 3 "" H 6000 2200 50  0001 C CNN
	1    6000 2200
	1    0    0    -1  
$EndComp
Text GLabel 5400 2200 3    50   Input ~ 0
T41_T_CS
Text GLabel 5500 2200 3    50   Input ~ 0
T41_SCLK
Text GLabel 5600 2200 3    50   Input ~ 0
T41_MISO
Text GLabel 5700 2200 3    50   Input ~ 0
T41_LCD_DC
Text GLabel 5800 2200 3    50   Input ~ 0
T41_LCD_CS
Text GLabel 5900 2200 3    50   Input ~ 0
T41_MOSI
Text GLabel 11050 2200 3    50   Input ~ 0
RPI_T_CS
Text GLabel 11150 2200 3    50   Input ~ 0
RPI_SCLK
Text GLabel 11800 5200 3    50   Input ~ 0
LED_RPI_I2S_TX
Text GLabel 13000 5200 3    50   Input ~ 0
I2S_BCLK
Text GLabel 11800 3850 1    50   Input ~ 0
I2S_FCLK
Text GLabel 11700 5200 3    50   Input ~ 0
I2S_TXB
Text GLabel 11600 5200 3    50   Input ~ 0
I2S_RXB
Text GLabel 12000 5200 3    50   Input ~ 10
RPI_READY
Text GLabel 12400 3850 1    50   Input ~ 0
RPI_SCLK
Text GLabel 12500 3850 1    50   Input ~ 0
RPI_MISO
Text GLabel 12600 3850 1    50   Input ~ 0
RPI_MOSI
Text Notes 5400 1850 0    50   ~ 0
ILI9488_T3
Text GLabel 3600 3900 1    50   Input ~ 0
T41_SCLK
Text GLabel 3600 5950 3    50   Input ~ 0
T41_MISO
Text GLabel 3500 5950 3    50   Input ~ 0
T41_MOSI
Text GLabel 2900 5950 3    50   Input ~ 0
LED_RPI_RUN
Text GLabel 3000 5950 3    50   Input ~ 0
LED_RPI_READY
Text GLabel 3300 5950 3    50   Input ~ 0
T41_LCD_DC
Text GLabel 3400 5950 3    50   Input ~ 0
T41_LCD_CS
Text GLabel 2700 5950 3    50   Input ~ 0
T41_T_CS
Text GLabel 2800 5950 3    50   Input ~ 0
LED_T3_BUSY
Text GLabel 12400 5200 3    50   Input ~ 0
RPI_LCD_CS
Text GLabel 12300 5200 3    50   Input ~ 0
RPI_T_CS
Text GLabel 13200 3850 1    50   Input ~ 0
RPI_LCD_DC
$Comp
L power:GND #PWR027
U 1 1 67A37846
P 13300 5200
F 0 "#PWR027" H 13300 4950 50  0001 C CNN
F 1 "GND" V 13300 4900 50  0000 L CNN
F 2 "" H 13300 5200 50  0001 C CNN
F 3 "" H 13300 5200 50  0001 C CNN
	1    13300 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 67A37CAF
P 12900 5200
F 0 "#PWR026" H 12900 4950 50  0001 C CNN
F 1 "GND" V 12900 4900 50  0000 L CNN
F 2 "" H 12900 5200 50  0001 C CNN
F 3 "" H 12900 5200 50  0001 C CNN
	1    12900 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR025
U 1 1 67A37F8C
P 12600 5200
F 0 "#PWR025" H 12600 4950 50  0001 C CNN
F 1 "GND" V 12600 4900 50  0000 L CNN
F 2 "" H 12600 5200 50  0001 C CNN
F 3 "" H 12600 5200 50  0001 C CNN
	1    12600 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR024
U 1 1 67A38141
P 12100 5200
F 0 "#PWR024" H 12100 4950 50  0001 C CNN
F 1 "GND" V 12100 4900 50  0000 L CNN
F 2 "" H 12100 5200 50  0001 C CNN
F 3 "" H 12100 5200 50  0001 C CNN
	1    12100 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR023
U 1 1 67A38257
P 11900 5200
F 0 "#PWR023" H 11900 4950 50  0001 C CNN
F 1 "GND" V 11900 4900 50  0000 L CNN
F 2 "" H 11900 5200 50  0001 C CNN
F 3 "" H 11900 5200 50  0001 C CNN
	1    11900 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 67A38A35
P 11600 3850
F 0 "#PWR012" H 11600 3600 50  0001 C CNN
F 1 "GND" V 11600 3550 50  0000 L CNN
F 2 "" H 11600 3850 50  0001 C CNN
F 3 "" H 11600 3850 50  0001 C CNN
	1    11600 3850
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR013
U 1 1 67A38E9E
P 12300 3850
F 0 "#PWR013" H 12300 3600 50  0001 C CNN
F 1 "GND" V 12300 3550 50  0000 L CNN
F 2 "" H 12300 3850 50  0001 C CNN
F 3 "" H 12300 3850 50  0001 C CNN
	1    12300 3850
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR014
U 1 1 67A392BE
P 13100 3850
F 0 "#PWR014" H 13100 3600 50  0001 C CNN
F 1 "GND" V 13100 3550 50  0000 L CNN
F 2 "" H 13100 3850 50  0001 C CNN
F 3 "" H 13100 3850 50  0001 C CNN
	1    13100 3850
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR032
U 1 1 67A3B5C4
P 2300 5950
F 0 "#PWR032" H 2300 5700 50  0001 C CNN
F 1 "GND" V 2300 5650 50  0000 L CNN
F 2 "" H 2300 5950 50  0001 C CNN
F 3 "" H 2300 5950 50  0001 C CNN
	1    2300 5950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 67A3C2A4
P 2400 3900
F 0 "#PWR016" H 2400 3650 50  0001 C CNN
F 1 "GND" V 2400 3600 50  0000 L CNN
F 2 "" H 2400 3900 50  0001 C CNN
F 3 "" H 2400 3900 50  0001 C CNN
	1    2400 3900
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR017
U 1 1 67A3C67C
P 3700 3900
F 0 "#PWR017" H 3700 3650 50  0001 C CNN
F 1 "GND" V 3700 3600 50  0000 L CNN
F 2 "" H 3700 3900 50  0001 C CNN
F 3 "" H 3700 3900 50  0001 C CNN
	1    3700 3900
	-1   0    0    1   
$EndComp
Text GLabel 4300 5950 3    50   Input ~ 0
T41_RX7
Text GLabel 4200 5950 3    50   Input ~ 0
T41_TX7
Text GLabel 4500 3900 1    50   Input ~ 0
T41_RX8
Text GLabel 4400 3900 1    50   Input ~ 0
T41_TX8
Text GLabel 13200 5200 3    50   Input ~ 0
T41_RX1
Text GLabel 13100 5200 3    50   Input ~ 0
T41_TX1
$Comp
L power:GND #PWR035
U 1 1 67A5DC81
P 1350 8250
F 0 "#PWR035" H 1350 8000 50  0001 C CNN
F 1 "GND" V 1350 7950 50  0000 L CNN
F 2 "" H 1350 8250 50  0001 C CNN
F 3 "" H 1350 8250 50  0001 C CNN
	1    1350 8250
	-1   0    0    1   
$EndComp
Text Notes 11150 1850 0    50   ~ 0
ILI9488
$Comp
L Device:R R3
U 1 1 64CCBE5B
P 6000 4550
F 0 "R3" V 6100 4500 50  0000 L CNN
F 1 "220" V 6000 4550 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 5930 4550 50  0001 C CNN
F 3 "~" H 6000 4550 50  0001 C CNN
	1    6000 4550
	0    -1   -1   0   
$EndComp
Text GLabel 6400 4550 2    50   Input ~ 0
RPI_RUN
Text GLabel 5850 4550 0    50   Input ~ 0
SENS_PI_RUN
$Comp
L Transistor_BJT:BC547 Q1
U 1 1 64CF1712
P 6200 4850
F 0 "Q1" H 6391 4896 50  0000 L CNN
F 1 "BC547" H 6391 4805 50  0000 L CNN
F 2 "0_my_footprints:myTransistor" H 6400 4775 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 6200 4850 50  0001 L CNN
	1    6200 4850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR022
U 1 1 64CF464E
P 6300 5150
F 0 "#PWR022" H 6300 4900 50  0001 C CNN
F 1 "GND" H 6305 4977 50  0000 C CNN
F 2 "" H 6300 5150 50  0001 C CNN
F 3 "" H 6300 5150 50  0001 C CNN
	1    6300 5150
	1    0    0    -1  
$EndComp
Text GLabel 5700 4850 0    50   Input ~ 0
PI_REBOOT
Wire Wire Line
	6150 4550 6300 4550
Wire Wire Line
	6300 4650 6300 4550
Connection ~ 6300 4550
Wire Wire Line
	6300 4550 6400 4550
Wire Wire Line
	6300 5050 6300 5150
Text GLabel 3200 3900 1    50   Input ~ 0
ROT_INT
Text GLabel 3100 3900 1    50   Input ~ 0
T41_SDA
Text GLabel 3000 3900 1    50   Input ~ 0
T41_SCL
Text GLabel 2500 3900 1    50   Input ~ 0
T41_3V3
Text GLabel 3000 2200 3    50   Input ~ 0
T41_3V3
Text GLabel 3300 3900 1    50   Input ~ 0
SENS_PI_RUN
Text GLabel 4500 5950 3    50   Input ~ 0
PI_REBOOT
Text GLabel 4400 5950 3    50   Input ~ 0
RPI_READY
Text GLabel 4400 2650 3    50   Input ~ 0
T41_SCL
Text GLabel 4500 2650 3    50   Input ~ 0
T41_SDA
$Comp
L Device:R R2
U 1 1 67964E23
P 4500 2500
F 0 "R2" H 4550 2500 50  0000 L CNN
F 1 "1K" V 4500 2500 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 4430 2500 50  0001 C CNN
F 3 "~" H 4500 2500 50  0001 C CNN
	1    4500 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 67965E12
P 4400 2500
F 0 "R1" H 4250 2500 50  0000 L CNN
F 1 "1K" V 4400 2500 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 4330 2500 50  0001 C CNN
F 3 "~" H 4400 2500 50  0001 C CNN
	1    4400 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 2350 4500 2250
Wire Wire Line
	4400 2350 4400 2250
$Comp
L Device:R R4
U 1 1 6796F63B
P 5850 4850
F 0 "R4" V 5950 4800 50  0000 L CNN
F 1 "1K" V 5850 4850 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 5780 4850 50  0001 C CNN
F 3 "~" H 5850 4850 50  0001 C CNN
	1    5850 4850
	0    -1   -1   0   
$EndComp
Text GLabel 2050 2200 3    50   Input ~ 0
BTN_CLK
Text GLabel 1450 8250 1    50   Input ~ 0
T41_TX7
Text GLabel 2100 8250 1    50   Input ~ 0
T41_RX7
Text GLabel 2500 5950 3    50   Input ~ 0
T41_TX1
Text GLabel 2400 5950 3    50   Input ~ 0
T41_RX1
Text GLabel 1750 2200 3    50   Input ~ 0
LED_DIN
Text GLabel 1850 2200 3    50   Input ~ 0
BTN_DIN
Text GLabel 2800 3900 1    50   Input ~ 0
BTN_CLK
Text GLabel 2900 3900 1    50   Input ~ 0
LED_DIN
Text GLabel 2700 3900 1    50   Input ~ 0
BTN_DIN
Text GLabel 2600 3900 1    50   Input ~ 0
BTN_SENSE
Text GLabel 2150 2200 3    50   Input ~ 0
T41_3V3
Text GLabel 1650 2200 3    50   Input ~ 0
BTN_SENSE
Text Notes 4000 1800 0    50   ~ 0
Rotary mcp23017 needs\n1K pullups on SDA & SCL
Wire Wire Line
	4400 2250 4450 2250
Text GLabel 4450 2200 1    50   Input ~ 0
T41_3V3
Wire Wire Line
	4450 2200 4450 2250
Connection ~ 4450 2250
Wire Wire Line
	4450 2250 4500 2250
$Comp
L Connector_Generic:Conn_01x02 J5
U 1 1 679E8689
P 13300 2000
F 0 "J5" V 13400 1850 50  0000 R CNN
F 1 "rPi_5V" V 13400 2150 50  0000 R CNN
F 2 "0_my_footprints:myJSTx02" H 13300 2000 50  0001 C CNN
F 3 "~" H 13300 2000 50  0001 C CNN
	1    13300 2000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR08
U 1 1 679ECFE3
P 13400 2200
F 0 "#PWR08" H 13400 1950 50  0001 C CNN
F 1 "GND" V 13400 1900 50  0000 L CNN
F 2 "" H 13400 2200 50  0001 C CNN
F 3 "" H 13400 2200 50  0001 C CNN
	1    13400 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR037
U 1 1 67B33AE6
P 12400 8750
F 0 "#PWR037" H 12400 8500 50  0001 C CNN
F 1 "GND" V 12400 8450 50  0000 L CNN
F 2 "" H 12400 8750 50  0001 C CNN
F 3 "" H 12400 8750 50  0001 C CNN
	1    12400 8750
	-1   0    0    1   
$EndComp
Text GLabel 11700 8800 1    50   Input ~ 0
LED_T3_BUSY
Text GLabel 12000 8800 1    50   Input ~ 0
LED_AUDIO_BUSY
Text GLabel 12200 8800 1    50   Input ~ 0
LED_RPI_I2S_RX
Text GLabel 12300 8800 1    50   Input ~ 0
LED_RPI_I2S_TX
Text GLabel 11900 8800 1    50   Input ~ 0
LED_RPI_READY
Text GLabel 11800 8800 1    50   Input ~ 0
LED_RPI_RUN
Text GLabel 12100 8800 1    50   Input ~ 0
LED_RPI_BUSY
$Comp
L Connector_Generic:Conn_01x02 J6
U 1 1 679E6862
P 11350 4450
F 0 "J6" H 11350 4650 50  0000 R CNN
F 1 "RPI_RUN" H 11450 4550 50  0000 R CNN
F 2 "0_my_footprints:myJSTx02" H 11350 4450 50  0001 C CNN
F 3 "~" H 11350 4450 50  0001 C CNN
	1    11350 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR021
U 1 1 679EB87B
P 11150 4450
F 0 "#PWR021" H 11150 4200 50  0001 C CNN
F 1 "GND" V 11150 4150 50  0000 L CNN
F 2 "" H 11150 4450 50  0001 C CNN
F 3 "" H 11150 4450 50  0001 C CNN
	1    11150 4450
	0    1    1    0   
$EndComp
Text GLabel 3000 7600 0    50   Input ~ 0
T41_3V3
Text GLabel 3900 7350 1    50   Input ~ 0
PEDAL1
Text GLabel 5200 7350 1    50   Input ~ 0
PEDAL2
Text GLabel 6450 7350 1    50   Input ~ 0
PEDAL3
Text GLabel 7700 7350 1    50   Input ~ 0
PEDAL4
Text GLabel 3800 5950 3    50   Input ~ 0
PEDAL1
Text GLabel 3900 5950 3    50   Input ~ 0
PEDAL2
Text GLabel 4000 5950 3    50   Input ~ 0
PEDAL3
Text GLabel 4100 5950 3    50   Input ~ 0
PEDAL4
$Comp
L 0_my_symbols:QuarterInchJack1 J12
U 1 1 67A759FF
P 6550 8900
F 0 "J12" V 6300 9200 50  0000 R CNN
F 1 "PEDAL3" V 6150 9050 50  0000 R CNN
F 2 "0_my_footprints2:QuarterInchJack1" H 6550 8950 50  0001 C CNN
F 3 "" H 6550 8950 50  0001 C CNN
	1    6550 8900
	0    -1   -1   0   
$EndComp
$Comp
L 0_my_symbols:QuarterInchJack1 J13
U 1 1 67A76419
P 7800 8900
F 0 "J13" V 7550 9200 50  0000 R CNN
F 1 "PEDAL4" V 7400 9050 50  0000 R CNN
F 2 "0_my_footprints2:QuarterInchJack1" H 7800 8950 50  0001 C CNN
F 3 "" H 7800 8950 50  0001 C CNN
	1    7800 8900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R5
U 1 1 67ACA208
P 3350 7600
F 0 "R5" V 3450 7550 50  0000 L CNN
F 1 "220" V 3350 7600 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 3280 7600 50  0001 C CNN
F 3 "~" H 3350 7600 50  0001 C CNN
	1    3350 7600
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R6
U 1 1 67ACD401
P 3750 8100
F 0 "R6" V 3850 8050 50  0000 L CNN
F 1 "10K" V 3750 8100 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 3680 8100 50  0001 C CNN
F 3 "~" H 3750 8100 50  0001 C CNN
	1    3750 8100
	-1   0    0    1   
$EndComp
$Comp
L Device:R R7
U 1 1 67ACDF8A
P 5050 8100
F 0 "R7" V 5150 8050 50  0000 L CNN
F 1 "10K" V 5050 8100 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 4980 8100 50  0001 C CNN
F 3 "~" H 5050 8100 50  0001 C CNN
	1    5050 8100
	-1   0    0    1   
$EndComp
$Comp
L Device:R R8
U 1 1 67ACE349
P 6300 8100
F 0 "R8" V 6400 8050 50  0000 L CNN
F 1 "10K" V 6300 8100 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 6230 8100 50  0001 C CNN
F 3 "~" H 6300 8100 50  0001 C CNN
	1    6300 8100
	-1   0    0    1   
$EndComp
$Comp
L Device:R R9
U 1 1 67ACFA4C
P 7550 8100
F 0 "R9" V 7650 8050 50  0000 L CNN
F 1 "10K" V 7550 8100 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 7480 8100 50  0001 C CNN
F 3 "~" H 7550 8100 50  0001 C CNN
	1    7550 8100
	-1   0    0    1   
$EndComp
$Comp
L 0_my_symbols:EigthInchJack1 J9
U 1 1 67AFA9BD
P 1800 8900
F 0 "J9" H 1983 9575 50  0000 C CNN
F 1 "EigthInchJack1" H 1983 9484 50  0000 C CNN
F 2 "0_my_footprints2:EigthInchJack1" H 1800 8950 50  0001 C CNN
F 3 "" H 1800 8950 50  0001 C CNN
	1    1800 8900
	0    -1   -1   0   
$EndComp
$Comp
L 0_my_symbols:QuarterInchJack1 J14
U 1 1 67B8B7DE
P 9600 8900
F 0 "J14" V 9350 9200 50  0000 R CNN
F 1 "GUITAR_IN" V 9200 9050 50  0000 R CNN
F 2 "0_my_footprints2:QuarterInchJack1" H 9600 8950 50  0001 C CNN
F 3 "" H 9600 8950 50  0001 C CNN
	1    9600 8900
	0    -1   -1   0   
$EndComp
$Comp
L 0_my_symbols:RCA2_PCB J15
U 1 1 67B8D37F
P 10800 8950
F 0 "J15" V 10500 9250 50  0000 R CNN
F 1 "LINE_OUT" V 10500 9050 50  0000 R CNN
F 2 "0_my_footprints2:RCA2_PCB" H 10800 8550 50  0001 C CNN
F 3 "" H 10800 8550 50  0001 C CNN
	1    10800 8950
	0    -1   -1   0   
$EndComp
Text GLabel 11000 8750 1    50   Input ~ 0
LINE_OUT_R
Text GLabel 10700 8750 1    50   Input ~ 0
LINE_OUT_L
$Comp
L power:GND #PWR036
U 1 1 67BA48CE
P 10850 8750
F 0 "#PWR036" H 10850 8500 50  0001 C CNN
F 1 "GND" V 10850 8550 50  0000 C CNN
F 2 "" H 10850 8750 50  0001 C CNN
F 3 "" H 10850 8750 50  0001 C CNN
	1    10850 8750
	-1   0    0    1   
$EndComp
Text GLabel 9700 8250 1    50   Input ~ 0
LINE_IN_L
Text GLabel 9500 8250 1    50   Input ~ 0
LINE_IN_R
$Comp
L power:GND #PWR034
U 1 1 67BB0343
P 9000 7850
F 0 "#PWR034" H 9000 7600 50  0001 C CNN
F 1 "GND" V 9000 7650 50  0000 C CNN
F 2 "" H 9000 7850 50  0001 C CNN
F 3 "" H 9000 7850 50  0001 C CNN
	1    9000 7850
	0    1    1    0   
$EndComp
Wire Wire Line
	3000 7600 3200 7600
Wire Wire Line
	3500 7600 4100 7600
Wire Wire Line
	7900 7600 7900 8250
Wire Wire Line
	6650 8250 6650 7600
Connection ~ 6650 7600
Wire Wire Line
	6650 7600 7900 7600
Wire Wire Line
	5400 8250 5400 7600
Connection ~ 5400 7600
Wire Wire Line
	5400 7600 6650 7600
Wire Wire Line
	4100 8250 4100 7600
Connection ~ 4100 7600
Wire Wire Line
	4100 7600 5400 7600
Wire Wire Line
	3900 7350 3900 8250
Wire Wire Line
	5200 7350 5200 8250
Wire Wire Line
	6450 7350 6450 8250
Wire Wire Line
	7700 7350 7700 8250
Text GLabel 9100 4350 1    50   Input ~ 0
LINE_IN_L
Text GLabel 9500 4350 1    50   Input ~ 0
LINE_OUT_L
Text GLabel 9300 4350 1    50   Input ~ 0
LINE_OUT_R
$Comp
L power:GND #PWR030
U 1 1 679E1C5A
P 9650 5400
F 0 "#PWR030" H 9650 5150 50  0001 C CNN
F 1 "GND" V 9650 5100 50  0000 L CNN
F 2 "" H 9650 5400 50  0001 C CNN
F 3 "" H 9650 5400 50  0001 C CNN
	1    9650 5400
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J8
U 1 1 679D8C31
P 9450 5400
F 0 "J8" H 9450 5100 50  0000 R CNN
F 1 "I2S_TXB" H 9550 5200 50  0000 R CNN
F 2 "0_my_footprints:myJSTx02" H 9450 5400 50  0001 C CNN
F 3 "~" H 9450 5400 50  0001 C CNN
	1    9450 5400
	-1   0    0    1   
$EndComp
Text GLabel 7700 5450 3    50   Input ~ 0
T41_TX8
Text GLabel 7800 5450 3    50   Input ~ 0
T41_RX8
$Comp
L power:GND #PWR031
U 1 1 67A3AA10
P 7600 5450
F 0 "#PWR031" H 7600 5200 50  0001 C CNN
F 1 "GND" V 7600 5150 50  0000 L CNN
F 2 "" H 7600 5450 50  0001 C CNN
F 3 "" H 7600 5450 50  0001 C CNN
	1    7600 5450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR019
U 1 1 67A3A486
P 7700 4000
F 0 "#PWR019" H 7700 3750 50  0001 C CNN
F 1 "GND" V 7700 3700 50  0000 L CNN
F 2 "" H 7700 4000 50  0001 C CNN
F 3 "" H 7700 4000 50  0001 C CNN
	1    7700 4000
	-1   0    0    1   
$EndComp
Text GLabel 11150 4550 0    50   Input ~ 0
RPI_RUN
Text GLabel 7900 5450 3    50   Input ~ 0
LED_AUDIO_BUSY
Text GLabel 8100 4000 1    50   Input ~ 0
I2S_BCLK
Text GLabel 8200 4000 1    50   Input ~ 0
I2S_FCLK
Text GLabel 8300 5450 3    50   Input ~ 0
I2S_RXB
Text GLabel 9650 5300 2    50   Input ~ 0
I2S_TXB
Text Notes 9000 7650 0    50   ~ 0
Note: NEED TE3 OPTION/CONFIG \nto use MONO LINE_IN_L/R (ring/tip) for input.\n
Text Notes 7500 2250 0    50   ~ 0
*might* allow for a MIC in 1/8th in jack via \npins on audio shield
$Comp
L 0_my_symbols:QuarterInchJack1 J11
U 1 1 67A742E2
P 5300 8900
F 0 "J11" V 5050 9200 50  0000 R CNN
F 1 "PEDAL2" V 4900 9050 50  0000 R CNN
F 2 "0_my_footprints2:QuarterInchJack1" H 5300 8950 50  0001 C CNN
F 3 "" H 5300 8950 50  0001 C CNN
	1    5300 8900
	0    -1   -1   0   
$EndComp
$Comp
L 0_my_symbols:QuarterInchJack1 J10
U 1 1 67A70CF2
P 4000 8900
F 0 "J10" V 3750 9200 50  0000 R CNN
F 1 "PEDAL1" V 3600 9050 50  0000 R CNN
F 2 "0_my_footprints2:QuarterInchJack1" H 4000 8950 50  0001 C CNN
F 3 "" H 4000 8950 50  0001 C CNN
	1    4000 8900
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR033
U 1 1 67A045B5
P 3000 7800
F 0 "#PWR033" H 3000 7550 50  0001 C CNN
F 1 "GND" V 3000 7500 50  0000 L CNN
F 2 "" H 3000 7800 50  0001 C CNN
F 3 "" H 3000 7800 50  0001 C CNN
	1    3000 7800
	0    1    1    0   
$EndComp
Wire Wire Line
	7550 7800 7550 7950
Wire Wire Line
	3000 7800 3500 7800
Wire Wire Line
	7300 7800 7300 8250
Connection ~ 7300 7800
Wire Wire Line
	7300 7800 7550 7800
Wire Wire Line
	6300 7950 6300 7800
Connection ~ 6300 7800
Wire Wire Line
	6300 7800 7300 7800
Wire Wire Line
	6050 7800 6050 8250
Connection ~ 6050 7800
Wire Wire Line
	6050 7800 6300 7800
Wire Wire Line
	5050 7950 5050 7800
Connection ~ 5050 7800
Wire Wire Line
	5050 7800 6050 7800
Wire Wire Line
	4800 7800 4800 8250
Connection ~ 4800 7800
Wire Wire Line
	4800 7800 5050 7800
Wire Wire Line
	3750 7950 3750 7800
Connection ~ 3750 7800
Wire Wire Line
	3750 7800 4800 7800
Wire Wire Line
	3500 7800 3500 8250
Connection ~ 3500 7800
Wire Wire Line
	3500 7800 3750 7800
$Comp
L Device:R R10
U 1 1 67A8E02B
P 9350 8100
F 0 "R10" V 9450 8050 50  0000 L CNN
F 1 "10K" V 9350 8100 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 9280 8100 50  0001 C CNN
F 3 "~" H 9350 8100 50  0001 C CNN
	1    9350 8100
	-1   0    0    1   
$EndComp
Wire Wire Line
	9000 7850 9100 7850
Wire Wire Line
	9350 7850 9350 7950
Wire Wire Line
	9100 8250 9100 7850
Connection ~ 9100 7850
Wire Wire Line
	9100 7850 9350 7850
Wire Wire Line
	12400 8800 12400 8750
$Comp
L power:+5V #PWR04
U 1 1 67B6103B
P 5300 2200
F 0 "#PWR04" H 5300 2050 50  0001 C CNN
F 1 "+5V" V 5300 2300 50  0000 L CNN
F 2 "" H 5300 2200 50  0001 C CNN
F 3 "" H 5300 2200 50  0001 C CNN
	1    5300 2200
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR015
U 1 1 67B6351A
P 2300 3900
F 0 "#PWR015" H 2300 3750 50  0001 C CNN
F 1 "+5V" V 2300 4000 50  0000 L CNN
F 2 "" H 2300 3900 50  0001 C CNN
F 3 "" H 2300 3900 50  0001 C CNN
	1    2300 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 67B672C5
P 3700 2350
F 0 "C2" H 3818 2396 50  0000 L CNN
F 1 "47uf" H 3818 2305 50  0000 L CNN
F 2 "0_my_footprints:CP_my10uf" H 3738 2200 50  0001 C CNN
F 3 "~" H 3700 2350 50  0001 C CNN
	1    3700 2350
	1    0    0    -1  
$EndComp
Text GLabel 3700 2200 1    50   Input ~ 0
T41_3V3
$Comp
L power:GND #PWR011
U 1 1 67B6A59D
P 3700 2500
F 0 "#PWR011" H 3700 2250 50  0001 C CNN
F 1 "GND" V 3700 2200 50  0000 L CNN
F 2 "" H 3700 2500 50  0001 C CNN
F 3 "" H 3700 2500 50  0001 C CNN
	1    3700 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 67B6DFED
P 12450 2300
F 0 "C1" H 12568 2346 50  0000 L CNN
F 1 "100uf" H 12568 2255 50  0000 L CNN
F 2 "0_my_footprints:CP_my100uf" H 12488 2150 50  0001 C CNN
F 3 "~" H 12450 2300 50  0001 C CNN
	1    12450 2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 67B6DFF3
P 12450 2450
F 0 "#PWR010" H 12450 2200 50  0001 C CNN
F 1 "GND" V 12450 2150 50  0000 L CNN
F 2 "" H 12450 2450 50  0001 C CNN
F 3 "" H 12450 2450 50  0001 C CNN
	1    12450 2450
	1    0    0    -1  
$EndComp
Text GLabel 11550 2200 3    50   Input ~ 0
RPI_MOSI
Text GLabel 11450 2200 3    50   Input ~ 0
RPI_LCD_CS
Text GLabel 11350 2200 3    50   Input ~ 0
RPI_LCD_DC
Text GLabel 11250 2200 3    50   Input ~ 0
RPI_MISO
$Comp
L power:GND #PWR07
U 1 1 67986521
P 11650 2200
F 0 "#PWR07" H 11650 1950 50  0001 C CNN
F 1 "GND" V 11650 1900 50  0000 L CNN
F 2 "" H 11650 2200 50  0001 C CNN
F 3 "" H 11650 2200 50  0001 C CNN
	1    11650 2200
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J4
U 1 1 67986515
P 11350 2000
F 0 "J4" V 11450 1600 50  0000 L CNN
F 1 "RPI_DISPLAY" V 11450 1900 50  0000 L CNN
F 2 "0_my_footprints:myJSTx08" H 11350 2000 50  0001 C CNN
F 3 "~" H 11350 2000 50  0001 C CNN
	1    11350 2000
	0    1    -1   0   
$EndComp
Connection ~ 12400 8750
Wire Wire Line
	12400 8750 12400 8700
$Comp
L Connector_Generic:Conn_01x08 J16
U 1 1 67B179B0
P 12000 9000
F 0 "J16" V 12150 9250 50  0000 L CNN
F 1 "LEDS" V 12150 8700 50  0000 L CNN
F 2 "0_my_footprints:myJSTx08" H 12000 9000 50  0001 C CNN
F 3 "~" H 12000 9000 50  0001 C CNN
	1    12000 9000
	0    -1   1    0   
$EndComp
Text GLabel 3700 5950 3    50   Input ~ 0
T41_3V3
Text GLabel 11900 3850 1    50   Input ~ 10
LED_RPI_I2S_RX
Text GLabel 12000 3850 1    50   Input ~ 10
LED_RPI_BUSY
Text GLabel 2500 2400 1    50   Input ~ 0
BTN_SENSE
$Comp
L Device:R R11
U 1 1 67AE46DD
P 2500 2600
F 0 "R11" H 2550 2600 50  0000 L CNN
F 1 "10K" V 2500 2600 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 2430 2600 50  0001 C CNN
F 3 "~" H 2500 2600 50  0001 C CNN
	1    2500 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 2450 2500 2400
$Comp
L power:GND #PWR0101
U 1 1 67AE6279
P 2500 2800
F 0 "#PWR0101" H 2500 2550 50  0001 C CNN
F 1 "GND" V 2500 2500 50  0000 L CNN
F 2 "" H 2500 2800 50  0001 C CNN
F 3 "" H 2500 2800 50  0001 C CNN
	1    2500 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 2750 2500 2800
Text Notes 11550 6700 0    50   ~ 0
The bold pins are differfent in Looper3 than previous\nLooper2.  They depend on #define LOOPER3\nin the circle/Rules.mk makefile to be used in the\n_prh audio and system libraries.
Text Notes 7800 3250 0    50   ~ 0
I2S BCLK and FCLK were WRONG in initial \nbuilt test mother_board, off by one pin to the left,\nGRRRR. with BCLK going to digital pin 22,\nand FCLK going to the BCLK pin!!! They\nhave now been corrected in the schematic\nand PCB which needs to be remade.  
Text GLabel 13300 2200 3    50   Input ~ 0
RPI_5V
Text GLabel 10950 2200 3    50   Input ~ 0
RPI_5V
Text GLabel 12450 2150 1    50   Input ~ 0
RPI_5V
Text Notes 11400 1350 0    50   ~ 0
RPI_5V is separated from teensies +5V.\nThe teensies get their power from the USB hub\nwhich has caps for each plug.  The RPI also gets\npower from the hub 5V rail but has its own cap\nand allows for a inline power switch so that it will be \npossible to plug the hub into the laptop/ipad without \nnecessarily powering up the rPI (which draws 1A+).
$Comp
L power:+5V #PWR018
U 1 1 67B5E392
P 7600 4000
F 0 "#PWR018" H 7600 3850 50  0001 C CNN
F 1 "+5V" V 7600 4100 50  0000 L CNN
F 2 "" H 7600 4000 50  0001 C CNN
F 3 "" H 7600 4000 50  0001 C CNN
	1    7600 4000
	1    0    0    -1  
$EndComp
Text Notes 5150 3600 0    50   ~ 0
The teensy 5V's are tied together so that both\nwill run if the 4.1 is plugged directly into the laptop.
Text GLabel 13400 5200 3    50   Input ~ 0
RPI_5V
Text GLabel 13500 5200 3    50   Input ~ 0
RPI_5V
Text Notes 8200 6350 0    50   ~ 0
Built card had I2S_RXB hooked up wrong to gpio5 \nBuilt card, schematic and PCB design modified to\ncorrect pin, gpio6\n
Text Notes 9650 4100 0    50   ~ 0
Carnival of errors.  Built card had incorrect\nsymbol, with the audio pins showing:\n29 - LINE_IN_L\n30 - GND\n31 - LINE_IN_R\n32 - LINE_OUT_R\n33 - LINE_OUT_L\nThe footprint, built board, schematic\nand PCB design have been fixed as\nshown here.\n\n  
Text GLabel 9200 4350 1    50   Input ~ 0
LINE_IN_R
$Comp
L power:GND #PWR020
U 1 1 67B9218D
P 9400 4350
F 0 "#PWR020" H 9400 4100 50  0001 C CNN
F 1 "GND" V 9400 4050 50  0000 L CNN
F 2 "" H 9400 4350 50  0001 C CNN
F 3 "" H 9400 4350 50  0001 C CNN
	1    9400 4350
	-1   0    0    1   
$EndComp
$Comp
L 0_my_teensy:teensyAudioRevD_WithAudio U1
U 1 1 67B4E93C
P 8150 4700
F 0 "U1" H 7550 4700 60  0000 L CNN
F 1 "teensyAudioRevD_WithAudio" H 7750 4700 60  0000 L CNN
F 2 "0_my_teensy:audioShieldRevD_audioPinsStack" V 9100 4650 60  0001 C CNN
F 3 "" V 9100 4650 60  0000 C CNN
	1    8150 4700
	1    0    0    -1  
$EndComp
$EndSCHEMATC

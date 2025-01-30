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
L 0_my_teensy:myTeensy4.1 U?
U 1 1 679426B6
P 4650 3950
F 0 "U?" H 4550 3900 50  0000 L CNN
F 1 "myTeensy4.1" H 4550 3800 50  0000 L CNN
F 2 "" H 4350 3050 50  0001 C CNN
F 3 "" H 4350 3050 50  0001 C CNN
	1    4650 3950
	1    0    0    -1  
$EndComp
$Comp
L 0_my_symbols:rpi_connector J?
U 1 1 67943AF8
P 11000 3900
F 0 "J?" H 10650 3900 50  0000 L CNN
F 1 "rpi_connector" H 10800 3900 50  0000 L CNN
F 2 "" H 10900 3800 50  0001 C CNN
F 3 "" H 10900 3800 50  0001 C CNN
	1    11000 3900
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J?
U 1 1 679456F8
P 6100 1050
F 0 "J?" V 6200 650 50  0000 L CNN
F 1 "TE_DISPLAY" V 6200 1000 50  0000 L CNN
F 2 "" H 6100 1050 50  0001 C CNN
F 3 "~" H 6100 1050 50  0001 C CNN
	1    6100 1050
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J?
U 1 1 67946D3E
P 5000 1050
F 0 "J?" V 5100 800 50  0000 L CNN
F 1 "ROTARIES" V 5100 950 50  0000 L CNN
F 2 "" H 5000 1050 50  0001 C CNN
F 3 "~" H 5000 1050 50  0001 C CNN
	1    5000 1050
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6794C62E
P 4800 1250
F 0 "#PWR?" H 4800 1000 50  0001 C CNN
F 1 "GND" V 4800 950 50  0000 L CNN
F 2 "" H 4800 1250 50  0001 C CNN
F 3 "" H 4800 1250 50  0001 C CNN
	1    4800 1250
	1    0    0    -1  
$EndComp
Text GLabel 4900 1250 3    50   Input ~ 0
T41_SCL
Text GLabel 5000 1250 3    50   Input ~ 0
T41_SDA
Text GLabel 5100 1250 3    50   Input ~ 0
ROT_INT
$Comp
L Connector_Generic:Conn_01x06 J?
U 1 1 67952F34
P 4000 1050
F 0 "J?" V 4100 700 50  0000 L CNN
F 1 "ROW_BOARDS" V 4100 800 50  0000 L CNN
F 2 "" H 4000 1050 50  0001 C CNN
F 3 "~" H 4000 1050 50  0001 C CNN
	1    4000 1050
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67955DCC
P 4100 1250
F 0 "#PWR?" H 4100 1000 50  0001 C CNN
F 1 "GND" V 4100 950 50  0000 L CNN
F 2 "" H 4100 1250 50  0001 C CNN
F 3 "" H 4100 1250 50  0001 C CNN
	1    4100 1250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6797D5D1
P 6500 1250
F 0 "#PWR?" H 6500 1000 50  0001 C CNN
F 1 "GND" V 6500 950 50  0000 L CNN
F 2 "" H 6500 1250 50  0001 C CNN
F 3 "" H 6500 1250 50  0001 C CNN
	1    6500 1250
	1    0    0    -1  
$EndComp
Text GLabel 5900 1250 3    50   Input ~ 0
T41_T_CS
Text GLabel 6000 1250 3    50   Input ~ 0
T41_SCLK
Text GLabel 6100 1250 3    50   Input ~ 0
T41_MISO
Text GLabel 6200 1250 3    50   Input ~ 0
T41_LCD_DC
Text GLabel 6300 1250 3    50   Input ~ 0
T41_LCD_CS
Text GLabel 6400 1250 3    50   Input ~ 0
T41_MOSI
$Comp
L Connector_Generic:Conn_01x08 J?
U 1 1 67986515
P 10900 1250
F 0 "J?" V 11000 850 50  0000 L CNN
F 1 "RPI_DISPLAY" V 11000 1150 50  0000 L CNN
F 2 "" H 10900 1250 50  0001 C CNN
F 3 "~" H 10900 1250 50  0001 C CNN
	1    10900 1250
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 6798651B
P 10600 1450
F 0 "#PWR?" H 10600 1300 50  0001 C CNN
F 1 "+5V" V 10600 1550 50  0000 L CNN
F 2 "" H 10600 1450 50  0001 C CNN
F 3 "" H 10600 1450 50  0001 C CNN
	1    10600 1450
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67986521
P 11300 1450
F 0 "#PWR?" H 11300 1200 50  0001 C CNN
F 1 "GND" V 11300 1150 50  0000 L CNN
F 2 "" H 11300 1450 50  0001 C CNN
F 3 "" H 11300 1450 50  0001 C CNN
	1    11300 1450
	1    0    0    -1  
$EndComp
Text GLabel 10700 1450 3    50   Input ~ 0
RPI_T_CS
Text GLabel 10800 1450 3    50   Input ~ 0
RPI_SCLK
Text GLabel 10900 1450 3    50   Input ~ 0
RPI_MISO
Text GLabel 11000 1450 3    50   Input ~ 0
RPI_LCD_DC
Text GLabel 11100 1450 3    50   Input ~ 0
RPI_LCD_CS
Text GLabel 11200 1450 3    50   Input ~ 0
RPI_MOSI
Text GLabel 8500 6550 1    50   Input ~ 0
LED_RPI_RUN
Text GLabel 8600 6550 1    50   Input ~ 0
LED_RPI_READY
Text GLabel 8800 6550 1    50   Input ~ 0
LED_RPI_I2S_TX
Text GLabel 8900 6550 1    50   Input ~ 0
LED_RPI_I2S_RX
Text GLabel 10450 4600 3    50   Input ~ 0
LED_RPI_I2S_RX
Text GLabel 10250 4600 3    50   Input ~ 0
LED_RPI_I2S_TX
Text GLabel 11450 4600 3    50   Input ~ 0
I2S_BCLK
Text GLabel 10250 3250 1    50   Input ~ 0
I2S_FCLK
$Comp
L Connector_Generic:Conn_01x01 J?
U 1 1 679C02F5
P 8450 3950
F 0 "J?" H 8350 3700 50  0000 C CNN
F 1 "I2S_TXB" H 8368 3816 50  0000 C CNN
F 2 "" H 8450 3950 50  0001 C CNN
F 3 "~" H 8450 3950 50  0001 C CNN
	1    8450 3950
	-1   0    0    1   
$EndComp
Text GLabel 8650 3950 2    50   Input ~ 0
I2S_TXB
Text GLabel 10150 4600 3    50   Input ~ 0
I2S_TXB
Text GLabel 10050 4600 3    50   Input ~ 0
I2S_RXB
Text GLabel 7600 4650 3    50   Input ~ 0
I2S_RXB
Text GLabel 7500 3200 1    50   Input ~ 0
I2S_FCLK
Text GLabel 7400 3200 1    50   Input ~ 0
I2S_BCLK
Text GLabel 8700 6550 1    50   Input ~ 0
LED_AUDIO_ALIVE
Text GLabel 7400 4650 3    50   Input ~ 0
LED_AUDIO_ALIVE
$Comp
L Connector_Generic:Conn_01x01 J?
U 1 1 679CE3ED
P 9800 3950
F 0 "J?" H 9750 4200 50  0000 C CNN
F 1 "RPI_RUN" H 9750 4100 50  0000 C CNN
F 2 "" H 9800 3950 50  0001 C CNN
F 3 "~" H 9800 3950 50  0001 C CNN
	1    9800 3950
	1    0    0    -1  
$EndComp
Text GLabel 9600 3950 0    50   Input ~ 0
RPI_RUN
Text GLabel 10950 4600 3    50   Input ~ 0
RPI_READY
$Comp
L 0_my_teensy:teensyAudioRevD U?
U 1 1 67941570
P 7450 3900
F 0 "U?" H 7200 3900 60  0000 L CNN
F 1 "teensyAudioRevD" H 6800 3700 60  0000 L CNN
F 2 "" V 8400 3850 60  0000 C CNN
F 3 "" V 8400 3850 60  0000 C CNN
	1    7450 3900
	1    0    0    -1  
$EndComp
Text GLabel 10850 3250 1    50   Input ~ 0
RPI_SCLK
Text GLabel 10950 3250 1    50   Input ~ 0
RPI_MISO
Text GLabel 11050 3250 1    50   Input ~ 0
RPI_MOSI
Text Notes 5900 900  0    50   ~ 0
ILI9488_T3
Text GLabel 5050 5100 3    50   Input ~ 0
T41_SCLK?
Text GLabel 4850 5100 3    50   Input ~ 0
T41_MISO
Text GLabel 4750 5100 3    50   Input ~ 0
T41_MOSI
Text GLabel 4150 5100 3    50   Input ~ 0
LED_RPI_RUN
Text GLabel 4250 5100 3    50   Input ~ 0
LED_RPI_READY
Text Notes 1450 4250 0    50   ~ 0
T41 standard SPI SCK\nconflicts with ONBOARD_LED.\nI will start by leaving it attached\nand using a different pin for\nthe alive led, but it would probably\nbe better on the other side of the\nboard near mosi and CS\n
Text GLabel 4550 5100 3    50   Input ~ 0
T41_LCD_DC
Text GLabel 4650 5100 3    50   Input ~ 0
T41_LCD_CS
Text GLabel 4450 5100 3    50   Input ~ 0
T41_T_CS
Text GLabel 8400 6550 1    50   Input ~ 0
LED_T3_ALIVE
Text GLabel 4050 5100 3    50   Input ~ 0
LED_T3_ALIVE
Text GLabel 10850 4600 3    50   Input ~ 0
RPI_LCD_CS
Text GLabel 10750 4600 3    50   Input ~ 0
RPI_T_CS
Text GLabel 11650 3250 1    50   Input ~ 0
RPI_LCD_DC
$Comp
L power:GND #PWR?
U 1 1 67A37846
P 11750 4600
F 0 "#PWR?" H 11750 4350 50  0001 C CNN
F 1 "GND" V 11750 4300 50  0000 L CNN
F 2 "" H 11750 4600 50  0001 C CNN
F 3 "" H 11750 4600 50  0001 C CNN
	1    11750 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A37CAF
P 11350 4600
F 0 "#PWR?" H 11350 4350 50  0001 C CNN
F 1 "GND" V 11350 4300 50  0000 L CNN
F 2 "" H 11350 4600 50  0001 C CNN
F 3 "" H 11350 4600 50  0001 C CNN
	1    11350 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A37F8C
P 11050 4600
F 0 "#PWR?" H 11050 4350 50  0001 C CNN
F 1 "GND" V 11050 4300 50  0000 L CNN
F 2 "" H 11050 4600 50  0001 C CNN
F 3 "" H 11050 4600 50  0001 C CNN
	1    11050 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A38141
P 10550 4600
F 0 "#PWR?" H 10550 4350 50  0001 C CNN
F 1 "GND" V 10550 4300 50  0000 L CNN
F 2 "" H 10550 4600 50  0001 C CNN
F 3 "" H 10550 4600 50  0001 C CNN
	1    10550 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A38257
P 10350 4600
F 0 "#PWR?" H 10350 4350 50  0001 C CNN
F 1 "GND" V 10350 4300 50  0000 L CNN
F 2 "" H 10350 4600 50  0001 C CNN
F 3 "" H 10350 4600 50  0001 C CNN
	1    10350 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A38A35
P 10050 3250
F 0 "#PWR?" H 10050 3000 50  0001 C CNN
F 1 "GND" V 10050 2950 50  0000 L CNN
F 2 "" H 10050 3250 50  0001 C CNN
F 3 "" H 10050 3250 50  0001 C CNN
	1    10050 3250
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A38E9E
P 10750 3250
F 0 "#PWR?" H 10750 3000 50  0001 C CNN
F 1 "GND" V 10750 2950 50  0000 L CNN
F 2 "" H 10750 3250 50  0001 C CNN
F 3 "" H 10750 3250 50  0001 C CNN
	1    10750 3250
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A392BE
P 11550 3250
F 0 "#PWR?" H 11550 3000 50  0001 C CNN
F 1 "GND" V 11550 2950 50  0000 L CNN
F 2 "" H 11550 3250 50  0001 C CNN
F 3 "" H 11550 3250 50  0001 C CNN
	1    11550 3250
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A3A486
P 7000 3200
F 0 "#PWR?" H 7000 2950 50  0001 C CNN
F 1 "GND" V 7000 2900 50  0000 L CNN
F 2 "" H 7000 3200 50  0001 C CNN
F 3 "" H 7000 3200 50  0001 C CNN
	1    7000 3200
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A3AA10
P 6900 4650
F 0 "#PWR?" H 6900 4400 50  0001 C CNN
F 1 "GND" V 6900 4350 50  0000 L CNN
F 2 "" H 6900 4650 50  0001 C CNN
F 3 "" H 6900 4650 50  0001 C CNN
	1    6900 4650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A3B5C4
P 3550 5100
F 0 "#PWR?" H 3550 4850 50  0001 C CNN
F 1 "GND" V 3550 4800 50  0000 L CNN
F 2 "" H 3550 5100 50  0001 C CNN
F 3 "" H 3550 5100 50  0001 C CNN
	1    3550 5100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A3C2A4
P 3650 3050
F 0 "#PWR?" H 3650 2800 50  0001 C CNN
F 1 "GND" V 3650 2750 50  0000 L CNN
F 2 "" H 3650 3050 50  0001 C CNN
F 3 "" H 3650 3050 50  0001 C CNN
	1    3650 3050
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A3C67C
P 4950 3050
F 0 "#PWR?" H 4950 2800 50  0001 C CNN
F 1 "GND" V 4950 2750 50  0000 L CNN
F 2 "" H 4950 3050 50  0001 C CNN
F 3 "" H 4950 3050 50  0001 C CNN
	1    4950 3050
	-1   0    0    1   
$EndComp
Text GLabel 5550 5100 3    50   Input ~ 0
T41_RX7
Text GLabel 5450 5100 3    50   Input ~ 0
T41_TX7
Text GLabel 7100 4650 3    50   Input ~ 0
T41_RX7
Text GLabel 7000 4650 3    50   Input ~ 0
T41_TX7
Text GLabel 5750 3050 1    50   Input ~ 0
T41_RX8
Text GLabel 5650 3050 1    50   Input ~ 0
T41_TX8
Text GLabel 11650 4600 3    50   Input ~ 0
T41_RX8
Text GLabel 11550 4600 3    50   Input ~ 0
T41_TX8
$Comp
L power:GND #PWR?
U 1 1 67A5DC81
P 2900 1250
F 0 "#PWR?" H 2900 1000 50  0001 C CNN
F 1 "GND" V 2900 950 50  0000 L CNN
F 2 "" H 2900 1250 50  0001 C CNN
F 3 "" H 2900 1250 50  0001 C CNN
	1    2900 1250
	1    0    0    -1  
$EndComp
Text Notes 10800 1100 0    50   ~ 0
ILI9488
$Comp
L Device:R R?
U 1 1 64CCBE5B
P 4550 6450
F 0 "R?" V 4650 6400 50  0000 L CNN
F 1 "220" V 4550 6450 50  0000 C CNN
F 2 "" V 4480 6450 50  0001 C CNN
F 3 "~" H 4550 6450 50  0001 C CNN
	1    4550 6450
	0    -1   -1   0   
$EndComp
Text GLabel 4950 6450 2    50   Input ~ 0
RPI_RUN
Text GLabel 4400 6450 0    50   Input ~ 0
SENS_PI_RUN
$Comp
L Transistor_BJT:BC547 Q?
U 1 1 64CF1712
P 4750 6750
F 0 "Q?" H 4941 6796 50  0000 L CNN
F 1 "BC547" H 4941 6705 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4950 6675 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 4750 6750 50  0001 L CNN
	1    4750 6750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 64CF464E
P 4850 7050
F 0 "#PWR?" H 4850 6800 50  0001 C CNN
F 1 "GND" H 4855 6877 50  0000 C CNN
F 2 "" H 4850 7050 50  0001 C CNN
F 3 "" H 4850 7050 50  0001 C CNN
	1    4850 7050
	1    0    0    -1  
$EndComp
Text GLabel 4250 6750 0    50   Input ~ 0
PI_REBOOT
Wire Wire Line
	4700 6450 4850 6450
Wire Wire Line
	4850 6550 4850 6450
Connection ~ 4850 6450
Wire Wire Line
	4850 6450 4950 6450
Wire Wire Line
	4850 6950 4850 7050
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 67AB91F7
P 3000 1050
F 0 "J?" V 3100 700 50  0000 R CNN
F 1 "DBG_SERIAL" V 3100 750 50  0000 L CNN
F 2 "" H 3000 1050 50  0001 C CNN
F 3 "~" H 3000 1050 50  0001 C CNN
	1    3000 1050
	0    -1   -1   0   
$EndComp
Text Notes 2800 850  0    50   ~ 0
FTDI USB Serial
Text GLabel 4450 3050 1    50   Input ~ 0
ROT_INT
Text GLabel 4350 3050 1    50   Input ~ 0
T41_SDA
Text GLabel 4250 3050 1    50   Input ~ 0
T41_SCL
Text GLabel 3750 3050 1    50   Input ~ 0
T41_3V3
Text GLabel 3200 1250 3    50   Input ~ 0
T41_3V3
Text GLabel 5200 1250 3    50   Input ~ 0
T41_3V3
$Comp
L Connector_Generic:Conn_01x08 J?
U 1 1 67B2FCBF
P 8600 6750
F 0 "J?" V 8700 6350 50  0000 L CNN
F 1 "EXT_LEDS" V 8700 6650 50  0000 L CNN
F 2 "" H 8600 6750 50  0001 C CNN
F 3 "~" H 8600 6750 50  0001 C CNN
	1    8600 6750
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67B33AE6
P 8300 6550
F 0 "#PWR?" H 8300 6300 50  0001 C CNN
F 1 "GND" V 8300 6250 50  0000 L CNN
F 2 "" H 8300 6550 50  0001 C CNN
F 3 "" H 8300 6550 50  0001 C CNN
	1    8300 6550
	-1   0    0    1   
$EndComp
Text GLabel 5250 3050 1    50   Input ~ 0
SENS_PI_RUN
Text GLabel 5350 3050 1    50   Input ~ 0
PI_REBOOT
Text GLabel 5450 3050 1    50   Input ~ 0
RPI_READY
Text GLabel 2300 6100 1    50   Input ~ 0
T41_SCL
Text GLabel 2200 6100 1    50   Input ~ 0
T41_SDA
$Comp
L Device:R R?
U 1 1 67964E23
P 2200 6250
F 0 "R?" H 2250 6250 50  0000 L CNN
F 1 "1K" V 2200 6250 50  0000 C CNN
F 2 "" V 2130 6250 50  0001 C CNN
F 3 "~" H 2200 6250 50  0001 C CNN
	1    2200 6250
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 67965E12
P 2300 6250
F 0 "R?" H 2150 6250 50  0000 L CNN
F 1 "1K" V 2300 6250 50  0000 C CNN
F 2 "" V 2230 6250 50  0001 C CNN
F 3 "~" H 2300 6250 50  0001 C CNN
	1    2300 6250
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67968FB3
P 2250 6500
F 0 "#PWR?" H 2250 6250 50  0001 C CNN
F 1 "GND" H 2255 6327 50  0000 C CNN
F 2 "" H 2250 6500 50  0001 C CNN
F 3 "" H 2250 6500 50  0001 C CNN
	1    2250 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 6400 2200 6500
Wire Wire Line
	2200 6500 2250 6500
Wire Wire Line
	2300 6400 2300 6500
Wire Wire Line
	2300 6500 2250 6500
Connection ~ 2250 6500
$Comp
L Device:R R?
U 1 1 6796F63B
P 4400 6750
F 0 "R?" V 4500 6700 50  0000 L CNN
F 1 "1K" V 4400 6750 50  0000 C CNN
F 2 "" V 4330 6750 50  0001 C CNN
F 3 "~" H 4400 6750 50  0001 C CNN
	1    4400 6750
	0    -1   -1   0   
$EndComp
Text GLabel 4200 1250 3    50   Input ~ 0
BTN_CLK
Text GLabel 3000 1250 3    50   Input ~ 0
T41_TX1
Text GLabel 3100 1250 3    50   Input ~ 0
T41_RX1
Text GLabel 3750 5100 3    50   Input ~ 0
T41_TX1
Text GLabel 3650 5100 3    50   Input ~ 0
T41_RX1
Text GLabel 3900 1250 3    50   Input ~ 0
LED_DIN
Text GLabel 4000 1250 3    50   Input ~ 0
BTN_DIN
Text GLabel 4750 3050 1    50   Input ~ 0
BTN_CLK
Text GLabel 4150 3050 1    50   Input ~ 0
LED_DIN
Text GLabel 4650 3050 1    50   Input ~ 0
BTN_DIN
Text GLabel 4550 3050 1    50   Input ~ 0
BTN_SENSE
Text GLabel 4300 1250 3    50   Input ~ 0
T41_3V3
Text GLabel 3550 3050 1    50   Input ~ 0
T41_5V
Text GLabel 3800 1250 3    50   Input ~ 0
BTN_SENSE
Text Notes 1800 5550 0    50   ~ 0
Rotary mcp23017 needs\n1K pullups on SDA & SCL
Text GLabel 5800 1250 3    50   Input ~ 0
T41_5V
$EndSCHEMATC

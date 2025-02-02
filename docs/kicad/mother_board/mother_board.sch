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
L 0_my_teensy:myTeensy4.1 U1
U 1 1 679426B6
P 2950 4250
F 0 "U1" H 2850 4200 50  0000 L CNN
F 1 "myTeensy4.1" H 2850 4100 50  0000 L CNN
F 2 "0_my_teensy:teensy41" H 2650 3350 50  0001 C CNN
F 3 "" H 2650 3350 50  0001 C CNN
	1    2950 4250
	1    0    0    -1  
$EndComp
$Comp
L 0_my_symbols:rpi_connector J9
U 1 1 67943AF8
P 9300 4200
F 0 "J9" H 8950 4200 50  0000 L CNN
F 1 "rpi_connector" H 9100 4200 50  0000 L CNN
F 2 "0_my_footprints2:rpi_zero_2w" H 9200 4100 50  0001 C CNN
F 3 "" H 9200 4100 50  0001 C CNN
	1    9300 4200
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J4
U 1 1 679456F8
P 5250 1700
F 0 "J4" V 5350 1300 50  0000 L CNN
F 1 "TE_DISPLAY" V 5350 1650 50  0000 L CNN
F 2 "0_my_footprints:myJSTx08" H 5250 1700 50  0001 C CNN
F 3 "~" H 5250 1700 50  0001 C CNN
	1    5250 1700
	0    1    -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J3
U 1 1 67946D3E
P 4150 1700
F 0 "J3" V 4250 1450 50  0000 L CNN
F 1 "ROTARIES" V 4250 1600 50  0000 L CNN
F 2 "0_my_footprints:myJSTx05" H 4150 1700 50  0001 C CNN
F 3 "~" H 4150 1700 50  0001 C CNN
	1    4150 1700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR05
U 1 1 6794C62E
P 3950 1900
F 0 "#PWR05" H 3950 1650 50  0001 C CNN
F 1 "GND" V 3950 1600 50  0000 L CNN
F 2 "" H 3950 1900 50  0001 C CNN
F 3 "" H 3950 1900 50  0001 C CNN
	1    3950 1900
	1    0    0    -1  
$EndComp
Text GLabel 4050 1900 3    50   Input ~ 0
T41_SCL
Text GLabel 4150 1900 3    50   Input ~ 0
T41_SDA
Text GLabel 4250 1900 3    50   Input ~ 0
ROT_INT
$Comp
L Connector_Generic:Conn_01x06 J2
U 1 1 67952F34
P 3150 1700
F 0 "J2" V 3250 1350 50  0000 L CNN
F 1 "ROW_BOARDS" V 3250 1450 50  0000 L CNN
F 2 "0_my_footprints:myJSTx06" H 3150 1700 50  0001 C CNN
F 3 "~" H 3150 1700 50  0001 C CNN
	1    3150 1700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 67955DCC
P 3250 1900
F 0 "#PWR04" H 3250 1650 50  0001 C CNN
F 1 "GND" V 3250 1600 50  0000 L CNN
F 2 "" H 3250 1900 50  0001 C CNN
F 3 "" H 3250 1900 50  0001 C CNN
	1    3250 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 6797D5D1
P 5550 1900
F 0 "#PWR08" H 5550 1650 50  0001 C CNN
F 1 "GND" V 5550 1600 50  0000 L CNN
F 2 "" H 5550 1900 50  0001 C CNN
F 3 "" H 5550 1900 50  0001 C CNN
	1    5550 1900
	1    0    0    -1  
$EndComp
Text GLabel 4950 1900 3    50   Input ~ 0
T41_T_CS
Text GLabel 5050 1900 3    50   Input ~ 0
T41_SCLK
Text GLabel 5150 1900 3    50   Input ~ 0
T41_MISO
Text GLabel 5250 1900 3    50   Input ~ 0
T41_LCD_DC
Text GLabel 5350 1900 3    50   Input ~ 0
T41_LCD_CS
Text GLabel 5450 1900 3    50   Input ~ 0
T41_MOSI
$Comp
L Connector_Generic:Conn_01x08 J8
U 1 1 67986515
P 8850 1700
F 0 "J8" V 8950 1300 50  0000 L CNN
F 1 "RPI_DISPLAY" V 8950 1600 50  0000 L CNN
F 2 "0_my_footprints:myJSTx08" H 8850 1700 50  0001 C CNN
F 3 "~" H 8850 1700 50  0001 C CNN
	1    8850 1700
	0    1    -1   0   
$EndComp
$Comp
L power:+5V #PWR013
U 1 1 6798651B
P 8450 1900
F 0 "#PWR013" H 8450 1750 50  0001 C CNN
F 1 "+5V" V 8450 2000 50  0000 L CNN
F 2 "" H 8450 1900 50  0001 C CNN
F 3 "" H 8450 1900 50  0001 C CNN
	1    8450 1900
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR017
U 1 1 67986521
P 9150 1900
F 0 "#PWR017" H 9150 1650 50  0001 C CNN
F 1 "GND" V 9150 1600 50  0000 L CNN
F 2 "" H 9150 1900 50  0001 C CNN
F 3 "" H 9150 1900 50  0001 C CNN
	1    9150 1900
	1    0    0    -1  
$EndComp
Text GLabel 8550 1900 3    50   Input ~ 0
RPI_T_CS
Text GLabel 8650 1900 3    50   Input ~ 0
RPI_SCLK
Text GLabel 8750 1900 3    50   Input ~ 0
RPI_MISO
Text GLabel 8850 1900 3    50   Input ~ 0
RPI_LCD_DC
Text GLabel 8950 1900 3    50   Input ~ 0
RPI_LCD_CS
Text GLabel 9050 1900 3    50   Input ~ 0
RPI_MOSI
Text GLabel 8750 4900 3    50   Input ~ 0
LED_RPI_I2S_RX
Text GLabel 8550 4900 3    50   Input ~ 0
LED_RPI_I2S_TX
Text GLabel 9750 4900 3    50   Input ~ 0
I2S_BCLK
Text GLabel 8550 3550 1    50   Input ~ 0
I2S_FCLK
Text GLabel 7050 4250 2    50   Input ~ 0
I2S_TXB
Text GLabel 8450 4900 3    50   Input ~ 0
I2S_TXB
Text GLabel 8350 4900 3    50   Input ~ 0
I2S_RXB
Text GLabel 5900 4950 3    50   Input ~ 0
I2S_RXB
Text GLabel 5800 3500 1    50   Input ~ 0
I2S_FCLK
Text GLabel 5700 3500 1    50   Input ~ 0
I2S_BCLK
Text GLabel 5700 4950 3    50   Input ~ 0
LED_AUDIO_BUSY
Text GLabel 7900 4250 0    50   Input ~ 0
RPI_RUN
Text GLabel 9250 4900 3    50   Input ~ 0
RPI_READY
$Comp
L 0_my_teensy:teensyAudioRevD U2
U 1 1 67941570
P 5750 4200
F 0 "U2" H 5500 4200 60  0000 L CNN
F 1 "teensyAudioRevD" H 5100 4000 60  0000 L CNN
F 2 "0_my_teensy:revDTeensy4Stack" V 6700 4150 60  0001 C CNN
F 3 "" V 6700 4150 60  0000 C CNN
	1    5750 4200
	1    0    0    -1  
$EndComp
Text GLabel 9150 3550 1    50   Input ~ 0
RPI_SCLK
Text GLabel 9250 3550 1    50   Input ~ 0
RPI_MISO
Text GLabel 9350 3550 1    50   Input ~ 0
RPI_MOSI
Text Notes 4950 1550 0    50   ~ 0
ILI9488_T3
Text GLabel 3350 5400 3    50   Input ~ 0
T41_SCLK
Text GLabel 3150 5400 3    50   Input ~ 0
T41_MISO
Text GLabel 3050 5400 3    50   Input ~ 0
T41_MOSI
Text GLabel 2450 5400 3    50   Input ~ 0
LED_RPI_RUN
Text GLabel 2550 5400 3    50   Input ~ 0
LED_RPI_READY
Text Notes 900  1050 0    50   ~ 0
T41 standard SPI SCK is same as ONBOARD_LED.\nI am using a different pin for the display SCLK\non the other side of the board near MISO/MOSI\n
Text GLabel 2850 5400 3    50   Input ~ 0
T41_LCD_DC
Text GLabel 2950 5400 3    50   Input ~ 0
T41_LCD_CS
Text GLabel 2750 5400 3    50   Input ~ 0
T41_T_CS
Text GLabel 2350 5400 3    50   Input ~ 0
LED_T3_BUSY
Text GLabel 9150 4900 3    50   Input ~ 0
RPI_LCD_CS
Text GLabel 9050 4900 3    50   Input ~ 0
RPI_T_CS
Text GLabel 9950 3550 1    50   Input ~ 0
RPI_LCD_DC
$Comp
L power:GND #PWR023
U 1 1 67A37846
P 10050 4900
F 0 "#PWR023" H 10050 4650 50  0001 C CNN
F 1 "GND" V 10050 4600 50  0000 L CNN
F 2 "" H 10050 4900 50  0001 C CNN
F 3 "" H 10050 4900 50  0001 C CNN
	1    10050 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR019
U 1 1 67A37CAF
P 9650 4900
F 0 "#PWR019" H 9650 4650 50  0001 C CNN
F 1 "GND" V 9650 4600 50  0000 L CNN
F 2 "" H 9650 4900 50  0001 C CNN
F 3 "" H 9650 4900 50  0001 C CNN
	1    9650 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR018
U 1 1 67A37F8C
P 9350 4900
F 0 "#PWR018" H 9350 4650 50  0001 C CNN
F 1 "GND" V 9350 4600 50  0000 L CNN
F 2 "" H 9350 4900 50  0001 C CNN
F 3 "" H 9350 4900 50  0001 C CNN
	1    9350 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 67A38141
P 8850 4900
F 0 "#PWR015" H 8850 4650 50  0001 C CNN
F 1 "GND" V 8850 4600 50  0000 L CNN
F 2 "" H 8850 4900 50  0001 C CNN
F 3 "" H 8850 4900 50  0001 C CNN
	1    8850 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 67A38257
P 8650 4900
F 0 "#PWR014" H 8650 4650 50  0001 C CNN
F 1 "GND" V 8650 4600 50  0000 L CNN
F 2 "" H 8650 4900 50  0001 C CNN
F 3 "" H 8650 4900 50  0001 C CNN
	1    8650 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 67A38A35
P 8350 3550
F 0 "#PWR012" H 8350 3300 50  0001 C CNN
F 1 "GND" V 8350 3250 50  0000 L CNN
F 2 "" H 8350 3550 50  0001 C CNN
F 3 "" H 8350 3550 50  0001 C CNN
	1    8350 3550
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR016
U 1 1 67A38E9E
P 9050 3550
F 0 "#PWR016" H 9050 3300 50  0001 C CNN
F 1 "GND" V 9050 3250 50  0000 L CNN
F 2 "" H 9050 3550 50  0001 C CNN
F 3 "" H 9050 3550 50  0001 C CNN
	1    9050 3550
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR021
U 1 1 67A392BE
P 9850 3550
F 0 "#PWR021" H 9850 3300 50  0001 C CNN
F 1 "GND" V 9850 3250 50  0000 L CNN
F 2 "" H 9850 3550 50  0001 C CNN
F 3 "" H 9850 3550 50  0001 C CNN
	1    9850 3550
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR010
U 1 1 67A3A486
P 5300 3500
F 0 "#PWR010" H 5300 3250 50  0001 C CNN
F 1 "GND" V 5300 3200 50  0000 L CNN
F 2 "" H 5300 3500 50  0001 C CNN
F 3 "" H 5300 3500 50  0001 C CNN
	1    5300 3500
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR09
U 1 1 67A3AA10
P 5200 4950
F 0 "#PWR09" H 5200 4700 50  0001 C CNN
F 1 "GND" V 5200 4650 50  0000 L CNN
F 2 "" H 5200 4950 50  0001 C CNN
F 3 "" H 5200 4950 50  0001 C CNN
	1    5200 4950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 67A3B5C4
P 1850 5400
F 0 "#PWR02" H 1850 5150 50  0001 C CNN
F 1 "GND" V 1850 5100 50  0000 L CNN
F 2 "" H 1850 5400 50  0001 C CNN
F 3 "" H 1850 5400 50  0001 C CNN
	1    1850 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 67A3C2A4
P 1950 3350
F 0 "#PWR03" H 1950 3100 50  0001 C CNN
F 1 "GND" V 1950 3050 50  0000 L CNN
F 2 "" H 1950 3350 50  0001 C CNN
F 3 "" H 1950 3350 50  0001 C CNN
	1    1950 3350
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 67A3C67C
P 3250 3350
F 0 "#PWR06" H 3250 3100 50  0001 C CNN
F 1 "GND" V 3250 3050 50  0000 L CNN
F 2 "" H 3250 3350 50  0001 C CNN
F 3 "" H 3250 3350 50  0001 C CNN
	1    3250 3350
	-1   0    0    1   
$EndComp
Text GLabel 3850 5400 3    50   Input ~ 0
T41_RX7
Text GLabel 3750 5400 3    50   Input ~ 0
T41_TX7
Text GLabel 5400 4950 3    50   Input ~ 0
T41_RX8
Text GLabel 5300 4950 3    50   Input ~ 0
T41_TX8
Text GLabel 4050 3350 1    50   Input ~ 0
T41_RX8
Text GLabel 3950 3350 1    50   Input ~ 0
T41_TX8
Text GLabel 9950 4900 3    50   Input ~ 0
T41_RX7
Text GLabel 9850 4900 3    50   Input ~ 0
T41_TX7
$Comp
L power:GND #PWR01
U 1 1 67A5DC81
P 1300 1900
F 0 "#PWR01" H 1300 1650 50  0001 C CNN
F 1 "GND" V 1300 1600 50  0000 L CNN
F 2 "" H 1300 1900 50  0001 C CNN
F 3 "" H 1300 1900 50  0001 C CNN
	1    1300 1900
	1    0    0    -1  
$EndComp
Text Notes 8650 1550 0    50   ~ 0
ILI9488
$Comp
L Device:R R4
U 1 1 64CCBE5B
P 3600 6850
F 0 "R4" V 3700 6800 50  0000 L CNN
F 1 "220" V 3600 6850 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 3530 6850 50  0001 C CNN
F 3 "~" H 3600 6850 50  0001 C CNN
	1    3600 6850
	0    -1   -1   0   
$EndComp
Text GLabel 4000 6850 2    50   Input ~ 0
RPI_RUN
Text GLabel 3450 6850 0    50   Input ~ 0
SENS_PI_RUN
$Comp
L Transistor_BJT:BC547 Q1
U 1 1 64CF1712
P 3800 7150
F 0 "Q1" H 3991 7196 50  0000 L CNN
F 1 "BC547" H 3991 7105 50  0000 L CNN
F 2 "0_my_footprints:myTransistor" H 4000 7075 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 3800 7150 50  0001 L CNN
	1    3800 7150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 64CF464E
P 3900 7450
F 0 "#PWR07" H 3900 7200 50  0001 C CNN
F 1 "GND" H 3905 7277 50  0000 C CNN
F 2 "" H 3900 7450 50  0001 C CNN
F 3 "" H 3900 7450 50  0001 C CNN
	1    3900 7450
	1    0    0    -1  
$EndComp
Text GLabel 3300 7150 0    50   Input ~ 0
PI_REBOOT
Wire Wire Line
	3750 6850 3900 6850
Wire Wire Line
	3900 6950 3900 6850
Connection ~ 3900 6850
Wire Wire Line
	3900 6850 4000 6850
Wire Wire Line
	3900 7350 3900 7450
$Comp
L Connector_Generic:Conn_01x04 J1
U 1 1 67AB91F7
P 1400 1700
F 0 "J1" V 1500 1350 50  0000 R CNN
F 1 "DBG_SERIAL" V 1500 1400 50  0000 L CNN
F 2 "0_my_footprints:myJSTx04" H 1400 1700 50  0001 C CNN
F 3 "~" H 1400 1700 50  0001 C CNN
	1    1400 1700
	0    -1   -1   0   
$EndComp
Text Notes 1200 1500 0    50   ~ 0
FTDI USB Serial
Text GLabel 2750 3350 1    50   Input ~ 0
ROT_INT
Text GLabel 2650 3350 1    50   Input ~ 0
T41_SDA
Text GLabel 2550 3350 1    50   Input ~ 0
T41_SCL
Text GLabel 2050 3350 1    50   Input ~ 0
T41_3V3
Text GLabel 1600 1900 3    50   Input ~ 0
T41_3V3
Text GLabel 4350 1900 3    50   Input ~ 0
T41_3V3
Text GLabel 3550 3350 1    50   Input ~ 0
SENS_PI_RUN
Text GLabel 3650 3350 1    50   Input ~ 0
PI_REBOOT
Text GLabel 3750 3350 1    50   Input ~ 0
RPI_READY
Text GLabel 1600 7300 3    50   Input ~ 0
T41_SCL
Text GLabel 1700 7300 3    50   Input ~ 0
T41_SDA
$Comp
L Device:R R2
U 1 1 67964E23
P 1700 7150
F 0 "R2" H 1750 7150 50  0000 L CNN
F 1 "1K" V 1700 7150 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 1630 7150 50  0001 C CNN
F 3 "~" H 1700 7150 50  0001 C CNN
	1    1700 7150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 67965E12
P 1600 7150
F 0 "R1" H 1450 7150 50  0000 L CNN
F 1 "1K" V 1600 7150 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 1530 7150 50  0001 C CNN
F 3 "~" H 1600 7150 50  0001 C CNN
	1    1600 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 7000 1700 6900
Wire Wire Line
	1600 7000 1600 6900
$Comp
L Device:R R3
U 1 1 6796F63B
P 3450 7150
F 0 "R3" V 3550 7100 50  0000 L CNN
F 1 "1K" V 3450 7150 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 3380 7150 50  0001 C CNN
F 3 "~" H 3450 7150 50  0001 C CNN
	1    3450 7150
	0    -1   -1   0   
$EndComp
Text GLabel 3350 1900 3    50   Input ~ 0
BTN_CLK
Text GLabel 1500 1900 3    50   Input ~ 0
T41_TX1
Text GLabel 1400 1900 3    50   Input ~ 0
T41_RX1
Text GLabel 2050 5400 3    50   Input ~ 0
T41_TX1
Text GLabel 1950 5400 3    50   Input ~ 0
T41_RX1
Text GLabel 3050 1900 3    50   Input ~ 0
LED_DIN
Text GLabel 3150 1900 3    50   Input ~ 0
BTN_DIN
Text GLabel 3050 3350 1    50   Input ~ 0
BTN_CLK
Text GLabel 2450 3350 1    50   Input ~ 0
LED_DIN
Text GLabel 2950 3350 1    50   Input ~ 0
BTN_DIN
Text GLabel 2850 3350 1    50   Input ~ 0
BTN_SENSE
Text GLabel 3450 1900 3    50   Input ~ 0
T41_3V3
Text GLabel 1850 3350 1    50   Input ~ 0
T41_5V
Text GLabel 2950 1900 3    50   Input ~ 0
BTN_SENSE
Text Notes 1200 6450 0    50   ~ 0
Rotary mcp23017 needs\n1K pullups on SDA & SCL
Text GLabel 4850 1900 3    50   Input ~ 0
T41_5V
Wire Wire Line
	1600 6900 1650 6900
Text GLabel 1650 6850 1    50   Input ~ 0
T41_3V3
Wire Wire Line
	1650 6850 1650 6900
Connection ~ 1650 6900
Wire Wire Line
	1650 6900 1700 6900
$Comp
L power:+5V #PWR024
U 1 1 679D6893
P 10150 4900
F 0 "#PWR024" H 10150 4750 50  0001 C CNN
F 1 "+5V" V 10150 5000 50  0000 L CNN
F 2 "" H 10150 4900 50  0001 C CNN
F 3 "" H 10150 4900 50  0001 C CNN
	1    10150 4900
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR025
U 1 1 679D6F56
P 10250 4900
F 0 "#PWR025" H 10250 4750 50  0001 C CNN
F 1 "+5V" V 10250 5000 50  0000 L CNN
F 2 "" H 10250 4900 50  0001 C CNN
F 3 "" H 10250 4900 50  0001 C CNN
	1    10250 4900
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J10
U 1 1 679E8689
P 9800 1700
F 0 "J10" V 9900 1550 50  0000 R CNN
F 1 "rPi_5V" V 9900 1850 50  0000 R CNN
F 2 "0_my_footprints:myJSTx02" H 9800 1700 50  0001 C CNN
F 3 "~" H 9800 1700 50  0001 C CNN
	1    9800 1700
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR022
U 1 1 679EBF82
P 9900 1900
F 0 "#PWR022" H 9900 1750 50  0001 C CNN
F 1 "+5V" V 9900 2000 50  0000 L CNN
F 2 "" H 9900 1900 50  0001 C CNN
F 3 "" H 9900 1900 50  0001 C CNN
	1    9900 1900
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR020
U 1 1 679ECFE3
P 9800 1900
F 0 "#PWR020" H 9800 1650 50  0001 C CNN
F 1 "GND" V 9800 1600 50  0000 L CNN
F 2 "" H 9800 1900 50  0001 C CNN
F 3 "" H 9800 1900 50  0001 C CNN
	1    9800 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 67B33AE6
P 5800 7000
F 0 "#PWR011" H 5800 6750 50  0001 C CNN
F 1 "GND" V 5800 6700 50  0000 L CNN
F 2 "" H 5800 7000 50  0001 C CNN
F 3 "" H 5800 7000 50  0001 C CNN
	1    5800 7000
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J5
U 1 1 67B2FCBF
P 5800 7200
F 0 "J5" V 5900 6800 50  0000 L CNN
F 1 "EXT_LEDS" V 5900 7100 50  0000 L CNN
F 2 "0_my_footprints:myJSTx08" H 5800 7200 50  0001 C CNN
F 3 "~" H 5800 7200 50  0001 C CNN
	1    5800 7200
	0    1    1    0   
$EndComp
Text GLabel 5900 7000 1    50   Input ~ 0
LED_T3_BUSY
Text GLabel 5400 7000 1    50   Input ~ 0
LED_AUDIO_BUSY
Text GLabel 5600 7000 1    50   Input ~ 0
LED_RPI_I2S_RX
Text GLabel 5500 7000 1    50   Input ~ 0
LED_RPI_I2S_TX
Text GLabel 6100 7000 1    50   Input ~ 0
LED_RPI_READY
Text GLabel 6000 7000 1    50   Input ~ 0
LED_RPI_RUN
Text GLabel 9450 4900 3    50   Input ~ 0
LED_RPI_BUSY
Text GLabel 5700 7000 1    50   Input ~ 0
LED_RPI_BUSY
$Comp
L Connector_Generic:Conn_01x02 J6
U 1 1 679D8C31
P 6850 4250
F 0 "J6" H 6850 3950 50  0000 R CNN
F 1 "I2S_TXB" H 6950 4050 50  0000 R CNN
F 2 "0_my_footprints:myJSTx02" H 6850 4250 50  0001 C CNN
F 3 "~" H 6850 4250 50  0001 C CNN
	1    6850 4250
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 679E1C5A
P 7050 4150
F 0 "#PWR0101" H 7050 3900 50  0001 C CNN
F 1 "GND" V 7050 3850 50  0000 L CNN
F 2 "" H 7050 4150 50  0001 C CNN
F 3 "" H 7050 4150 50  0001 C CNN
	1    7050 4150
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J7
U 1 1 679E6862
P 8100 4150
F 0 "J7" H 8100 4350 50  0000 R CNN
F 1 "RPI_RUN" H 8200 4250 50  0000 R CNN
F 2 "0_my_footprints:myJSTx02" H 8100 4150 50  0001 C CNN
F 3 "~" H 8100 4150 50  0001 C CNN
	1    8100 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 679EB87B
P 7900 4150
F 0 "#PWR0102" H 7900 3900 50  0001 C CNN
F 1 "GND" V 7900 3850 50  0000 L CNN
F 2 "" H 7900 4150 50  0001 C CNN
F 3 "" H 7900 4150 50  0001 C CNN
	1    7900 4150
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J11
U 1 1 67A01DD0
P 2300 1700
F 0 "J11" V 2400 1350 50  0000 L CNN
F 1 "PEDALS" V 2400 1550 50  0000 L CNN
F 2 "0_my_footprints:myJSTx06" H 2300 1700 50  0001 C CNN
F 3 "~" H 2300 1700 50  0001 C CNN
	1    2300 1700
	0    -1   -1   0   
$EndComp
Text GLabel 2100 1900 3    50   Input ~ 0
T41_3V3
$Comp
L power:GND #PWR026
U 1 1 67A045B5
P 2600 1900
F 0 "#PWR026" H 2600 1650 50  0001 C CNN
F 1 "GND" V 2600 1600 50  0000 L CNN
F 2 "" H 2600 1900 50  0001 C CNN
F 3 "" H 2600 1900 50  0001 C CNN
	1    2600 1900
	1    0    0    -1  
$EndComp
Text GLabel 2200 1900 3    50   Input ~ 0
PEDAL1
Text GLabel 2300 1900 3    50   Input ~ 0
PEDAL2
Text GLabel 2400 1900 3    50   Input ~ 0
PEDAL3
Text GLabel 2500 1900 3    50   Input ~ 0
PEDAL4
Text GLabel 2150 3350 1    50   Input ~ 0
PEDAL1
Text GLabel 2250 3350 1    50   Input ~ 0
PEDAL2
Text GLabel 2350 3350 1    50   Input ~ 0
PEDAL3
Text GLabel 3350 3350 1    50   Input ~ 0
PEDAL4
$EndSCHEMATC

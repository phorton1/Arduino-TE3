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
P 2950 4250
F 0 "U?" H 2850 4200 50  0000 L CNN
F 1 "myTeensy4.1" H 2850 4100 50  0000 L CNN
F 2 "" H 2650 3350 50  0001 C CNN
F 3 "" H 2650 3350 50  0001 C CNN
	1    2950 4250
	1    0    0    -1  
$EndComp
$Comp
L 0_my_symbols:rpi_connector J?
U 1 1 67943AF8
P 9300 4200
F 0 "J?" H 8950 4200 50  0000 L CNN
F 1 "rpi_connector" H 9100 4200 50  0000 L CNN
F 2 "" H 9200 4100 50  0001 C CNN
F 3 "" H 9200 4100 50  0001 C CNN
	1    9300 4200
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J?
U 1 1 679456F8
P 4500 1700
F 0 "J?" V 4600 1300 50  0000 L CNN
F 1 "TE_DISPLAY" V 4600 1650 50  0000 L CNN
F 2 "" H 4500 1700 50  0001 C CNN
F 3 "~" H 4500 1700 50  0001 C CNN
	1    4500 1700
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J?
U 1 1 67946D3E
P 3400 1700
F 0 "J?" V 3500 1450 50  0000 L CNN
F 1 "ROTARIES" V 3500 1600 50  0000 L CNN
F 2 "" H 3400 1700 50  0001 C CNN
F 3 "~" H 3400 1700 50  0001 C CNN
	1    3400 1700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6794C62E
P 3200 1900
F 0 "#PWR?" H 3200 1650 50  0001 C CNN
F 1 "GND" V 3200 1600 50  0000 L CNN
F 2 "" H 3200 1900 50  0001 C CNN
F 3 "" H 3200 1900 50  0001 C CNN
	1    3200 1900
	1    0    0    -1  
$EndComp
Text GLabel 3300 1900 3    50   Input ~ 0
T41_SCL
Text GLabel 3400 1900 3    50   Input ~ 0
T41_SDA
Text GLabel 3500 1900 3    50   Input ~ 0
ROT_INT
$Comp
L Connector_Generic:Conn_01x06 J?
U 1 1 67952F34
P 2400 1700
F 0 "J?" V 2500 1350 50  0000 L CNN
F 1 "ROW_BOARDS" V 2500 1450 50  0000 L CNN
F 2 "" H 2400 1700 50  0001 C CNN
F 3 "~" H 2400 1700 50  0001 C CNN
	1    2400 1700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67955DCC
P 2500 1900
F 0 "#PWR?" H 2500 1650 50  0001 C CNN
F 1 "GND" V 2500 1600 50  0000 L CNN
F 2 "" H 2500 1900 50  0001 C CNN
F 3 "" H 2500 1900 50  0001 C CNN
	1    2500 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6797D5D1
P 4900 1900
F 0 "#PWR?" H 4900 1650 50  0001 C CNN
F 1 "GND" V 4900 1600 50  0000 L CNN
F 2 "" H 4900 1900 50  0001 C CNN
F 3 "" H 4900 1900 50  0001 C CNN
	1    4900 1900
	1    0    0    -1  
$EndComp
Text GLabel 4300 1900 3    50   Input ~ 0
T41_T_CS
Text GLabel 4400 1900 3    50   Input ~ 0
T41_SCLK
Text GLabel 4500 1900 3    50   Input ~ 0
T41_MISO
Text GLabel 4600 1900 3    50   Input ~ 0
T41_LCD_DC
Text GLabel 4700 1900 3    50   Input ~ 0
T41_LCD_CS
Text GLabel 4800 1900 3    50   Input ~ 0
T41_MOSI
$Comp
L Connector_Generic:Conn_01x08 J?
U 1 1 67986515
P 9200 1700
F 0 "J?" V 9300 1300 50  0000 L CNN
F 1 "RPI_DISPLAY" V 9300 1600 50  0000 L CNN
F 2 "" H 9200 1700 50  0001 C CNN
F 3 "~" H 9200 1700 50  0001 C CNN
	1    9200 1700
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 6798651B
P 8900 1900
F 0 "#PWR?" H 8900 1750 50  0001 C CNN
F 1 "+5V" V 8900 2000 50  0000 L CNN
F 2 "" H 8900 1900 50  0001 C CNN
F 3 "" H 8900 1900 50  0001 C CNN
	1    8900 1900
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67986521
P 9600 1900
F 0 "#PWR?" H 9600 1650 50  0001 C CNN
F 1 "GND" V 9600 1600 50  0000 L CNN
F 2 "" H 9600 1900 50  0001 C CNN
F 3 "" H 9600 1900 50  0001 C CNN
	1    9600 1900
	1    0    0    -1  
$EndComp
Text GLabel 9000 1900 3    50   Input ~ 0
RPI_T_CS
Text GLabel 9100 1900 3    50   Input ~ 0
RPI_SCLK
Text GLabel 9200 1900 3    50   Input ~ 0
RPI_MISO
Text GLabel 9300 1900 3    50   Input ~ 0
RPI_LCD_DC
Text GLabel 9400 1900 3    50   Input ~ 0
RPI_LCD_CS
Text GLabel 9500 1900 3    50   Input ~ 0
RPI_MOSI
Text GLabel 5600 7000 1    50   Input ~ 0
LED_RPI_RUN
Text GLabel 5700 7000 1    50   Input ~ 0
LED_RPI_READY
Text GLabel 5900 7000 1    50   Input ~ 0
LED_RPI_I2S_TX
Text GLabel 6000 7000 1    50   Input ~ 0
LED_RPI_I2S_RX
Text GLabel 8750 4900 3    50   Input ~ 0
LED_RPI_I2S_RX
Text GLabel 8550 4900 3    50   Input ~ 0
LED_RPI_I2S_TX
Text GLabel 9750 4900 3    50   Input ~ 0
I2S_BCLK
Text GLabel 8550 3550 1    50   Input ~ 0
I2S_FCLK
$Comp
L Connector_Generic:Conn_01x01 J?
U 1 1 679C02F5
P 6750 4250
F 0 "J?" H 6650 4000 50  0000 C CNN
F 1 "I2S_TXB" H 6668 4116 50  0000 C CNN
F 2 "" H 6750 4250 50  0001 C CNN
F 3 "~" H 6750 4250 50  0001 C CNN
	1    6750 4250
	-1   0    0    1   
$EndComp
Text GLabel 6950 4250 2    50   Input ~ 0
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
Text GLabel 5800 7000 1    50   Input ~ 0
LED_AUDIO_ALIVE
Text GLabel 5700 4950 3    50   Input ~ 0
LED_AUDIO_ALIVE
$Comp
L Connector_Generic:Conn_01x01 J?
U 1 1 679CE3ED
P 8100 4250
F 0 "J?" H 8050 4500 50  0000 C CNN
F 1 "RPI_RUN" H 8050 4400 50  0000 C CNN
F 2 "" H 8100 4250 50  0001 C CNN
F 3 "~" H 8100 4250 50  0001 C CNN
	1    8100 4250
	1    0    0    -1  
$EndComp
Text GLabel 7900 4250 0    50   Input ~ 0
RPI_RUN
Text GLabel 9250 4900 3    50   Input ~ 0
RPI_READY
$Comp
L 0_my_teensy:teensyAudioRevD U?
U 1 1 67941570
P 5750 4200
F 0 "U?" H 5500 4200 60  0000 L CNN
F 1 "teensyAudioRevD" H 5100 4000 60  0000 L CNN
F 2 "" V 6700 4150 60  0000 C CNN
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
Text Notes 4300 1550 0    50   ~ 0
ILI9488_T3
Text GLabel 3350 5400 3    50   Input ~ 0
T41_SCLK?
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
Text GLabel 5500 7000 1    50   Input ~ 0
LED_T3_ALIVE
Text GLabel 2350 5400 3    50   Input ~ 0
LED_T3_ALIVE
Text GLabel 9150 4900 3    50   Input ~ 0
RPI_LCD_CS
Text GLabel 9050 4900 3    50   Input ~ 0
RPI_T_CS
Text GLabel 9950 3550 1    50   Input ~ 0
RPI_LCD_DC
$Comp
L power:GND #PWR?
U 1 1 67A37846
P 10050 4900
F 0 "#PWR?" H 10050 4650 50  0001 C CNN
F 1 "GND" V 10050 4600 50  0000 L CNN
F 2 "" H 10050 4900 50  0001 C CNN
F 3 "" H 10050 4900 50  0001 C CNN
	1    10050 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A37CAF
P 9650 4900
F 0 "#PWR?" H 9650 4650 50  0001 C CNN
F 1 "GND" V 9650 4600 50  0000 L CNN
F 2 "" H 9650 4900 50  0001 C CNN
F 3 "" H 9650 4900 50  0001 C CNN
	1    9650 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A37F8C
P 9350 4900
F 0 "#PWR?" H 9350 4650 50  0001 C CNN
F 1 "GND" V 9350 4600 50  0000 L CNN
F 2 "" H 9350 4900 50  0001 C CNN
F 3 "" H 9350 4900 50  0001 C CNN
	1    9350 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A38141
P 8850 4900
F 0 "#PWR?" H 8850 4650 50  0001 C CNN
F 1 "GND" V 8850 4600 50  0000 L CNN
F 2 "" H 8850 4900 50  0001 C CNN
F 3 "" H 8850 4900 50  0001 C CNN
	1    8850 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A38257
P 8650 4900
F 0 "#PWR?" H 8650 4650 50  0001 C CNN
F 1 "GND" V 8650 4600 50  0000 L CNN
F 2 "" H 8650 4900 50  0001 C CNN
F 3 "" H 8650 4900 50  0001 C CNN
	1    8650 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A38A35
P 8350 3550
F 0 "#PWR?" H 8350 3300 50  0001 C CNN
F 1 "GND" V 8350 3250 50  0000 L CNN
F 2 "" H 8350 3550 50  0001 C CNN
F 3 "" H 8350 3550 50  0001 C CNN
	1    8350 3550
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A38E9E
P 9050 3550
F 0 "#PWR?" H 9050 3300 50  0001 C CNN
F 1 "GND" V 9050 3250 50  0000 L CNN
F 2 "" H 9050 3550 50  0001 C CNN
F 3 "" H 9050 3550 50  0001 C CNN
	1    9050 3550
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A392BE
P 9850 3550
F 0 "#PWR?" H 9850 3300 50  0001 C CNN
F 1 "GND" V 9850 3250 50  0000 L CNN
F 2 "" H 9850 3550 50  0001 C CNN
F 3 "" H 9850 3550 50  0001 C CNN
	1    9850 3550
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A3A486
P 5300 3500
F 0 "#PWR?" H 5300 3250 50  0001 C CNN
F 1 "GND" V 5300 3200 50  0000 L CNN
F 2 "" H 5300 3500 50  0001 C CNN
F 3 "" H 5300 3500 50  0001 C CNN
	1    5300 3500
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A3AA10
P 5200 4950
F 0 "#PWR?" H 5200 4700 50  0001 C CNN
F 1 "GND" V 5200 4650 50  0000 L CNN
F 2 "" H 5200 4950 50  0001 C CNN
F 3 "" H 5200 4950 50  0001 C CNN
	1    5200 4950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A3B5C4
P 1850 5400
F 0 "#PWR?" H 1850 5150 50  0001 C CNN
F 1 "GND" V 1850 5100 50  0000 L CNN
F 2 "" H 1850 5400 50  0001 C CNN
F 3 "" H 1850 5400 50  0001 C CNN
	1    1850 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A3C2A4
P 1950 3350
F 0 "#PWR?" H 1950 3100 50  0001 C CNN
F 1 "GND" V 1950 3050 50  0000 L CNN
F 2 "" H 1950 3350 50  0001 C CNN
F 3 "" H 1950 3350 50  0001 C CNN
	1    1950 3350
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67A3C67C
P 3250 3350
F 0 "#PWR?" H 3250 3100 50  0001 C CNN
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
T41_RX7
Text GLabel 5300 4950 3    50   Input ~ 0
T41_TX7
Text GLabel 4050 3350 1    50   Input ~ 0
T41_RX8
Text GLabel 3950 3350 1    50   Input ~ 0
T41_TX8
Text GLabel 9950 4900 3    50   Input ~ 0
T41_RX8
Text GLabel 9850 4900 3    50   Input ~ 0
T41_TX8
$Comp
L power:GND #PWR?
U 1 1 67A5DC81
P 1300 1900
F 0 "#PWR?" H 1300 1650 50  0001 C CNN
F 1 "GND" V 1300 1600 50  0000 L CNN
F 2 "" H 1300 1900 50  0001 C CNN
F 3 "" H 1300 1900 50  0001 C CNN
	1    1300 1900
	1    0    0    -1  
$EndComp
Text Notes 9100 1550 0    50   ~ 0
ILI9488
$Comp
L Device:R R?
U 1 1 64CCBE5B
P 3600 6850
F 0 "R?" V 3700 6800 50  0000 L CNN
F 1 "220" V 3600 6850 50  0000 C CNN
F 2 "" V 3530 6850 50  0001 C CNN
F 3 "~" H 3600 6850 50  0001 C CNN
	1    3600 6850
	0    -1   -1   0   
$EndComp
Text GLabel 4000 6850 2    50   Input ~ 0
RPI_RUN
Text GLabel 3450 6850 0    50   Input ~ 0
SENS_PI_RUN
$Comp
L Transistor_BJT:BC547 Q?
U 1 1 64CF1712
P 3800 7150
F 0 "Q?" H 3991 7196 50  0000 L CNN
F 1 "BC547" H 3991 7105 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4000 7075 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 3800 7150 50  0001 L CNN
	1    3800 7150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 64CF464E
P 3900 7450
F 0 "#PWR?" H 3900 7200 50  0001 C CNN
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
L Connector_Generic:Conn_01x04 J?
U 1 1 67AB91F7
P 1400 1700
F 0 "J?" V 1500 1350 50  0000 R CNN
F 1 "DBG_SERIAL" V 1500 1400 50  0000 L CNN
F 2 "" H 1400 1700 50  0001 C CNN
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
Text GLabel 3600 1900 3    50   Input ~ 0
T41_3V3
$Comp
L Connector_Generic:Conn_01x08 J?
U 1 1 67B2FCBF
P 5700 7200
F 0 "J?" V 5800 6800 50  0000 L CNN
F 1 "EXT_LEDS" V 5800 7100 50  0000 L CNN
F 2 "" H 5700 7200 50  0001 C CNN
F 3 "~" H 5700 7200 50  0001 C CNN
	1    5700 7200
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 67B33AE6
P 5400 7000
F 0 "#PWR?" H 5400 6750 50  0001 C CNN
F 1 "GND" V 5400 6700 50  0000 L CNN
F 2 "" H 5400 7000 50  0001 C CNN
F 3 "" H 5400 7000 50  0001 C CNN
	1    5400 7000
	-1   0    0    1   
$EndComp
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
L Device:R R?
U 1 1 67964E23
P 1700 7150
F 0 "R?" H 1750 7150 50  0000 L CNN
F 1 "1K" V 1700 7150 50  0000 C CNN
F 2 "" V 1630 7150 50  0001 C CNN
F 3 "~" H 1700 7150 50  0001 C CNN
	1    1700 7150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 67965E12
P 1600 7150
F 0 "R?" H 1450 7150 50  0000 L CNN
F 1 "1K" V 1600 7150 50  0000 C CNN
F 2 "" V 1530 7150 50  0001 C CNN
F 3 "~" H 1600 7150 50  0001 C CNN
	1    1600 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 7000 1700 6900
Wire Wire Line
	1600 7000 1600 6900
$Comp
L Device:R R?
U 1 1 6796F63B
P 3450 7150
F 0 "R?" V 3550 7100 50  0000 L CNN
F 1 "1K" V 3450 7150 50  0000 C CNN
F 2 "" V 3380 7150 50  0001 C CNN
F 3 "~" H 3450 7150 50  0001 C CNN
	1    3450 7150
	0    -1   -1   0   
$EndComp
Text GLabel 2600 1900 3    50   Input ~ 0
BTN_CLK
Text GLabel 1400 1900 3    50   Input ~ 0
T41_TX1
Text GLabel 1500 1900 3    50   Input ~ 0
T41_RX1
Text GLabel 2050 5400 3    50   Input ~ 0
T41_TX1
Text GLabel 1950 5400 3    50   Input ~ 0
T41_RX1
Text GLabel 2300 1900 3    50   Input ~ 0
LED_DIN
Text GLabel 2400 1900 3    50   Input ~ 0
BTN_DIN
Text GLabel 3050 3350 1    50   Input ~ 0
BTN_CLK
Text GLabel 2450 3350 1    50   Input ~ 0
LED_DIN
Text GLabel 2950 3350 1    50   Input ~ 0
BTN_DIN
Text GLabel 2850 3350 1    50   Input ~ 0
BTN_SENSE
Text GLabel 2700 1900 3    50   Input ~ 0
T41_3V3
Text GLabel 1850 3350 1    50   Input ~ 0
T41_5V
Text GLabel 2200 1900 3    50   Input ~ 0
BTN_SENSE
Text Notes 1200 6450 0    50   ~ 0
Rotary mcp23017 needs\n1K pullups on SDA & SCL
Text GLabel 4200 1900 3    50   Input ~ 0
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
$EndSCHEMATC

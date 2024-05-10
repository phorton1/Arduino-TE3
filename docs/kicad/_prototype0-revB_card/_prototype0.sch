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
L 0_my_teensy:teensyAudioRevB U3
U 1 1 663C0C59
P 16150 7750
F 0 "U3" H 17028 7778 60  0001 L CNN
F 1 "teensyAudioRevB" H 16600 7700 60  0000 R CNN
F 2 "0_my_teensy:audioShieldRevB" V 17100 7700 60  0001 C CNN
F 3 "" V 17100 7700 60  0000 C CNN
	1    16150 7750
	-1   0    0    1   
$EndComp
Text GLabel 15500 6700 1    50   Input ~ 0
I2S_MCLK
Text GLabel 15700 7000 1    50   Input ~ 0
I2S_BCLK
Text GLabel 16400 8450 3    50   Input ~ 0
I2S_FCLK
Text GLabel 16000 8450 3    50   Input ~ 0
T40_SCL
Text GLabel 15900 8450 3    50   Input ~ 0
T40_SCA
Text GLabel 15400 8450 3    50   Input ~ 0
I2S_RXA
Text GLabel 16300 8450 3    50   Input ~ 0
I2S_TXA
$Comp
L Device:R R6
U 1 1 6652E99E
P 15500 6850
F 0 "R6" H 15450 7500 50  0001 L CNN
F 1 "100" V 15500 6850 50  0000 C CNN
F 2 "0_my_footprints2:resistor" V 15430 6850 50  0001 C CNN
F 3 "~" H 15500 6850 50  0001 C CNN
	1    15500 6850
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J2
U 1 1 666229FF
P 12850 3550
F 0 "J2" V 12850 4100 50  0001 R CNN
F 1 "RPI_ILI9488" V 13000 3700 50  0000 R CNN
F 2 "0_my_footprints2:JST8" H 12850 3550 50  0001 C CNN
F 3 "~" H 12850 3550 50  0001 C CNN
	1    12850 3550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR03
U 1 1 666282FE
P 13250 3750
F 0 "#PWR03" H 13250 3500 50  0001 C CNN
F 1 "GND" V 13250 3550 50  0000 C CNN
F 2 "" H 13250 3750 50  0001 C CNN
F 3 "" H 13250 3750 50  0001 C CNN
	1    13250 3750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J1
U 1 1 6663CA44
P 5550 3550
F 0 "J1" V 5550 4100 50  0001 R CNN
F 1 "T3_ILI9488" V 5700 3700 50  0000 R CNN
F 2 "0_my_footprints2:JST8" H 5550 3550 50  0001 C CNN
F 3 "~" H 5550 3550 50  0001 C CNN
	1    5550 3550
	0    -1   -1   0   
$EndComp
Text GLabel 5950 3750 3    50   Input ~ 0
T41_5V
$Comp
L power:GND #PWR01
U 1 1 6663CA4B
P 5750 3750
F 0 "#PWR01" H 5750 3500 50  0001 C CNN
F 1 "GND" V 5750 3550 50  0000 C CNN
F 2 "" H 5750 3750 50  0001 C CNN
F 3 "" H 5750 3750 50  0001 C CNN
	1    5750 3750
	1    0    0    -1  
$EndComp
Text GLabel 5450 3750 3    50   Input ~ 0
T41_MOSI
Text GLabel 5550 3750 3    50   Input ~ 0
T41_MISO
Text GLabel 5850 3750 3    50   Input ~ 0
T41_SCLK
Text GLabel 5250 3750 3    50   Input ~ 0
T41_CD
Text GLabel 5350 3750 3    50   Input ~ 0
T41_LED_CS
Text GLabel 5650 3750 3    50   Input ~ 0
T41_TOUCH_CS
Text GLabel 12750 3750 3    50   Input ~ 0
RPI_TOUCH_CS
Text GLabel 12650 3750 3    50   Input ~ 0
RPI_LED_CS
Text GLabel 12850 3750 3    50   Input ~ 0
RPI_CD
Text GLabel 13150 3750 3    50   Input ~ 0
RPI_SCLK
Text GLabel 13050 3750 3    50   Input ~ 0
RPI_MISO
Text GLabel 12950 3750 3    50   Input ~ 0
RPI_MOSI
Text GLabel 12550 3750 3    50   Input ~ 0
RPI_5V
$Comp
L power:GND #PWR019
U 1 1 66610187
P 13300 6750
F 0 "#PWR019" H 13300 6500 50  0001 C CNN
F 1 "GND" V 13300 6550 50  0000 C CNN
F 2 "" H 13300 6750 50  0001 C CNN
F 3 "" H 13300 6750 50  0001 C CNN
	1    13300 6750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR020
U 1 1 6660F832
P 13700 6750
F 0 "#PWR020" H 13700 6500 50  0001 C CNN
F 1 "GND" V 13700 6550 50  0000 C CNN
F 2 "" H 13700 6750 50  0001 C CNN
F 3 "" H 13700 6750 50  0001 C CNN
	1    13700 6750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 6660E5AB
P 13500 5550
F 0 "#PWR013" H 13500 5300 50  0001 C CNN
F 1 "GND" V 13500 5350 50  0000 C CNN
F 2 "" H 13500 5550 50  0001 C CNN
F 3 "" H 13500 5550 50  0001 C CNN
	1    13500 5550
	-1   0    0    1   
$EndComp
Text GLabel 13900 6750 3    50   Input ~ 0
RPI_5V
Text GLabel 13600 5550 1    50   Input ~ 0
RPI_CD
Text GLabel 13600 6750 3    50   Input ~ 0
RPI_TX
Text GLabel 13500 6750 3    50   Input ~ 0
RPI_RX
Text GLabel 13400 6750 3    50   Input ~ 10
I2S_BCLK
$Comp
L power:GND #PWR023
U 1 1 6634081F
P 16700 7000
F 0 "#PWR023" H 16700 6750 50  0001 C CNN
F 1 "GND" V 16700 6800 50  0000 C CNN
F 2 "" H 16700 7000 50  0001 C CNN
F 3 "" H 16700 7000 50  0001 C CNN
	1    16700 7000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR024
U 1 1 66341ED9
P 16600 8450
F 0 "#PWR024" H 16600 8200 50  0001 C CNN
F 1 "GND" V 16600 8250 50  0000 C CNN
F 2 "" H 16600 8450 50  0001 C CNN
F 3 "" H 16600 8450 50  0001 C CNN
	1    16600 8450
	1    0    0    -1  
$EndComp
Text GLabel 16500 8450 3    50   Input ~ 0
T40_3.3V
Text GLabel 15900 3150 1    50   Input ~ 10
I2S_BCLK
Text GLabel 15700 3150 1    50   Input ~ 0
I2S_MCLK
Text GLabel 16000 3150 1    50   Input ~ 10
I2S_FCLK
Text GLabel 16200 5250 3    50   Input ~ 0
I2S_TXA
Text GLabel 15600 3150 1    50   Input ~ 0
T40_3.3V
Text GLabel 16100 3150 1    50   Input ~ 0
T40_SCL
Text GLabel 16200 3150 1    50   Input ~ 0
T40_SCA
Text GLabel 16300 5250 3    50   Input ~ 0
I2S_RXA
$Comp
L power:GND #PWR04
U 1 1 663F8A41
P 15500 3150
F 0 "#PWR04" H 15500 2900 50  0001 C CNN
F 1 "GND" V 15500 2950 50  0000 C CNN
F 2 "" H 15500 3150 50  0001 C CNN
F 3 "" H 15500 3150 50  0001 C CNN
	1    15500 3150
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR014
U 1 1 663F90C2
P 15400 5250
F 0 "#PWR014" H 15400 5000 50  0001 C CNN
F 1 "GND" V 15400 5050 50  0000 C CNN
F 2 "" H 15400 5250 50  0001 C CNN
F 3 "" H 15400 5250 50  0001 C CNN
	1    15400 5250
	1    0    0    -1  
$EndComp
Text GLabel 16100 5250 3    50   Input ~ 10
I2S_TXB
Text GLabel 5850 5550 1    50   Input ~ 0
T41_SCLK
Text GLabel 4750 5550 1    50   Input ~ 0
T41_3.3V
Text GLabel 4550 5550 1    50   Input ~ 0
T41_5V
Text Notes 4750 6750 0    50   ~ 0
T3_TOUCH_CS chosen as "can use any digital pin" from ILI9341 page
Text GLabel 5550 7600 3    50   Input ~ 0
T41_CD
Text Notes 4750 6650 0    50   ~ 0
LED_OUT chosen using teensy w2812Serial alternate pin options
Text GLabel 6350 7600 3    50   Input ~ 10
T41_TOUCH_CS
Text GLabel 5650 7600 3    50   Input ~ 0
T41_LED_CS
$Comp
L power:GND #PWR09
U 1 1 66399473
P 4650 5550
F 0 "#PWR09" H 4650 5300 50  0001 C CNN
F 1 "GND" V 4650 5350 50  0000 C CNN
F 2 "" H 4650 5550 50  0001 C CNN
F 3 "" H 4650 5550 50  0001 C CNN
	1    4650 5550
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR010
U 1 1 66399467
P 5950 5550
F 0 "#PWR010" H 5950 5300 50  0001 C CNN
F 1 "GND" V 5950 5350 50  0000 C CNN
F 2 "" H 5950 5550 50  0001 C CNN
F 3 "" H 5950 5550 50  0001 C CNN
	1    5950 5550
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR021
U 1 1 6637C7F0
P 4550 7600
F 0 "#PWR021" H 4550 7350 50  0001 C CNN
F 1 "GND" V 4550 7400 50  0000 C CNN
F 2 "" H 4550 7600 50  0001 C CNN
F 3 "" H 4550 7600 50  0001 C CNN
	1    4550 7600
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR022
U 1 1 6637C7EA
P 5950 7600
F 0 "#PWR022" H 5950 7450 50  0001 C CNN
F 1 "+3V3" V 5950 7800 50  0000 C CNN
F 2 "" H 5950 7600 50  0001 C CNN
F 3 "" H 5950 7600 50  0001 C CNN
	1    5950 7600
	-1   0    0    1   
$EndComp
Text GLabel 6550 7600 3    50   Input ~ 0
LED_DOUT
Text GLabel 5750 7600 3    50   Input ~ 0
T41_MOSI
Text GLabel 5850 7600 3    50   Input ~ 0
T41_MISO
$Comp
L Device:R R5
U 1 1 64CCBE5B
P 9350 7000
F 0 "R5" H 9420 7046 50  0000 L CNN
F 1 "220" V 9350 7000 50  0000 C CNN
F 2 "0_my_footprints2:resistor" V 9280 7000 50  0001 C CNN
F 3 "~" H 9350 7000 50  0001 C CNN
	1    9350 7000
	0    -1   1    0   
$EndComp
Text GLabel 9750 7000 2    50   Input ~ 10
RPI_RUN
Text GLabel 9050 7000 0    50   Input ~ 0
SENS_PI_RUN
$Comp
L Transistor_BJT:BC547 Q1
U 1 1 64CF1712
P 9550 6700
F 0 "Q1" H 9741 6746 50  0000 L CNN
F 1 "BC547" H 9741 6655 50  0000 L CNN
F 2 "0_my_footprints2:transistor" H 9750 6625 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 9550 6700 50  0001 L CNN
	1    9550 6700
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR015
U 1 1 64CF464E
P 9650 6400
F 0 "#PWR015" H 9650 6150 50  0001 C CNN
F 1 "GND" H 9655 6227 50  0000 C CNN
F 2 "" H 9650 6400 50  0001 C CNN
F 3 "" H 9650 6400 50  0001 C CNN
	1    9650 6400
	1    0    0    1   
$EndComp
Text GLabel 9050 6700 0    50   Input ~ 0
PI_REBOOT
Wire Wire Line
	9500 7000 9650 7000
Wire Wire Line
	9650 6900 9650 7000
Connection ~ 9650 7000
Wire Wire Line
	9650 7000 9750 7000
Wire Wire Line
	9650 6500 9650 6400
$Comp
L Device:LED D2
U 1 1 662B77AA
P 9800 4050
F 0 "D2" H 9793 3795 50  0000 C CNN
F 1 "BLUE" H 9793 3886 50  0000 C CNN
F 2 "0_my_footprints2:led_blue" H 9800 4050 50  0001 C CNN
F 3 "~" H 9800 4050 50  0001 C CNN
	1    9800 4050
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 662B77B0
P 9500 4050
F 0 "R2" V 9650 4000 50  0000 L CNN
F 1 "560" V 9500 4050 50  0000 C CNN
F 2 "0_my_footprints2:resistor" V 9430 4050 50  0001 C CNN
F 3 "~" H 9500 4050 50  0001 C CNN
	1    9500 4050
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR05
U 1 1 662B77B6
P 9950 4050
F 0 "#PWR05" H 9950 3800 50  0001 C CNN
F 1 "GND" V 9950 3850 50  0000 C CNN
F 2 "" H 9950 4050 50  0001 C CNN
F 3 "" H 9950 4050 50  0001 C CNN
	1    9950 4050
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D1
U 1 1 662BFCA9
P 9800 3550
F 0 "D1" H 9793 3295 50  0000 C CNN
F 1 "GREEN" H 9793 3386 50  0000 C CNN
F 2 "0_my_footprints2:led_green" H 9800 3550 50  0001 C CNN
F 3 "~" H 9800 3550 50  0001 C CNN
	1    9800 3550
	-1   0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 662BFCAF
P 9500 3550
F 0 "R1" V 9650 3500 50  0000 L CNN
F 1 "220" V 9500 3550 50  0000 C CNN
F 2 "0_my_footprints2:resistor" V 9430 3550 50  0001 C CNN
F 3 "~" H 9500 3550 50  0001 C CNN
	1    9500 3550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 662BFCB5
P 9950 3550
F 0 "#PWR02" H 9950 3300 50  0001 C CNN
F 1 "GND" V 9950 3350 50  0000 C CNN
F 2 "" H 9950 3550 50  0001 C CNN
F 3 "" H 9950 3550 50  0001 C CNN
	1    9950 3550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 6632EF28
P 9950 4750
F 0 "#PWR06" H 9950 4500 50  0001 C CNN
F 1 "GND" V 9950 4550 50  0000 C CNN
F 2 "" H 9950 4750 50  0001 C CNN
F 3 "" H 9950 4750 50  0001 C CNN
	1    9950 4750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R4
U 1 1 663352F5
P 9500 5250
F 0 "R4" V 9650 5200 50  0000 L CNN
F 1 "220" V 9500 5250 50  0000 C CNN
F 2 "0_my_footprints2:resistor" V 9430 5250 50  0001 C CNN
F 3 "~" H 9500 5250 50  0001 C CNN
	1    9500 5250
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR08
U 1 1 663352FB
P 9950 5250
F 0 "#PWR08" H 9950 5000 50  0001 C CNN
F 1 "GND" V 9950 5050 50  0000 C CNN
F 2 "" H 9950 5250 50  0001 C CNN
F 3 "" H 9950 5250 50  0001 C CNN
	1    9950 5250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9050 6700 9350 6700
Wire Wire Line
	9050 7000 9200 7000
Text GLabel 9350 5250 0    50   Input ~ 0
RPI_I2S_RX_ACTIVE
Text GLabel 9350 4050 0    50   Input ~ 0
LED_PI_READY
Text GLabel 9350 3550 0    50   Input ~ 0
LED_PI_RUN
Text GLabel 4850 7600 3    50   Input ~ 10
LED_PI_READY
Text GLabel 4950 7600 3    50   Input ~ 10
LED_PI_RUN
Text GLabel 5250 7600 3    50   Input ~ 10
RPI_READY
Text GLabel 9350 4750 0    50   Input ~ 0
RPI_I2S_TX_ACTIVE
$Comp
L Device:LED D4
U 1 1 663352EF
P 9800 5250
F 0 "D4" H 9793 4995 50  0000 C CNN
F 1 "YELLOW" H 9793 5086 50  0000 C CNN
F 2 "0_my_footprints2:led_yellow" H 9800 5250 50  0001 C CNN
F 3 "~" H 9800 5250 50  0001 C CNN
	1    9800 5250
	-1   0    0    1   
$EndComp
$Comp
L Device:R R3
U 1 1 6632EF22
P 9500 4750
F 0 "R3" V 9650 4700 50  0000 L CNN
F 1 "220" V 9500 4750 50  0000 C CNN
F 2 "0_my_footprints2:resistor" V 9430 4750 50  0001 C CNN
F 3 "~" H 9500 4750 50  0001 C CNN
	1    9500 4750
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D3
U 1 1 6632EF1C
P 9800 4750
F 0 "D3" H 9793 4495 50  0000 C CNN
F 1 "YELLOW" H 9793 4586 50  0000 C CNN
F 2 "0_my_footprints2:led_yellow" H 9800 4750 50  0001 C CNN
F 3 "~" H 9800 4750 50  0001 C CNN
	1    9800 4750
	-1   0    0    1   
$EndComp
Text Notes 4750 6550 0    50   ~ 10
BOLD pins can be moved around
$Comp
L 0_my_teensy:myTeensy4.1 U2
U 1 1 6636A2E9
P 5650 6450
F 0 "U2" H 6000 6550 50  0001 R CNN
F 1 "myTeensy4.1" H 6150 6650 50  0000 R CNN
F 2 "0_my_teensy:teensy41" H 5350 5550 50  0001 C CNN
F 3 "" H 5350 5550 50  0001 C CNN
	1    5650 6450
	1    0    0    -1  
$EndComp
Text GLabel 12400 6750 3    50   Input ~ 0
RPI_I2S_TX_ACTIVE
$Comp
L Connector_Generic:Conn_01x01 J5
U 1 1 66503904
P 11800 4950
F 0 "J5" H 11750 5100 50  0001 L CNN
F 1 "RPI_RUN" H 11880 4901 50  0001 L CNN
F 2 "0_my_footprints2:pinSocket1x1" H 11800 4950 50  0001 C CNN
F 3 "~" H 11800 4950 50  0001 C CNN
	1    11800 4950
	1    0    0    -1  
$EndComp
Text GLabel 11600 4950 0    50   Input ~ 10
RPI_RUN
Text GLabel 12200 5550 1    50   Input ~ 10
I2S_FCLK
Text GLabel 12100 6750 3    50   Input ~ 10
I2S_TXB
Text GLabel 12000 6750 3    50   Input ~ 10
I2S_RXB
Text GLabel 13000 5550 1    50   Input ~ 0
RPI_MOSI
Text GLabel 12900 5550 1    50   Input ~ 0
RPI_MISO
Text GLabel 12800 5550 1    50   Input ~ 0
RPI_SCLK
Text GLabel 12800 6750 3    50   Input ~ 0
RPI_LED_CS
Text GLabel 12700 6750 3    50   Input ~ 0
RPI_TOUCH_CS
Text GLabel 12200 6750 3    50   Input ~ 0
RPI_READY
Text GLabel 12900 6750 3    50   Input ~ 0
RPI_I2S_RX_ACTIVE
$Comp
L power:GND #PWR012
U 1 1 6660E9EA
P 12700 5550
F 0 "#PWR012" H 12700 5300 50  0001 C CNN
F 1 "GND" V 12700 5350 50  0000 C CNN
F 2 "" H 12700 5550 50  0001 C CNN
F 3 "" H 12700 5550 50  0001 C CNN
	1    12700 5550
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR011
U 1 1 6660EE40
P 12000 5550
F 0 "#PWR011" H 12000 5300 50  0001 C CNN
F 1 "GND" V 12000 5350 50  0000 C CNN
F 2 "" H 12000 5550 50  0001 C CNN
F 3 "" H 12000 5550 50  0001 C CNN
	1    12000 5550
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR018
U 1 1 666109AB
P 13000 6750
F 0 "#PWR018" H 13000 6500 50  0001 C CNN
F 1 "GND" V 13000 6550 50  0000 C CNN
F 2 "" H 13000 6750 50  0001 C CNN
F 3 "" H 13000 6750 50  0001 C CNN
	1    13000 6750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR017
U 1 1 666110E8
P 12500 6750
F 0 "#PWR017" H 12500 6500 50  0001 C CNN
F 1 "GND" V 12500 6550 50  0000 C CNN
F 2 "" H 12500 6750 50  0001 C CNN
F 3 "" H 12500 6750 50  0001 C CNN
	1    12500 6750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 66611616
P 12300 6750
F 0 "#PWR016" H 12300 6500 50  0001 C CNN
F 1 "GND" V 12300 6550 50  0000 C CNN
F 2 "" H 12300 6750 50  0001 C CNN
F 3 "" H 12300 6750 50  0001 C CNN
	1    12300 6750
	1    0    0    -1  
$EndComp
Text GLabel 15500 5250 3    50   Input ~ 0
T40_RX1
Text GLabel 15600 5250 3    50   Input ~ 0
T40_TX1
Text GLabel 16500 3150 1    50   Input Italic 0
T40_RX3
Text GLabel 16600 3150 1    50   Input Italic 0
T40_TX3
Text GLabel 4650 7600 3    50   Input ~ 0
RPI_TX
Text GLabel 4750 7600 3    50   Input ~ 0
RPI_RX
Text GLabel 5450 7600 3    50   Input ~ 0
T40_RX1
Text GLabel 5350 7600 3    50   Input ~ 0
T40_TX1
Text GLabel 5650 5550 1    50   Input Italic 0
T40_RX3
Text GLabel 5750 5550 1    50   Input Italic 0
T40_TX3
Text Notes 4000 2300 0    50   ~ 10
The initial protoype will not have connectors for  EXPR, ROTARY. or BUTTONS.
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 664B6BE9
P 18250 4600
F 0 "J3" H 18330 4592 50  0001 L CNN
F 1 "USB Host" H 18000 4850 50  0000 C CNN
F 2 "0_my_footprints2:JST4" H 18250 4600 50  0001 C CNN
F 3 "~" H 18250 4600 50  0001 C CNN
	1    18250 4600
	1    0    0    1   
$EndComp
Text GLabel 15400 3150 1    50   Input ~ 0
T40_5V
Text GLabel 18050 4400 0    50   Input ~ 0
T40_5V
Text GLabel 18050 3650 0    50   Input ~ 0
HOST_D+
$Comp
L power:GND #PWR07
U 1 1 664E927B
P 18050 4700
F 0 "#PWR07" H 18050 4450 50  0001 C CNN
F 1 "GND" V 18050 4500 50  0000 C CNN
F 2 "" H 18050 4700 50  0001 C CNN
F 3 "" H 18050 4700 50  0001 C CNN
	1    18050 4700
	0    1    -1   0   
$EndComp
Text GLabel 18050 4500 0    50   Input ~ 0
HOST_D-
Text GLabel 18050 4600 0    50   Input ~ 0
HOST_D+
Text Notes 17250 3100 0    50   ~ 0
GPIO32 and Host +/- will be brought from the t40\nvia short cables with dupont pins that come out the \nback and that plug into a female connector on the \nmotherboard.
Text GLabel 18050 3750 0    50   Input ~ 10
I2S_RXB
Text GLabel 18050 3550 0    50   Input ~ 0
HOST_D-
$Comp
L 0_my_symbols:rpiA J7
U 1 1 66521D2F
P 12950 6400
F 0 "J7" H 13000 6550 50  0001 C CNN
F 1 "rpiA" H 13050 6550 50  0000 C CNN
F 2 "0_my_footprints2:pinSocket1x20" H 12800 6250 50  0001 C CNN
F 3 "" H 12800 6250 50  0001 C CNN
	1    12950 6400
	1    0    0    -1  
$EndComp
Text GLabel 13800 6750 3    50   Input ~ 0
RPI_5V
$Comp
L 0_my_symbols:rpiB J6
U 1 1 66525118
P 12950 5900
F 0 "J6" H 13150 5850 50  0001 C CNN
F 1 "rpiB" H 13300 5850 50  0000 C CNN
F 2 "0_my_footprints2:pinSocket1x20" H 12850 5500 50  0001 C CNN
F 3 "" H 12850 5500 50  0001 C CNN
	1    12950 5900
	1    0    0    -1  
$EndComp
Text Notes 4000 2400 0    50   ~ 0
See "prototype_extra_connectors.sch" for more info
Text GLabel 5150 7600 3    50   Input ~ 10
SENS_PI_RUN
Text GLabel 5050 7600 3    50   Input ~ 10
PI_REBOOT
$Comp
L Connector_Generic:Conn_01x03 J4
U 1 1 664C67F1
P 18250 3650
F 0 "J4" H 18168 3325 50  0001 C CNN
F 1 "40 bottom" H 18050 3400 50  0000 C CNN
F 2 "0_my_footprints2:pinSocket1x3" H 18250 3650 50  0001 C CNN
F 3 "~" H 18250 3650 50  0001 C CNN
	1    18250 3650
	1    0    0    1   
$EndComp
$Comp
L 0_my_teensy:myTeensy4.0 U1
U 1 1 664B86F7
P 15950 4150
F 0 "U1" H 15750 4150 60  0001 R CNN
F 1 "myTeensy4.0" H 16200 4050 60  0000 R CNN
F 2 "0_my_teensy:teensy40" V 16850 4200 60  0001 C CNN
F 3 "" V 16850 4200 60  0000 C CNN
	1    15950 4150
	1    0    0    -1  
$EndComp
$EndSCHEMATC

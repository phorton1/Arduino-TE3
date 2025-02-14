EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
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
L 0_my_symbols:74HC595 U1
U 1 1 6606EAF8
P 7250 1500
F 0 "U1" H 7628 1321 50  0000 L CNN
F 1 "74HC595" H 7628 1230 50  0000 L CNN
F 2 "Package_SO:SOIC-16_4.55x10.3mm_P1.27mm" H 7200 1250 50  0001 C CNN
F 3 "" H 7200 1250 50  0001 C CNN
	1    7250 1500
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW1
U 1 1 6606F9DD
P 6350 2750
F 0 "SW1" H 6350 2650 50  0000 C CNN
F 1 "SW1" H 6350 2894 50  0001 C CNN
F 2 "0_my_footprints:mySwitchSoft" H 6350 2750 50  0001 C CNN
F 3 "~" H 6350 2750 50  0001 C CNN
	1    6350 2750
	0    1    1    0   
$EndComp
$Comp
L LED:WS2812B D1
U 1 1 66071A8E
P 2750 1600
F 0 "D1" H 2500 1900 50  0000 L CNN
F 1 "WS2812B" H 3094 1555 50  0001 L CNN
F 2 "0_my_footprints:myWS2812" H 2800 1300 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 2850 1225 50  0001 L TNN
	1    2750 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 66073412
P 3200 3200
F 0 "C1" H 3200 3550 50  0000 C CNN
F 1 "100nf" H 3200 3450 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3238 3050 50  0001 C CNN
F 3 "~" H 3200 3200 50  0001 C CNN
	1    3200 3200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 660760DD
P 1250 1000
F 0 "#PWR02" H 1250 850 50  0001 C CNN
F 1 "+5V" V 1250 1200 50  0000 C CNN
F 2 "" H 1250 1000 50  0001 C CNN
F 3 "" H 1250 1000 50  0001 C CNN
	1    1250 1000
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 6607CA55
P 950 800
F 0 "J1" V 914 412 50  0000 R CNN
F 1 "Conn_01x06" V 823 412 50  0000 R CNN
F 2 "0_my_footprints:my6Pin-08mm" H 950 800 50  0001 C CNN
F 3 "~" H 950 800 50  0001 C CNN
	1    950  800 
	0    -1   -1   0   
$EndComp
Text GLabel 900  3400 1    50   Input ~ 0
LED_DOUT
$Comp
L Switch:SW_SPST SW2
U 1 1 660928C5
P 6700 2750
F 0 "SW2" H 6700 2650 50  0000 C CNN
F 1 "SW1" H 6700 2894 50  0001 C CNN
F 2 "0_my_footprints:mySwitchSoft" H 6700 2750 50  0001 C CNN
F 3 "~" H 6700 2750 50  0001 C CNN
	1    6700 2750
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_SPST SW3
U 1 1 66092C2E
P 7050 2750
F 0 "SW3" H 7050 2650 50  0000 C CNN
F 1 "SW1" H 7050 2894 50  0001 C CNN
F 2 "0_my_footprints:mySwitchSoft" H 7050 2750 50  0001 C CNN
F 3 "~" H 7050 2750 50  0001 C CNN
	1    7050 2750
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_SPST SW4
U 1 1 66092F3E
P 7400 2750
F 0 "SW4" H 7400 2650 50  0000 C CNN
F 1 "SW1" H 7400 2894 50  0001 C CNN
F 2 "0_my_footprints:mySwitchSoft" H 7400 2750 50  0001 C CNN
F 3 "~" H 7400 2750 50  0001 C CNN
	1    7400 2750
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_SPST SW5
U 1 1 660945C8
P 7750 2750
F 0 "SW5" H 7750 2650 50  0000 C CNN
F 1 "SW1" H 7750 2894 50  0001 C CNN
F 2 "0_my_footprints:mySwitchSoft" H 7750 2750 50  0001 C CNN
F 3 "~" H 7750 2750 50  0001 C CNN
	1    7750 2750
	0    1    1    0   
$EndComp
Text GLabel 6350 2950 3    50   Input ~ 0
BTN_SENSE
$Comp
L power:GND #PWR013
U 1 1 660A4A49
P 7950 2100
F 0 "#PWR013" H 7950 1850 50  0001 C CNN
F 1 "GND" V 7950 1900 50  0000 C CNN
F 2 "" H 7950 2100 50  0001 C CNN
F 3 "" H 7950 2100 50  0001 C CNN
	1    7950 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 2100 7950 2100
$Comp
L power:+5V #PWR03
U 1 1 660AD766
P 6850 1350
F 0 "#PWR03" H 6850 1200 50  0001 C CNN
F 1 "+5V" V 6850 1550 50  0000 C CNN
F 2 "" H 6850 1350 50  0001 C CNN
F 3 "" H 6850 1350 50  0001 C CNN
	1    6850 1350
	1    0    0    -1  
$EndComp
Text GLabel 7050 1350 1    50   Input ~ 0
BTN_DIN
Text GLabel 7550 1350 1    50   Input ~ 0
BTN_DOUT
Text GLabel 7350 1350 1    50   Input ~ 0
BTN_CLK
NoConn ~ 7350 2100
NoConn ~ 7450 2100
NoConn ~ 6950 1350
$Comp
L power:GND #PWR04
U 1 1 660B3EA6
P 7150 1350
F 0 "#PWR04" H 7150 1100 50  0001 C CNN
F 1 "GND" V 7150 1150 50  0000 C CNN
F 2 "" H 7150 1350 50  0001 C CNN
F 3 "" H 7150 1350 50  0001 C CNN
	1    7150 1350
	-1   0    0    1   
$EndComp
Text GLabel 7250 1350 1    50   Input ~ 0
BTN_CLK
$Comp
L power:+5V #PWR07
U 1 1 660C6F1A
P 2750 1300
F 0 "#PWR07" H 2750 1150 50  0001 C CNN
F 1 "+5V" V 2750 1500 50  0000 C CNN
F 2 "" H 2750 1300 50  0001 C CNN
F 3 "" H 2750 1300 50  0001 C CNN
	1    2750 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 660C8E8C
P 2750 1900
F 0 "#PWR014" H 2750 1650 50  0001 C CNN
F 1 "GND" V 2750 1700 50  0000 C CNN
F 2 "" H 2750 1900 50  0001 C CNN
F 3 "" H 2750 1900 50  0001 C CNN
	1    2750 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 1600 5450 1600
Text GLabel 5500 1600 2    50   Input ~ 0
LED_DOUT
Text GLabel 2450 1600 0    50   Input ~ 0
LED_DIN
$Comp
L LED:WS2812B D2
U 1 1 660FBD04
P 3350 1600
F 0 "D2" H 3100 1900 50  0000 L CNN
F 1 "WS2812B" H 3694 1555 50  0001 L CNN
F 2 "0_my_footprints:myWS2812" H 3400 1300 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 3450 1225 50  0001 L TNN
	1    3350 1600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR08
U 1 1 660FBD0A
P 3350 1300
F 0 "#PWR08" H 3350 1150 50  0001 C CNN
F 1 "+5V" V 3350 1500 50  0000 C CNN
F 2 "" H 3350 1300 50  0001 C CNN
F 3 "" H 3350 1300 50  0001 C CNN
	1    3350 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 660FBD10
P 3350 1900
F 0 "#PWR015" H 3350 1650 50  0001 C CNN
F 1 "GND" V 3350 1700 50  0000 C CNN
F 2 "" H 3350 1900 50  0001 C CNN
F 3 "" H 3350 1900 50  0001 C CNN
	1    3350 1900
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D3
U 1 1 660FDBA6
P 3950 1600
F 0 "D3" H 3700 1900 50  0000 L CNN
F 1 "WS2812B" H 4294 1555 50  0001 L CNN
F 2 "0_my_footprints:myWS2812" H 4000 1300 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 4050 1225 50  0001 L TNN
	1    3950 1600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR09
U 1 1 660FDBAC
P 3950 1300
F 0 "#PWR09" H 3950 1150 50  0001 C CNN
F 1 "+5V" V 3950 1500 50  0000 C CNN
F 2 "" H 3950 1300 50  0001 C CNN
F 3 "" H 3950 1300 50  0001 C CNN
	1    3950 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 660FDBB2
P 3950 1900
F 0 "#PWR016" H 3950 1650 50  0001 C CNN
F 1 "GND" V 3950 1700 50  0000 C CNN
F 2 "" H 3950 1900 50  0001 C CNN
F 3 "" H 3950 1900 50  0001 C CNN
	1    3950 1900
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D4
U 1 1 660FE5F8
P 4550 1600
F 0 "D4" H 4300 1900 50  0000 L CNN
F 1 "WS2812B" H 4894 1555 50  0001 L CNN
F 2 "0_my_footprints:myWS2812" H 4600 1300 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 4650 1225 50  0001 L TNN
	1    4550 1600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR010
U 1 1 660FE5FE
P 4550 1300
F 0 "#PWR010" H 4550 1150 50  0001 C CNN
F 1 "+5V" V 4550 1500 50  0000 C CNN
F 2 "" H 4550 1300 50  0001 C CNN
F 3 "" H 4550 1300 50  0001 C CNN
	1    4550 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR017
U 1 1 660FE604
P 4550 1900
F 0 "#PWR017" H 4550 1650 50  0001 C CNN
F 1 "GND" V 4550 1700 50  0000 C CNN
F 2 "" H 4550 1900 50  0001 C CNN
F 3 "" H 4550 1900 50  0001 C CNN
	1    4550 1900
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D5
U 1 1 660FEFBF
P 5150 1600
F 0 "D5" H 4900 1900 50  0000 L CNN
F 1 "WS2812B" H 5494 1555 50  0001 L CNN
F 2 "0_my_footprints:myWS2812" H 5200 1300 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 5250 1225 50  0001 L TNN
	1    5150 1600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR011
U 1 1 660FEFC5
P 5150 1300
F 0 "#PWR011" H 5150 1150 50  0001 C CNN
F 1 "+5V" V 5150 1500 50  0000 C CNN
F 2 "" H 5150 1300 50  0001 C CNN
F 3 "" H 5150 1300 50  0001 C CNN
	1    5150 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR018
U 1 1 660FEFCB
P 5150 1900
F 0 "#PWR018" H 5150 1650 50  0001 C CNN
F 1 "GND" V 5150 1700 50  0000 C CNN
F 2 "" H 5150 1900 50  0001 C CNN
F 3 "" H 5150 1900 50  0001 C CNN
	1    5150 1900
	1    0    0    -1  
$EndComp
Connection ~ 5450 1600
Wire Wire Line
	5450 1600 5500 1600
$Comp
L power:+5V #PWR06
U 1 1 6612DC07
P 2950 3050
F 0 "#PWR06" H 2950 2900 50  0001 C CNN
F 1 "+5V" V 2950 3250 50  0000 C CNN
F 2 "" H 2950 3050 50  0001 C CNN
F 3 "" H 2950 3050 50  0001 C CNN
	1    2950 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 6612F449
P 2950 3350
F 0 "#PWR012" H 2950 3100 50  0001 C CNN
F 1 "GND" V 2950 3150 50  0000 C CNN
F 2 "" H 2950 3350 50  0001 C CNN
F 3 "" H 2950 3350 50  0001 C CNN
	1    2950 3350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR020
U 1 1 66085251
P 1300 3400
F 0 "#PWR020" H 1300 3250 50  0001 C CNN
F 1 "+5V" V 1300 3600 50  0000 C CNN
F 2 "" H 1300 3400 50  0001 C CNN
F 3 "" H 1300 3400 50  0001 C CNN
	1    1300 3400
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J2
U 1 1 6608525E
P 1000 3600
F 0 "J2" V 964 3212 50  0000 R CNN
F 1 "Conn_01x06" V 873 3212 50  0000 R CNN
F 2 "0_my_footprints:my6Pin-08mm" H 1000 3600 50  0001 C CNN
F 3 "~" H 1000 3600 50  0001 C CNN
	1    1000 3600
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR019
U 1 1 66085257
P 1100 3400
F 0 "#PWR019" H 1100 3150 50  0001 C CNN
F 1 "GND" V 1100 3150 50  0000 C CNN
F 2 "" H 1100 3400 50  0001 C CNN
F 3 "" H 1100 3400 50  0001 C CNN
	1    1100 3400
	1    0    0    1   
$EndComp
$Comp
L Device:C C6
U 1 1 6611B57A
P 5000 3200
F 0 "C6" H 5115 3246 50  0000 L CNN
F 1 "10uf" H 5115 3155 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5038 3050 50  0001 C CNN
F 3 "~" H 5000 3200 50  0001 C CNN
	1    5000 3200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR021
U 1 1 6611B580
P 5000 3050
F 0 "#PWR021" H 5000 2900 50  0001 C CNN
F 1 "+5V" V 5000 3250 50  0000 C CNN
F 2 "" H 5000 3050 50  0001 C CNN
F 3 "" H 5000 3050 50  0001 C CNN
	1    5000 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR022
U 1 1 6611B586
P 5000 3350
F 0 "#PWR022" H 5000 3100 50  0001 C CNN
F 1 "GND" V 5000 3150 50  0000 C CNN
F 2 "" H 5000 3350 50  0001 C CNN
F 3 "" H 5000 3350 50  0001 C CNN
	1    5000 3350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 661253CC
P 3500 3200
F 0 "C2" H 3500 3550 50  0000 C CNN
F 1 "100nf" H 3500 3450 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3538 3050 50  0001 C CNN
F 3 "~" H 3500 3200 50  0001 C CNN
	1    3500 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 66125891
P 3800 3200
F 0 "C3" H 3800 3550 50  0000 C CNN
F 1 "100nf" H 3800 3450 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3838 3050 50  0001 C CNN
F 3 "~" H 3800 3200 50  0001 C CNN
	1    3800 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 66125E35
P 4100 3200
F 0 "C4" H 4100 3550 50  0000 C CNN
F 1 "100nf" H 4100 3450 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4138 3050 50  0001 C CNN
F 3 "~" H 4100 3200 50  0001 C CNN
	1    4100 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 66126E33
P 4400 3200
F 0 "C5" H 4400 3550 50  0000 C CNN
F 1 "100nf" H 4400 3450 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4438 3050 50  0001 C CNN
F 3 "~" H 4400 3200 50  0001 C CNN
	1    4400 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 3050 3200 3050
Connection ~ 3200 3050
Wire Wire Line
	3200 3050 3500 3050
Connection ~ 3500 3050
Wire Wire Line
	3500 3050 3800 3050
Connection ~ 3800 3050
Wire Wire Line
	3800 3050 4100 3050
Connection ~ 4100 3050
Wire Wire Line
	4100 3050 4400 3050
Wire Wire Line
	2950 3350 3200 3350
Connection ~ 3200 3350
Wire Wire Line
	3200 3350 3500 3350
Connection ~ 3500 3350
Wire Wire Line
	3500 3350 3800 3350
Connection ~ 3800 3350
Wire Wire Line
	3800 3350 4100 3350
Connection ~ 4100 3350
Wire Wire Line
	4100 3350 4400 3350
Text GLabel 6700 2950 3    50   Input ~ 0
BTN_SENSE
Text GLabel 7050 2950 3    50   Input ~ 0
BTN_SENSE
Text GLabel 7400 2950 3    50   Input ~ 0
BTN_SENSE
Text GLabel 7750 2950 3    50   Input ~ 0
BTN_SENSE
Text Notes 8000 1350 0    50   ~ 0
Note that BTN_SENSE\ndivided down to 3.3V\non the motherboard for\ncompatibility with teensy4.1
$Comp
L power:+5V #PWR0101
U 1 1 679D4168
P 7450 1350
F 0 "#PWR0101" H 7450 1200 50  0001 C CNN
F 1 "+5V" V 7450 1550 50  0000 C CNN
F 2 "" H 7450 1350 50  0001 C CNN
F 3 "" H 7450 1350 50  0001 C CNN
	1    7450 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 66075C0C
P 1050 1000
F 0 "#PWR01" H 1050 750 50  0001 C CNN
F 1 "GND" V 1050 800 50  0000 C CNN
F 2 "" H 1050 1000 50  0001 C CNN
F 3 "" H 1050 1000 50  0001 C CNN
	1    1050 1000
	1    0    0    -1  
$EndComp
Text GLabel 800  3400 1    50   Input ~ 0
BTN_SENSE
Text GLabel 1200 3400 1    50   Input ~ 0
BTN_CLK
Text GLabel 1000 3400 1    50   Input ~ 0
BTN_DOUT
Text GLabel 750  1000 3    50   Input ~ 0
BTN_SENSE
Text GLabel 850  1000 3    50   Input ~ 0
LED_DIN
Text GLabel 1150 1000 3    50   Input ~ 0
BTN_CLK
Text GLabel 950  1000 3    50   Input ~ 0
BTN_DIN
Wire Wire Line
	6350 2250 6850 2250
Wire Wire Line
	6850 2250 6850 2100
Wire Wire Line
	6350 2250 6350 2550
Wire Wire Line
	6700 2350 6950 2350
Wire Wire Line
	6950 2350 6950 2100
Wire Wire Line
	6700 2350 6700 2550
Wire Wire Line
	7050 2550 7050 2100
Wire Wire Line
	7400 2350 7150 2350
Wire Wire Line
	7150 2350 7150 2100
Wire Wire Line
	7400 2350 7400 2550
Wire Wire Line
	7750 2250 7250 2250
Wire Wire Line
	7250 2250 7250 2100
Wire Wire Line
	7750 2250 7750 2550
$EndSCHEMATC

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
Text Notes 7000 6850 0    79   ~ 0
Reverse Engineered Schematics
$Comp
L MCU_Microchip_PIC16:PIC16F690-ISO U1
U 1 1 60F1E4DF
P 3000 1700
F 0 "U1" H 3000 1750 50  0000 C CNN
F 1 "PIC16F690-ISO" H 3000 1550 50  0000 C CNN
F 2 "" H 3000 1700 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/41262E.pdf" H 3000 1700 50  0001 C CNN
	1    3000 1700
	1    0    0    -1  
$EndComp
$Comp
L Connector:RJ45 J1
U 1 1 60F1FDFF
P 1450 4300
F 0 "J1" H 1450 4350 50  0000 C CNN
F 1 "RJ45 HBX+DEC Motor" V 1100 4300 50  0000 C CNN
F 2 "" V 1450 4325 50  0001 C CNN
F 3 "~" V 1450 4325 50  0001 C CNN
	1    1450 4300
	1    0    0    -1  
$EndComp
$Comp
L Connector:RJ45 J2
U 1 1 60F22196
P 2900 4300
F 0 "J2" H 2900 4300 50  0000 C CNN
F 1 "RJ45 HBX+DEC Motor" V 2550 4300 50  0000 C CNN
F 2 "" V 2900 4325 50  0001 C CNN
F 3 "~" V 2900 4325 50  0001 C CNN
	1    2900 4300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male CON2
U 1 1 60F256A9
P 6750 900
F 0 "CON2" V 6700 900 50  0000 C CNN
F 1 "Motor Connector" H 7050 750 50  0000 C CNN
F 2 "" H 6750 900 50  0001 C CNN
F 3 "~" H 6750 900 50  0001 C CNN
	1    6750 900 
	1    0    0    -1  
$EndComp
Text Label 7050 900  0    50   ~ 0
M+
Text Label 7050 1000 0    50   ~ 0
M-
Wire Wire Line
	6950 900  7050 900 
Wire Wire Line
	6950 1000 7050 1000
$Comp
L Connector_Generic:Conn_02x04_Counter_Clockwise U4
U 1 1 60F2A975
P 5650 1100
F 0 "U4" H 5700 1417 50  0000 C CNN
F 1 "TC4426A" H 5700 1326 50  0000 C CNN
F 2 "" H 5650 1100 50  0001 C CNN
F 3 "~" H 5650 1100 50  0001 C CNN
	1    5650 1100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x04_Counter_Clockwise Q1
U 1 1 60F2C581
P 5650 1750
F 0 "Q1" H 5700 2067 50  0000 C CNN
F 1 "4947A Dual P-Channel Mosfet" H 5700 1976 50  0000 C CNN
F 2 "" H 5650 1750 50  0001 C CNN
F 3 "~" H 5650 1750 50  0001 C CNN
	1    5650 1750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x04_Counter_Clockwise Q4
U 1 1 60F2D130
P 7000 1750
F 0 "Q4" H 7050 2067 50  0000 C CNN
F 1 "4936A Dual N-Channel Mosfet" H 7050 1976 50  0000 C CNN
F 2 "" H 7000 1750 50  0001 C CNN
F 3 "~" H 7000 1750 50  0001 C CNN
	1    7000 1750
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male U2_PD
U 1 1 60F3306B
P 9150 1050
F 0 "U2_PD" H 9258 1331 50  0000 C CNN
F 1 "Motor Encoder Photodiodes" H 9650 800 50  0000 C CNN
F 2 "" H 9150 1050 50  0001 C CNN
F 3 "~" H 9150 1050 50  0001 C CNN
	1    9150 1050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male U2_LED
U 1 1 60F34313
P 9150 1550
F 0 "U2_LED" H 9300 1650 50  0000 C CNN
F 1 "Motor Encoder LED" H 9500 1400 50  0000 C CNN
F 2 "" H 9150 1550 50  0001 C CNN
F 3 "~" H 9150 1550 50  0001 C CNN
	1    9150 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal X1
U 1 1 60F36B03
P 1600 3000
F 0 "X1" H 1600 3268 50  0000 C CNN
F 1 "20 MHz Crystal" H 1600 3177 50  0000 C CNN
F 2 "" H 1600 3000 50  0001 C CNN
F 3 "~" H 1600 3000 50  0001 C CNN
	1    1600 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:L L1
U 1 1 60F3789D
P 2400 5350
F 0 "L1" V 2310 5350 50  0000 C CNN
F 1 "L" V 2310 5350 50  0001 C CNN
F 2 "" H 2400 5350 50  0001 C CNN
F 3 "~" H 2400 5350 50  0001 C CNN
	1    2400 5350
	0    1    1    0   
$EndComp
$Comp
L Device:D D4
U 1 1 60F3A9A8
P 2050 4950
F 0 "D4" H 1900 4900 50  0000 C CNN
F 1 "D" H 2050 5076 50  0001 C CNN
F 2 "" H 2050 4950 50  0001 C CNN
F 3 "~" H 2050 4950 50  0001 C CNN
	1    2050 4950
	-1   0    0    1   
$EndComp
$Comp
L Connector:RJ12 J3
U 1 1 60F3DF43
P 5500 3700
F 0 "J3" H 5500 3750 50  0000 C CNN
F 1 "RJ12 (ST-04 Guiding Port)" V 5150 3750 50  0000 C CNN
F 2 "" V 5500 3725 50  0001 C CNN
F 3 "~" V 5500 3725 50  0001 C CNN
	1    5500 3700
	1    0    0    -1  
$EndComp
Text Label 1950 3900 0    50   ~ 0
GND
Text Label 2200 5350 2    50   ~ 0
VCC_12V_OUT
Text Label 2600 5350 0    50   ~ 0
VCC_12V
Text Label 1950 4000 0    50   ~ 0
GND
Wire Wire Line
	1850 3900 1950 3900
Wire Wire Line
	1850 4000 1950 4000
Wire Wire Line
	1850 4500 1950 4500
Wire Wire Line
	1850 4600 1950 4600
Text Label 3450 3900 0    50   ~ 0
GND
Text Label 3450 4000 0    50   ~ 0
GND
Wire Wire Line
	3300 3900 3450 3900
Wire Wire Line
	3300 4000 3450 4000
Wire Wire Line
	3300 4500 3450 4500
Wire Wire Line
	3300 4600 3450 4600
Text Label 1950 4200 0    50   ~ 0
IN_TX
Text Label 1950 4300 0    50   ~ 0
IN_RX
Text Label 1950 4100 0    50   ~ 0
RA_SEL
Text Label 1950 4400 0    50   ~ 0
DEC_SEL
Wire Wire Line
	1850 4100 1950 4100
Wire Wire Line
	1850 4200 1950 4200
Wire Wire Line
	1850 4300 1950 4300
Wire Wire Line
	1850 4400 1950 4400
Text Label 3450 4100 0    50   ~ 0
RA_SEL
Text Label 3450 4200 0    50   ~ 0
IN_TX
Text Label 3450 4300 0    50   ~ 0
IN_RX
Text Label 3450 4400 0    50   ~ 0
DEC_SEL
Wire Wire Line
	3300 4100 3450 4100
Wire Wire Line
	3300 4200 3450 4200
Wire Wire Line
	3300 4300 3450 4300
Wire Wire Line
	3300 4400 3450 4400
$Comp
L Device:R R1
U 1 1 60F33D10
P 4100 3050
F 0 "R1" V 4100 3050 50  0000 C CNN
F 1 "R" V 3984 3050 50  0001 C CNN
F 2 "" V 4030 3050 50  0001 C CNN
F 3 "~" H 4100 3050 50  0001 C CNN
	1    4100 3050
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 60F35BA9
P 8400 2000
F 0 "R2" V 8400 2000 50  0000 C CNN
F 1 "R" V 8284 2000 50  0001 C CNN
F 2 "" V 8330 2000 50  0001 C CNN
F 3 "~" H 8400 2000 50  0001 C CNN
	1    8400 2000
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 60F3620F
P 8400 1650
F 0 "R3" V 8400 1650 50  0000 C CNN
F 1 "R" V 8284 1650 50  0001 C CNN
F 2 "" V 8330 1650 50  0001 C CNN
F 3 "~" H 8400 1650 50  0001 C CNN
	1    8400 1650
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 60F3644C
P 8400 1900
F 0 "R4" V 8400 1900 50  0000 C CNN
F 1 "R" V 8284 1900 50  0001 C CNN
F 2 "" V 8330 1900 50  0001 C CNN
F 3 "~" H 8400 1900 50  0001 C CNN
	1    8400 1900
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 60F36642
P 8400 1150
F 0 "R5" V 8400 1150 50  0000 C CNN
F 1 "R" V 8284 1150 50  0001 C CNN
F 2 "" V 8330 1150 50  0001 C CNN
F 3 "~" H 8400 1150 50  0001 C CNN
	1    8400 1150
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 60F3B364
P 8400 1500
F 0 "R6" V 8400 1500 50  0000 C CNN
F 1 "R" V 8284 1500 50  0001 C CNN
F 2 "" V 8330 1500 50  0001 C CNN
F 3 "~" H 8400 1500 50  0001 C CNN
	1    8400 1500
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 60F3B36A
P 8400 1750
F 0 "R7" V 8400 1750 50  0000 C CNN
F 1 "R" V 8284 1750 50  0001 C CNN
F 2 "" V 8330 1750 50  0001 C CNN
F 3 "~" H 8400 1750 50  0001 C CNN
	1    8400 1750
	0    1    1    0   
$EndComp
$Comp
L Device:R R8
U 1 1 60F3B370
P 7150 1200
F 0 "R8" V 7150 1200 50  0000 C CNN
F 1 "R" V 7034 1200 50  0001 C CNN
F 2 "" V 7080 1200 50  0001 C CNN
F 3 "~" H 7150 1200 50  0001 C CNN
	1    7150 1200
	0    1    1    0   
$EndComp
$Comp
L Device:R R9
U 1 1 60F3B376
P 2400 5150
F 0 "R9" V 2400 5150 50  0000 C CNN
F 1 "R" V 2284 5150 50  0001 C CNN
F 2 "" V 2330 5150 50  0001 C CNN
F 3 "~" H 2400 5150 50  0001 C CNN
	1    2400 5150
	0    1    1    0   
$EndComp
$Comp
L Device:R R10
U 1 1 60F3B37C
P 6850 3400
F 0 "R10" V 6850 3400 50  0000 C CNN
F 1 "R" V 6734 3400 50  0001 C CNN
F 2 "" V 6780 3400 50  0001 C CNN
F 3 "~" H 6850 3400 50  0001 C CNN
	1    6850 3400
	0    1    1    0   
$EndComp
$Comp
L Device:R R11
U 1 1 60F4448E
P 6850 3500
F 0 "R11" V 6850 3500 50  0000 C CNN
F 1 "R" V 6734 3500 50  0001 C CNN
F 2 "" V 6780 3500 50  0001 C CNN
F 3 "~" H 6850 3500 50  0001 C CNN
	1    6850 3500
	0    1    1    0   
$EndComp
$Comp
L Device:R R12
U 1 1 60F44494
P 6850 3600
F 0 "R12" V 6850 3600 50  0000 C CNN
F 1 "R" V 6734 3600 50  0001 C CNN
F 2 "" V 6780 3600 50  0001 C CNN
F 3 "~" H 6850 3600 50  0001 C CNN
	1    6850 3600
	0    1    1    0   
$EndComp
$Comp
L Device:R R13
U 1 1 60F4449A
P 6850 3700
F 0 "R13" V 6850 3700 50  0000 C CNN
F 1 "R" V 6734 3700 50  0001 C CNN
F 2 "" V 6780 3700 50  0001 C CNN
F 3 "~" H 6850 3700 50  0001 C CNN
	1    6850 3700
	0    1    1    0   
$EndComp
$Comp
L Device:R R15
U 1 1 60F444A6
P 2400 4950
F 0 "R15" V 2400 4950 50  0000 C CNN
F 1 "R" V 2284 4950 50  0001 C CNN
F 2 "" V 2330 4950 50  0001 C CNN
F 3 "~" H 2400 4950 50  0001 C CNN
	1    2400 4950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R17
U 1 1 60F444B2
P 2400 5050
F 0 "R17" V 2400 5050 50  0000 C CNN
F 1 "R" V 2284 5050 50  0001 C CNN
F 2 "" V 2330 5050 50  0001 C CNN
F 3 "~" H 2400 5050 50  0001 C CNN
	1    2400 5050
	0    1    1    0   
$EndComp
$Comp
L Device:R R18
U 1 1 60F444B8
P 9650 1550
F 0 "R18" V 9650 1550 50  0000 C CNN
F 1 "R" V 9534 1550 50  0001 C CNN
F 2 "" V 9580 1550 50  0001 C CNN
F 3 "~" H 9650 1550 50  0001 C CNN
	1    9650 1550
	0    1    1    0   
$EndComp
$Comp
L Device:R R20
U 1 1 60F444C4
P 6150 2350
F 0 "R20" V 6150 2350 50  0000 C CNN
F 1 "R" V 6034 2350 50  0001 C CNN
F 2 "" V 6080 2350 50  0001 C CNN
F 3 "~" H 6150 2350 50  0001 C CNN
	1    6150 2350
	0    1    1    0   
$EndComp
$Comp
L Device:R R21
U 1 1 60F486E6
P 4100 2800
F 0 "R21" V 4100 2800 50  0000 C CNN
F 1 "R" V 3984 2800 50  0001 C CNN
F 2 "" V 4030 2800 50  0001 C CNN
F 3 "~" H 4100 2800 50  0001 C CNN
	1    4100 2800
	0    1    1    0   
$EndComp
$Comp
L Device:R R23
U 1 1 60F486F2
P 8400 2150
F 0 "R23" V 8400 2150 50  0000 C CNN
F 1 "R" V 8284 2150 50  0001 C CNN
F 2 "" V 8330 2150 50  0001 C CNN
F 3 "~" H 8400 2150 50  0001 C CNN
	1    8400 2150
	0    1    1    0   
$EndComp
$Comp
L Device:R R24
U 1 1 60F486F8
P 4500 2700
F 0 "R24" V 4500 2700 50  0000 C CNN
F 1 "R" V 4384 2700 50  0001 C CNN
F 2 "" V 4430 2700 50  0001 C CNN
F 3 "~" H 4500 2700 50  0001 C CNN
	1    4500 2700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R26
U 1 1 60F48704
P 4100 2700
F 0 "R26" V 4100 2700 50  0000 C CNN
F 1 "R" V 3984 2700 50  0001 C CNN
F 2 "" V 4030 2700 50  0001 C CNN
F 3 "~" H 4100 2700 50  0001 C CNN
	1    4100 2700
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C1
U 1 1 60F50301
P 4500 3250
F 0 "C1" V 4450 3350 50  0000 L CNN
F 1 "C" H 4615 3205 50  0001 L CNN
F 2 "" H 4538 3100 50  0001 C CNN
F 3 "~" H 4500 3250 50  0001 C CNN
	1    4500 3250
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C2
U 1 1 60F52F7E
P 1400 3200
F 0 "C2" V 1350 3300 50  0000 L CNN
F 1 "C" H 1515 3155 50  0001 L CNN
F 2 "" H 1438 3050 50  0001 C CNN
F 3 "~" H 1400 3200 50  0001 C CNN
	1    1400 3200
	-1   0    0    1   
$EndComp
$Comp
L Device:C C3
U 1 1 60F53606
P 1800 3200
F 0 "C3" V 1850 3300 50  0000 L CNN
F 1 "C" H 1915 3155 50  0001 L CNN
F 2 "" H 1838 3050 50  0001 C CNN
F 3 "~" H 1800 3200 50  0001 C CNN
	1    1800 3200
	-1   0    0    1   
$EndComp
$Comp
L Device:C C4
U 1 1 60F53ABB
P 6800 1200
F 0 "C4" V 6750 1300 50  0000 L CNN
F 1 "C" H 6915 1155 50  0001 L CNN
F 2 "" H 6838 1050 50  0001 C CNN
F 3 "~" H 6800 1200 50  0001 C CNN
	1    6800 1200
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C8
U 1 1 60F59881
P 4500 3050
F 0 "C8" V 4450 3150 50  0000 L CNN
F 1 "C" H 4615 3005 50  0001 L CNN
F 2 "" H 4538 2900 50  0001 C CNN
F 3 "~" H 4500 3050 50  0001 C CNN
	1    4500 3050
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C9
U 1 1 60F59887
P 6150 2500
F 0 "C9" V 6100 2600 50  0000 L CNN
F 1 "C" H 6265 2455 50  0001 L CNN
F 2 "" H 6188 2350 50  0001 C CNN
F 3 "~" H 6150 2500 50  0001 C CNN
	1    6150 2500
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C10
U 1 1 60F5988D
P 8400 1000
F 0 "C10" V 8350 1100 50  0000 L CNN
F 1 "C" H 8515 955 50  0001 L CNN
F 2 "" H 8438 850 50  0001 C CNN
F 3 "~" H 8400 1000 50  0001 C CNN
	1    8400 1000
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C11
U 1 1 60F5BDB5
P 8400 1350
F 0 "C11" V 8350 1450 50  0000 L CNN
F 1 "C" H 8515 1305 50  0001 L CNN
F 2 "" H 8438 1200 50  0001 C CNN
F 3 "~" H 8400 1350 50  0001 C CNN
	1    8400 1350
	0    -1   -1   0   
$EndComp
Text Label 1350 3000 2    50   ~ 0
OSC1
Text Label 1850 3000 0    50   ~ 0
OSC2
Text Label 1850 3450 0    50   ~ 0
GND
Wire Wire Line
	1350 3000 1400 3000
Wire Wire Line
	1400 3050 1400 3000
Connection ~ 1400 3000
Wire Wire Line
	1400 3000 1450 3000
Wire Wire Line
	1750 3000 1800 3000
Wire Wire Line
	1800 3050 1800 3000
Connection ~ 1800 3000
Wire Wire Line
	1800 3000 1850 3000
Wire Wire Line
	1400 3350 1400 3450
Wire Wire Line
	1800 3450 1800 3350
Text Label 4600 1700 0    50   ~ 0
OSC1
Text Label 4600 1600 0    50   ~ 0
OSC2
Wire Wire Line
	4500 1600 4600 1600
Wire Wire Line
	4500 1700 4600 1700
Text Label 3000 800  0    50   ~ 0
VCC_5V
Text Label 3050 2600 0    50   ~ 0
GND
Wire Wire Line
	3000 800  3000 900 
Wire Wire Line
	3000 2500 3000 2600
Wire Wire Line
	3000 2600 3050 2600
NoConn ~ 5450 1000
NoConn ~ 5950 1000
Text Label 5350 1100 2    50   ~ 0
U4_IN1
Text Label 5350 1300 2    50   ~ 0
U4_IN2
Text Label 5350 1200 2    50   ~ 0
GND
Text Label 6000 1100 0    50   ~ 0
~U4_OUT1
Text Label 6000 1300 0    50   ~ 0
~U4_OUT2
Text Label 6000 1200 0    50   ~ 0
VCC_12V
Wire Wire Line
	5350 1100 5450 1100
Wire Wire Line
	5350 1200 5450 1200
Wire Wire Line
	5350 1300 5450 1300
Wire Wire Line
	5950 1100 6000 1100
Wire Wire Line
	5950 1200 6000 1200
Wire Wire Line
	5950 1300 6000 1300
Text Label 5400 1650 2    50   ~ 0
VCC_12V
Text Label 5400 1750 2    50   ~ 0
~U4_OUT1
Text Label 5400 1950 2    50   ~ 0
~U4_OUT2
Text Label 5400 1850 2    50   ~ 0
VCC_12V
Text Label 6050 1950 0    50   ~ 0
M+
Text Label 6050 1750 0    50   ~ 0
M-
Wire Wire Line
	5950 1650 6000 1650
Wire Wire Line
	6000 1650 6000 1750
Wire Wire Line
	6000 1750 5950 1750
Wire Wire Line
	5950 1850 6000 1850
Wire Wire Line
	6000 1850 6000 1950
Wire Wire Line
	6000 1950 5950 1950
Wire Wire Line
	6000 1950 6050 1950
Connection ~ 6000 1950
Wire Wire Line
	6000 1750 6050 1750
Connection ~ 6000 1750
Text Label 6750 1650 2    50   ~ 0
Q4_SRC
Text Label 6750 1850 2    50   ~ 0
Q4_SRC
Text Label 7400 1950 0    50   ~ 0
M-
Text Label 7400 1750 0    50   ~ 0
M+
Wire Wire Line
	7300 1650 7350 1650
Wire Wire Line
	7350 1650 7350 1750
Wire Wire Line
	7350 1750 7300 1750
Wire Wire Line
	7400 1750 7350 1750
Connection ~ 7350 1750
Wire Wire Line
	7300 1850 7350 1850
Wire Wire Line
	7350 1850 7350 1950
Wire Wire Line
	7350 1950 7300 1950
Wire Wire Line
	7400 1950 7350 1950
Connection ~ 7350 1950
Wire Wire Line
	6750 1650 6800 1650
Wire Wire Line
	6750 1850 6800 1850
Wire Wire Line
	1400 3450 1800 3450
Wire Wire Line
	1850 3450 1800 3450
Connection ~ 1800 3450
Text Label 9900 1650 0    50   ~ 0
GND
Text Label 9900 1550 0    50   ~ 0
VCC_5V
Wire Wire Line
	9350 1650 9900 1650
Wire Wire Line
	9350 1550 9500 1550
Wire Wire Line
	9800 1550 9900 1550
Text Label 9900 1150 0    50   ~ 0
GND
Text Label 9900 1050 0    50   ~ 0
VCC_5V
$Comp
L Device:R R?
U 1 1 61051EAF
P 9600 1050
F 0 "R?" V 9600 1050 50  0000 C CNN
F 1 "R" V 9484 1050 50  0001 C CNN
F 2 "" V 9530 1050 50  0001 C CNN
F 3 "~" H 9600 1050 50  0001 C CNN
	1    9600 1050
	0    1    1    0   
$EndComp
Wire Wire Line
	9350 1050 9450 1050
Wire Wire Line
	9750 1050 9900 1050
Wire Wire Line
	9350 1150 9900 1150
$Comp
L Device:R R?
U 1 1 6105D45E
P 9600 850
F 0 "R?" V 9600 850 50  0000 C CNN
F 1 "R" V 9484 850 50  0001 C CNN
F 2 "" V 9530 850 50  0001 C CNN
F 3 "~" H 9600 850 50  0001 C CNN
	1    9600 850 
	0    1    1    0   
$EndComp
Text Label 9900 850  0    50   ~ 0
VCC_5V
Wire Wire Line
	9900 850  9750 850 
Wire Wire Line
	9450 850  9350 850 
Wire Wire Line
	9350 850  9350 950 
Wire Wire Line
	9350 950  9900 950 
Connection ~ 9350 950 
Text Label 9900 950  0    50   ~ 0
ENC1
Text Label 9900 1250 0    50   ~ 0
ENC2
Wire Wire Line
	9350 1250 9900 1250
Wire Wire Line
	2200 5350 2250 5350
Wire Wire Line
	2550 5350 2600 5350
Text Label 1950 4500 0    50   ~ 0
VCC_12V_OUT
Text Label 1950 4600 0    50   ~ 0
VCC_12V_OUT
Text Label 3450 4500 0    50   ~ 0
VCC_12V_OUT
Text Label 3450 4600 0    50   ~ 0
VCC_12V_OUT
Text Label 8650 1750 0    50   ~ 0
GND
Text Label 8650 1650 0    50   ~ 0
U4_IN1
Wire Wire Line
	8550 1650 8650 1650
Wire Wire Line
	8550 1750 8650 1750
Wire Wire Line
	8250 1650 8200 1650
Wire Wire Line
	8200 1650 8200 1750
Wire Wire Line
	8200 1750 8250 1750
Text Label 8650 2000 0    50   ~ 0
GND
Text Label 8650 1900 0    50   ~ 0
U4_IN2
Wire Wire Line
	8250 1900 8200 1900
Wire Wire Line
	8200 1900 8200 2000
Wire Wire Line
	8200 2000 8250 2000
Wire Wire Line
	8550 1900 8650 1900
Wire Wire Line
	8550 2000 8650 2000
Text Label 6750 1750 2    50   ~ 0
Q4_G1
Text Label 6750 1950 2    50   ~ 0
Q4_G2
Wire Wire Line
	6750 1750 6800 1750
Wire Wire Line
	6750 1950 6800 1950
Text Label 8150 1900 2    50   ~ 0
Q4_G2
Wire Wire Line
	8150 1900 8200 1900
Connection ~ 8200 1900
Text Label 8150 1650 2    50   ~ 0
Q4_G1
Wire Wire Line
	8150 1650 8200 1650
Connection ~ 8200 1650
Text Label 8150 2150 2    50   ~ 0
Q4_SRC
Text Label 8650 2150 0    50   ~ 0
GND
Wire Wire Line
	8150 2150 8250 2150
Wire Wire Line
	8550 2150 8650 2150
Text Label 4700 2700 0    50   ~ 0
GND
Wire Wire Line
	4700 2700 4650 2700
Wire Wire Line
	4300 2800 4250 2800
Text Label 1400 1800 2    50   ~ 0
MCU_RC6
Wire Wire Line
	1400 1800 1500 1800
Text Label 3900 2800 2    50   ~ 0
MCU_RC6
Wire Wire Line
	3900 2800 3950 2800
Text Label 8000 1000 2    50   ~ 0
VCC_12V
Wire Wire Line
	8000 1000 8150 1000
Wire Wire Line
	8150 1000 8150 1150
Wire Wire Line
	8150 1150 8250 1150
Connection ~ 8150 1000
Wire Wire Line
	8150 1000 8250 1000
Wire Wire Line
	8150 1350 8250 1350
Wire Wire Line
	8150 1350 8150 1500
Wire Wire Line
	8150 1500 8250 1500
Wire Wire Line
	8550 1000 8600 1000
Wire Wire Line
	8600 1000 8600 1150
Wire Wire Line
	8600 1150 8550 1150
Wire Wire Line
	8550 1350 8600 1350
Wire Wire Line
	8600 1350 8600 1500
Wire Wire Line
	8600 1500 8550 1500
Wire Wire Line
	8600 1000 8650 1000
Connection ~ 8600 1000
Wire Wire Line
	8600 1350 8650 1350
Connection ~ 8600 1350
Text Label 8650 1350 0    50   ~ 0
~U4_OUT2
Text Label 8650 1000 0    50   ~ 0
~U4_OUT1
Text Label 8000 1350 2    50   ~ 0
VCC_12V
Wire Wire Line
	8000 1350 8150 1350
Connection ~ 8150 1350
Text Label 6600 1200 2    50   ~ 0
M+
Text Label 7350 1200 0    50   ~ 0
M-
Wire Wire Line
	6600 1200 6650 1200
Wire Wire Line
	6950 1200 7000 1200
Wire Wire Line
	7300 1200 7350 1200
Wire Wire Line
	6000 2350 5900 2350
Wire Wire Line
	5900 2350 5900 2500
Wire Wire Line
	5900 2500 6000 2500
Text Label 6400 2500 0    50   ~ 0
GND
Wire Wire Line
	6300 2500 6400 2500
Text Label 6400 2350 0    50   ~ 0
Q4_SRC
Wire Wire Line
	6300 2350 6400 2350
Text Label 5850 2350 2    50   ~ 0
MCU_RC3
Wire Wire Line
	5850 2350 5900 2350
Connection ~ 5900 2350
Text Label 1400 1500 2    50   ~ 0
MCU_RC3
Wire Wire Line
	1400 1500 1500 1500
Text Label 7250 2350 2    50   ~ 0
MCU_RC4
Text Label 7250 2450 2    50   ~ 0
MCU_RC5
Text Label 7400 2350 0    50   ~ 0
Q4_G1
Text Label 7400 2450 0    50   ~ 0
Q4_G2
Wire Wire Line
	7250 2350 7400 2350
Wire Wire Line
	7250 2450 7400 2450
Text Label 1400 1600 2    50   ~ 0
MCU_RC4
Text Label 1400 1700 2    50   ~ 0
MCU_RC5
Wire Wire Line
	1400 1600 1500 1600
Wire Wire Line
	1400 1700 1500 1700
Wire Wire Line
	4250 3050 4300 3050
Text Label 4700 3050 0    50   ~ 0
GND
Text Label 4700 3250 0    50   ~ 0
GND
Wire Wire Line
	4650 3050 4700 3050
Wire Wire Line
	4650 3250 4700 3250
Text Label 4600 1500 0    50   ~ 0
Vpp
Wire Wire Line
	4500 1500 4600 1500
Text Label 3900 3050 2    50   ~ 0
Vpp
Wire Wire Line
	3900 3050 3950 3050
Wire Wire Line
	3950 3050 3950 3250
Wire Wire Line
	3950 3250 4350 3250
Connection ~ 3950 3050
Text Label 3900 2950 2    50   ~ 0
VCC_5V
Wire Wire Line
	3900 2950 4300 2950
Wire Wire Line
	4300 2950 4300 3050
Connection ~ 4300 3050
Wire Wire Line
	4300 3050 4350 3050
$Comp
L Device:R R?
U 1 1 614D0743
P 6300 3050
F 0 "R?" V 6300 3050 50  0000 C CNN
F 1 "R" V 6184 3050 50  0001 C CNN
F 2 "" V 6230 3050 50  0001 C CNN
F 3 "~" H 6300 3050 50  0001 C CNN
	1    6300 3050
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 614D153E
P 6400 3050
F 0 "R?" V 6400 3050 50  0000 C CNN
F 1 "R" V 6284 3050 50  0001 C CNN
F 2 "" V 6330 3050 50  0001 C CNN
F 3 "~" H 6400 3050 50  0001 C CNN
	1    6400 3050
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 614D17AF
P 6500 3050
F 0 "R?" V 6500 3050 50  0000 C CNN
F 1 "R" V 6384 3050 50  0001 C CNN
F 2 "" V 6430 3050 50  0001 C CNN
F 3 "~" H 6500 3050 50  0001 C CNN
	1    6500 3050
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 614D192D
P 6600 3050
F 0 "R?" V 6600 3050 50  0000 C CNN
F 1 "R" V 6484 3050 50  0001 C CNN
F 2 "" V 6530 3050 50  0001 C CNN
F 3 "~" H 6600 3050 50  0001 C CNN
	1    6600 3050
	-1   0    0    1   
$EndComp
Text Label 6200 2850 2    50   ~ 0
VCC_5V
Wire Wire Line
	6200 2850 6300 2850
Wire Wire Line
	6600 2850 6600 2900
Wire Wire Line
	6500 2850 6500 2900
Connection ~ 6500 2850
Wire Wire Line
	6500 2850 6600 2850
Wire Wire Line
	6400 2850 6400 2900
Connection ~ 6400 2850
Wire Wire Line
	6400 2850 6500 2850
Wire Wire Line
	6300 2850 6300 2900
Connection ~ 6300 2850
Wire Wire Line
	6300 2850 6400 2850
NoConn ~ 5900 3900
Text Label 5950 3800 0    50   ~ 0
GND
Wire Wire Line
	5900 3800 5950 3800
Wire Wire Line
	5900 3400 6300 3400
Wire Wire Line
	5900 3500 6400 3500
Wire Wire Line
	5900 3600 6500 3600
Wire Wire Line
	5900 3700 6600 3700
Wire Wire Line
	6300 3200 6300 3400
Connection ~ 6300 3400
Wire Wire Line
	6300 3400 6700 3400
Wire Wire Line
	6400 3200 6400 3500
Connection ~ 6400 3500
Wire Wire Line
	6400 3500 6700 3500
Wire Wire Line
	6500 3200 6500 3600
Connection ~ 6500 3600
Wire Wire Line
	6500 3600 6700 3600
Wire Wire Line
	6600 3200 6600 3700
Connection ~ 6600 3700
Wire Wire Line
	6600 3700 6700 3700
Text Label 7100 3400 0    50   ~ 0
RA+
Text Label 7100 3500 0    50   ~ 0
DEC+
Text Label 7100 3600 0    50   ~ 0
DEC-
Text Label 7100 3700 0    50   ~ 0
RA-
Wire Wire Line
	7000 3400 7100 3400
Wire Wire Line
	7000 3500 7100 3500
Wire Wire Line
	7000 3600 7100 3600
Wire Wire Line
	7000 3700 7100 3700
Text Label 4600 2000 0    50   ~ 0
MCU_RX
Text Label 4600 2200 0    50   ~ 0
MCU_TX
Wire Wire Line
	4500 2000 4600 2000
Wire Wire Line
	4500 2200 4600 2200
Wire Wire Line
	2200 4950 2250 4950
Wire Wire Line
	2550 4950 2600 4950
Text Label 1850 4950 2    50   ~ 0
IN_TX
Wire Wire Line
	1850 4950 1900 4950
Text Label 1850 5050 2    50   ~ 0
IN_RX
Wire Wire Line
	1850 5050 2250 5050
Wire Wire Line
	2550 5050 2600 5050
Text Label 4600 2100 0    50   ~ 0
ENC1
Text Label 4600 1900 0    50   ~ 0
ENC2
Wire Wire Line
	4500 1900 4600 1900
Wire Wire Line
	4500 2100 4600 2100
Text Label 1400 1900 2    50   ~ 0
DEC-
Text Label 1400 1400 2    50   ~ 0
RA+
Text Label 1400 1300 2    50   ~ 0
DEC+
Text Label 1400 1200 2    50   ~ 0
RA-
Wire Wire Line
	1400 1200 1500 1200
Wire Wire Line
	1400 1300 1500 1300
Wire Wire Line
	1400 1400 1500 1400
Wire Wire Line
	1400 1900 1500 1900
Text Label 1850 5150 2    50   ~ 0
DEC_SEL
Text Label 2600 5050 0    50   ~ 0
MCU_RX
Text Label 2600 4950 0    50   ~ 0
MCU_TX
Text Label 4600 1400 0    50   ~ 0
MCU_RA2
Wire Wire Line
	4500 1400 4600 1400
Text Label 2600 5150 0    50   ~ 0
MCU_RA2
Wire Wire Line
	2550 5150 2600 5150
Wire Wire Line
	1850 5150 2250 5150
Text Label 4600 1200 0    50   ~ 0
MCU_PGD
Text Label 4600 1300 0    50   ~ 0
MCU_PGC
Wire Wire Line
	4500 1200 4600 1200
Wire Wire Line
	4500 1300 4600 1300
Wire Wire Line
	3950 2700 3900 2700
Text Label 3900 2700 2    50   ~ 0
VCC_12V
Wire Wire Line
	4250 2700 4300 2700
Wire Wire Line
	4300 2800 4300 2700
Connection ~ 4300 2700
Wire Wire Line
	4300 2700 4350 2700
Wire Notes Line
	5050 700  5050 2650
Wire Notes Line
	5050 2650 9050 2650
Wire Notes Line
	9050 2650 9050 700 
Wire Notes Line
	9050 700  5050 700 
Text Notes 5050 700  0    50   ~ 0
Motor Driver Assembly
Connection ~ 9900 4050
Wire Wire Line
	10250 3950 10250 4050
Wire Wire Line
	9900 3950 9900 4050
Wire Wire Line
	9900 4050 10250 4050
Wire Wire Line
	9800 4050 9900 4050
Wire Wire Line
	10250 3650 10300 3650
Connection ~ 10250 3650
Wire Wire Line
	8650 4050 8700 4050
Text Label 8700 4050 0    50   ~ 0
GND
Connection ~ 8300 3800
Wire Wire Line
	8300 4050 8350 4050
Wire Wire Line
	8300 3800 8300 4050
Wire Wire Line
	8650 3800 8700 3800
Text Label 8700 3800 0    50   ~ 0
GND
Wire Wire Line
	8300 3650 8700 3650
Connection ~ 8300 3650
Wire Wire Line
	8300 3800 8350 3800
Wire Wire Line
	8300 3650 8300 3800
Wire Wire Line
	8250 3650 8300 3650
Text Label 8700 3650 0    50   ~ 0
VCC_12V
Wire Wire Line
	7900 3400 7950 3400
Connection ~ 7900 3400
Wire Wire Line
	7900 3650 7950 3650
Wire Wire Line
	7900 3400 7900 3650
Wire Wire Line
	8650 3400 8700 3400
Wire Wire Line
	8250 3400 8350 3400
Wire Wire Line
	7850 3400 7900 3400
Text Label 8700 3400 0    50   ~ 0
GND
Text Label 7850 3400 2    50   ~ 0
INPUT_12V
Text Label 8250 3050 0    50   ~ 0
INPUT_12V
$Comp
L Device:CP C13
U 1 1 60F5C29B
P 8500 4050
F 0 "C13" V 8450 3850 50  0000 L CNN
F 1 "C" H 8615 4005 50  0001 L CNN
F 2 "" H 8538 3900 50  0001 C CNN
F 3 "~" H 8500 4050 50  0001 C CNN
	1    8500 4050
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C7
U 1 1 60F5987B
P 10250 3800
F 0 "C7" V 10200 3900 50  0000 L CNN
F 1 "C" H 10365 3755 50  0001 L CNN
F 2 "" H 10288 3650 50  0001 C CNN
F 3 "~" H 10250 3800 50  0001 C CNN
	1    10250 3800
	-1   0    0    1   
$EndComp
$Comp
L Device:C C6
U 1 1 60F59875
P 8500 3800
F 0 "C6" V 8450 3650 50  0000 L CNN
F 1 "C" H 8615 3755 50  0001 L CNN
F 2 "" H 8538 3650 50  0001 C CNN
F 3 "~" H 8500 3800 50  0001 C CNN
	1    8500 3800
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R22
U 1 1 60F486EC
P 8500 3400
F 0 "R22" V 8500 3400 50  0000 C CNN
F 1 "R" V 8384 3400 50  0001 C CNN
F 2 "" V 8430 3400 50  0001 C CNN
F 3 "~" H 8500 3400 50  0001 C CNN
	1    8500 3400
	0    1    1    0   
$EndComp
Wire Wire Line
	10200 3650 10250 3650
Wire Wire Line
	9500 3650 9600 3650
Text Label 9500 3650 2    50   ~ 0
VCC_12V
Text Label 10300 3650 0    50   ~ 0
VCC_5V
Text Label 9800 4050 2    50   ~ 0
GND
$Comp
L Device:D D1
U 1 1 60F3D4B0
P 8100 3650
F 0 "D1" H 8100 3775 50  0000 C CNN
F 1 "D" H 8100 3776 50  0001 C CNN
F 2 "" H 8100 3650 50  0001 C CNN
F 3 "~" H 8100 3650 50  0001 C CNN
	1    8100 3650
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D2
U 1 1 60F3C17E
P 8100 3400
F 0 "D2" H 8093 3525 50  0000 C CNN
F 1 "POWER LED" H 8100 3250 50  0000 C CNN
F 2 "" H 8100 3400 50  0001 C CNN
F 3 "~" H 8100 3400 50  0001 C CNN
	1    8100 3400
	-1   0    0    1   
$EndComp
$Comp
L Regulator_Linear:AZ1117-5.0 U3
U 1 1 60F2E36D
P 9900 3650
F 0 "U3" H 9750 3500 50  0000 C CNN
F 1 "AZ1117-5.0 (GH15E)" H 9900 3800 50  0000 C CNN
F 2 "" H 9900 3900 50  0001 C CIN
F 3 "https://www.diodes.com/assets/Datasheets/AZ1117.pdf" H 9900 3650 50  0001 C CNN
	1    9900 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 3250 10300 3250
Wire Wire Line
	10200 3050 10300 3050
Text Label 10300 3250 0    50   ~ 0
GND
Text Label 10300 3050 0    50   ~ 0
INPUT_12V
$Comp
L Connector:Barrel_Jack JP4
U 1 1 60F28BE1
P 9900 3150
F 0 "JP4" H 10000 3150 50  0000 C CNN
F 1 "Power Jack" H 9900 3350 50  0000 C CNN
F 2 "" H 9950 3110 50  0001 C CNN
F 3 "~" H 9950 3110 50  0001 C CNN
	1    9900 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 3150 8250 3150
Wire Wire Line
	7950 3050 8250 3050
Text Label 8250 3150 0    50   ~ 0
PWR_SW_OUT_12V
$Comp
L Connector:Conn_01x02_Male CON1
U 1 1 60F24F54
P 7750 3050
F 0 "CON1" V 7700 3000 50  0000 C CNN
F 1 "POWER Switch" H 8100 3200 50  0000 C CNN
F 2 "" H 7750 3050 50  0001 C CNN
F 3 "~" H 7750 3050 50  0001 C CNN
	1    7750 3050
	1    0    0    -1  
$EndComp
Text Notes 7000 6700 0    79   ~ 0
Bresser EXOS2 GoTo RA Axis Motor Rev.1.03 (2016-06)
Wire Notes Line
	7400 2800 7400 4200
Wire Notes Line
	7400 4200 10750 4200
Wire Notes Line
	10750 4200 10750 2800
Wire Notes Line
	10750 2800 7400 2800
Text Notes 7400 2800 0    50   ~ 0
Power Supply Assembly
Wire Notes Line
	9100 700  9100 1750
Wire Notes Line
	9100 1750 10200 1750
Wire Notes Line
	10200 1750 10200 700 
Wire Notes Line
	10200 700  9100 700 
Text Notes 9100 700  0    50   ~ 0
Motor Encoder Assembly
Wire Notes Line
	1100 2650 1100 3550
Wire Notes Line
	1100 3550 2100 3550
Wire Notes Line
	2100 3550 2100 2650
Wire Notes Line
	2100 2650 1100 2650
Text Notes 1100 2650 0    50   ~ 0
MCU Quartz Assembly
Wire Notes Line
	1000 700  1000 3600
Wire Notes Line
	1000 3600 5000 3600
Wire Notes Line
	5000 3600 5000 700 
Wire Notes Line
	5000 700  1000 700 
Text Notes 1000 700  0    50   ~ 0
MCU Assembly
Wire Notes Line
	5050 2750 5050 4200
Wire Notes Line
	5050 4200 7350 4200
Wire Notes Line
	7350 4200 7350 2750
Wire Notes Line
	7350 2750 5050 2750
Text Notes 5050 2750 0    50   ~ 0
ST-4 Autoguiding Port Assembly
Text Notes 6700 3150 0    50   ~ 0
These Resistors\nare not\nlabeled!
Wire Notes Line
	1000 3700 1000 5400
Wire Notes Line
	1000 5400 4000 5400
Wire Notes Line
	4000 5400 4000 3700
Wire Notes Line
	4000 3700 1000 3700
Text Notes 1000 3700 0    50   ~ 0
System Power and Communication Port Assembly
$Comp
L Device:C C12
U 1 1 60F5C291
P 1200 7100
F 0 "C12" V 1150 7200 50  0000 L CNN
F 1 "C" H 1315 7055 50  0001 L CNN
F 2 "" H 1238 6950 50  0001 C CNN
F 3 "~" H 1200 7100 50  0001 C CNN
	1    1200 7100
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C5
U 1 1 60F54271
P 1200 7300
F 0 "C5" V 1150 7400 50  0000 L CNN
F 1 "C" H 1315 7255 50  0001 L CNN
F 2 "" H 1238 7150 50  0001 C CNN
F 3 "~" H 1200 7300 50  0001 C CNN
	1    1200 7300
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R25
U 1 1 60F486FE
P 750 7350
F 0 "R25" V 750 7350 50  0000 C CNN
F 1 "R" V 634 7350 50  0001 C CNN
F 2 "" V 680 7350 50  0001 C CNN
F 3 "~" H 750 7350 50  0001 C CNN
	1    750  7350
	0    1    1    0   
$EndComp
$Comp
L Device:R R19
U 1 1 60F444BE
P 750 7250
F 0 "R19" V 750 7250 50  0000 C CNN
F 1 "R" V 634 7250 50  0001 C CNN
F 2 "" V 680 7250 50  0001 C CNN
F 3 "~" H 750 7250 50  0001 C CNN
	1    750  7250
	0    1    1    0   
$EndComp
$Comp
L Device:R R16
U 1 1 60F444AC
P 750 7150
F 0 "R16" V 750 7150 50  0000 C CNN
F 1 "R" V 634 7150 50  0001 C CNN
F 2 "" V 680 7150 50  0001 C CNN
F 3 "~" H 750 7150 50  0001 C CNN
	1    750  7150
	0    1    1    0   
$EndComp
$Comp
L Device:R R14
U 1 1 60F444A0
P 750 7050
F 0 "R14" V 750 7050 50  0000 C CNN
F 1 "R" V 634 7050 50  0001 C CNN
F 2 "" V 680 7050 50  0001 C CNN
F 3 "~" H 750 7050 50  0001 C CNN
	1    750  7050
	0    1    1    0   
$EndComp
Text Notes 550  7700 0    50   ~ 0
These enumerated Components\nwere not found and may not exist\non the Board!
Wire Notes Line
	500  6900 500  7750
Wire Notes Line
	500  7750 1900 7750
Wire Notes Line
	1900 7750 1900 6900
Wire Notes Line
	1900 6900 500  6900
Text Notes 500  6900 0    50   ~ 0
Unused Components
$EndSCHEMATC
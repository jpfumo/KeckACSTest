EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
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
L DEV-16771:DEV-16771 U1
U 1 1 620588A6
P 4700 3950
F 0 "U1" H 4700 6117 50  0000 C CNN
F 1 "DEV-16771" H 4700 6026 50  0000 C CNN
F 2 "Kona1:teensy41" H 4700 3950 50  0001 L BNN
F 3 "" H 4700 3950 50  0001 L BNN
F 4 "4.1" H 4700 3950 50  0001 L BNN "PARTREV"
F 5 "SparkFun Electronics" H 4700 3950 50  0001 L BNN "MANUFACTURER"
F 6 "4.07mm" H 4700 3950 50  0001 L BNN "MAXIMUM_PACKAGE_HEIGHT"
F 7 "Manufacturer recommendations" H 4700 3950 50  0001 L BNN "STANDARD"
	1    4700 3950
	1    0    0    -1  
$EndComp
$Comp
L Kona_Parts:SEL_SW SW1
U 1 1 62058680
P 7650 2500
F 0 "SW1" H 7878 2151 50  0000 L CNN
F 1 "SEL_SW" H 7878 2060 50  0000 L CNN
F 2 "Kona1:SEL_SW" H 7650 2500 50  0001 C CNN
F 3 "" H 7650 2500 50  0001 C CNN
	1    7650 2500
	1    0    0    -1  
$EndComp
$Comp
L Kona_Parts:FDN358P MOSFET1
U 1 1 62155F17
P 6850 3700
F 0 "MOSFET1" H 7280 3647 60  0000 L CNN
F 1 "FDN358P" H 7280 3753 60  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7300 3440 60  0001 C CNN
F 3 "" H 6850 3700 60  0000 C CNN
	1    6850 3700
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 62157F66
P 7900 5400
F 0 "#PWR0103" H 7900 5150 50  0001 C CNN
F 1 "GND" H 7905 5227 50  0000 C CNN
F 2 "" H 7900 5400 50  0001 C CNN
F 3 "" H 7900 5400 50  0001 C CNN
	1    7900 5400
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0104
U 1 1 6215891D
P 7150 3350
F 0 "#PWR0104" H 7150 3200 50  0001 C CNN
F 1 "+3V3" H 7165 3523 50  0000 C CNN
F 2 "" H 7150 3350 50  0001 C CNN
F 3 "" H 7150 3350 50  0001 C CNN
	1    7150 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 3350 7150 3400
$Comp
L Device:R R3
U 1 1 621595E1
P 6700 3550
F 0 "R3" H 6770 3596 50  0000 L CNN
F 1 "10K0" V 6600 3450 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6630 3550 50  0001 C CNN
F 3 "~" H 6700 3550 50  0001 C CNN
	1    6700 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 3400 7150 3400
Connection ~ 7150 3400
Wire Wire Line
	7150 3400 7150 3500
Wire Wire Line
	6850 3700 6700 3700
$Comp
L power:+3V3 #PWR0105
U 1 1 6215A2F2
P 5950 2050
F 0 "#PWR0105" H 5950 1900 50  0001 C CNN
F 1 "+3V3" H 5965 2223 50  0000 C CNN
F 2 "" H 5950 2050 50  0001 C CNN
F 3 "" H 5950 2050 50  0001 C CNN
	1    5950 2050
	1    0    0    -1  
$EndComp
Text GLabel 6850 2800 0    50   Input ~ 0
SW_UP
$Comp
L power:GND #PWR0106
U 1 1 6215B195
P 7500 3250
F 0 "#PWR0106" H 7500 3000 50  0001 C CNN
F 1 "GND" H 7505 3077 50  0000 C CNN
F 2 "" H 7500 3250 50  0001 C CNN
F 3 "" H 7500 3250 50  0001 C CNN
	1    7500 3250
	1    0    0    -1  
$EndComp
Text GLabel 6850 2900 0    50   Input ~ 0
SW_SEL
Text GLabel 6850 3000 0    50   Input ~ 0
SW_DWN
Text GLabel 3500 4450 0    50   Input ~ 0
SW_UP
Text GLabel 5900 3950 2    50   Input ~ 0
SW_SEL
Text GLabel 5900 4050 2    50   Input ~ 0
SW_DWN
Wire Wire Line
	3900 4450 3500 4450
Wire Wire Line
	5500 4050 5900 4050
Wire Wire Line
	5900 3950 5500 3950
$Comp
L power:GND #PWR0109
U 1 1 6215D09B
P 5750 6100
F 0 "#PWR0109" H 5750 5850 50  0001 C CNN
F 1 "GND" H 5755 5927 50  0000 C CNN
F 2 "" H 5750 6100 50  0001 C CNN
F 3 "" H 5750 6100 50  0001 C CNN
	1    5750 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 5750 5750 5750
Wire Wire Line
	5750 5750 5750 5850
Wire Wire Line
	5500 5850 5750 5850
Connection ~ 5750 5850
Wire Wire Line
	5750 5850 5750 6100
Text GLabel 3500 4550 0    50   Input ~ 0
SCK
Wire Wire Line
	3900 4550 3500 4550
Text GLabel 7650 4650 0    50   Input ~ 0
SCK
Wire Wire Line
	7650 4650 8000 4650
Text GLabel 3100 3450 0    50   Input ~ 0
RSTn
Text GLabel 7650 4350 0    50   Input ~ 0
RSTn
Wire Wire Line
	8000 4350 7650 4350
Text GLabel 7600 4250 0    50   Input ~ 0
CS
Wire Wire Line
	8000 4250 7700 4250
Text GLabel 7600 4450 0    50   Input ~ 0
DC
Wire Wire Line
	8000 4450 7600 4450
Text GLabel 5950 3650 2    50   Input ~ 0
DC
Wire Wire Line
	5950 3650 5500 3650
$Comp
L power:+3V3 #PWR0110
U 1 1 62161E59
P 8000 3850
F 0 "#PWR0110" H 8000 3700 50  0001 C CNN
F 1 "+3V3" H 8015 4023 50  0000 C CNN
F 2 "" H 8000 3850 50  0001 C CNN
F 3 "" H 8000 3850 50  0001 C CNN
	1    8000 3850
	1    0    0    -1  
$EndComp
Text GLabel 2200 5250 0    50   Input ~ 0
I2C_SCL
Text GLabel 2200 5150 0    50   Input ~ 0
I2C_SDA
$Comp
L Device:R R4
U 1 1 6216A2FD
P 6900 2200
F 0 "R4" V 6850 2300 50  0000 L CNN
F 1 "10K0" V 6850 1900 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6830 2200 50  0001 C CNN
F 3 "~" H 6900 2200 50  0001 C CNN
	1    6900 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 6216A74C
P 7000 2200
F 0 "R5" V 6950 2300 50  0000 L CNN
F 1 "10K0" V 6950 1900 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6930 2200 50  0001 C CNN
F 3 "~" H 7000 2200 50  0001 C CNN
	1    7000 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 6216A967
P 7100 2200
F 0 "R6" V 7050 2300 50  0000 L CNN
F 1 "10K0" V 7050 1900 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7030 2200 50  0001 C CNN
F 3 "~" H 7100 2200 50  0001 C CNN
	1    7100 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 2800 6900 2800
Wire Wire Line
	6850 2900 7000 2900
Wire Wire Line
	6850 3000 7100 3000
Wire Wire Line
	6900 2350 6900 2800
Connection ~ 6900 2800
Wire Wire Line
	6900 2800 7200 2800
Wire Wire Line
	7000 2350 7000 2900
Connection ~ 7000 2900
Wire Wire Line
	7000 2900 7300 2900
Wire Wire Line
	7100 2350 7100 3000
Connection ~ 7100 3000
Wire Wire Line
	7100 3000 7400 3000
$Comp
L power:+3V3 #PWR0111
U 1 1 62171E64
P 7000 1850
F 0 "#PWR0111" H 7000 1700 50  0001 C CNN
F 1 "+3V3" H 7015 2023 50  0000 C CNN
F 2 "" H 7000 1850 50  0001 C CNN
F 3 "" H 7000 1850 50  0001 C CNN
	1    7000 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 2050 6900 1950
Wire Wire Line
	6900 1950 7000 1950
Wire Wire Line
	7100 1950 7100 2050
Wire Wire Line
	7000 1850 7000 1950
Connection ~ 7000 1950
Wire Wire Line
	7000 1950 7100 1950
Wire Wire Line
	7000 2050 7000 1950
$Comp
L Device:C C1
U 1 1 621752C0
P 7750 2000
F 0 "C1" V 7498 2000 50  0000 C CNN
F 1 "0U1" V 7589 2000 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 7788 1850 50  0001 C CNN
F 3 "~" H 7750 2000 50  0001 C CNN
	1    7750 2000
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 62175EF8
P 7750 2250
F 0 "C2" V 7498 2250 50  0000 C CNN
F 1 "0U1" V 7589 2250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 7788 2100 50  0001 C CNN
F 3 "~" H 7750 2250 50  0001 C CNN
	1    7750 2250
	0    1    1    0   
$EndComp
$Comp
L Device:C C3
U 1 1 621761DB
P 7750 2500
F 0 "C3" V 7498 2500 50  0000 C CNN
F 1 "0U1" V 7589 2500 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 7788 2350 50  0001 C CNN
F 3 "~" H 7750 2500 50  0001 C CNN
	1    7750 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	7600 2000 7200 2000
Wire Wire Line
	7200 2000 7200 2800
Connection ~ 7200 2800
Wire Wire Line
	7200 2800 7500 2800
Wire Wire Line
	7600 2250 7300 2250
Wire Wire Line
	7300 2250 7300 2900
Connection ~ 7300 2900
Wire Wire Line
	7300 2900 7500 2900
Wire Wire Line
	7600 2500 7400 2500
Wire Wire Line
	7400 2500 7400 3000
Connection ~ 7400 3000
Wire Wire Line
	7400 3000 7500 3000
$Comp
L power:GND #PWR0112
U 1 1 6217C0F8
P 8200 2600
F 0 "#PWR0112" H 8200 2350 50  0001 C CNN
F 1 "GND" H 8205 2427 50  0000 C CNN
F 2 "" H 8200 2600 50  0001 C CNN
F 3 "" H 8200 2600 50  0001 C CNN
	1    8200 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 2000 8200 2000
Wire Wire Line
	8200 2000 8200 2250
Wire Wire Line
	7900 2250 8200 2250
Connection ~ 8200 2250
Wire Wire Line
	7900 2500 8200 2500
Wire Wire Line
	8200 2250 8200 2500
Connection ~ 8200 2500
Wire Wire Line
	8200 2500 8200 2600
$Comp
L Device:R R2
U 1 1 6218079F
P 2550 4950
F 0 "R2" V 2600 5050 50  0000 L CNN
F 1 "4K75" V 2650 4850 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2480 4950 50  0001 C CNN
F 3 "~" H 2550 4950 50  0001 C CNN
	1    2550 4950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 621810DD
P 2350 4950
F 0 "R1" V 2300 5050 50  0000 L CNN
F 1 "4K75" V 2250 4850 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2280 4950 50  0001 C CNN
F 3 "~" H 2350 4950 50  0001 C CNN
	1    2350 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 5150 2350 5150
Wire Wire Line
	2200 5250 2550 5250
Wire Wire Line
	2350 5100 2350 5150
Connection ~ 2350 5150
Wire Wire Line
	2350 5150 2850 5150
Wire Wire Line
	2550 5100 2550 5250
Connection ~ 2550 5250
$Comp
L power:+3V3 #PWR0113
U 1 1 62188761
P 2450 4650
F 0 "#PWR0113" H 2450 4500 50  0001 C CNN
F 1 "+3V3" H 2465 4823 50  0000 C CNN
F 2 "" H 2450 4650 50  0001 C CNN
F 3 "" H 2450 4650 50  0001 C CNN
	1    2450 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 4800 2350 4750
Wire Wire Line
	2350 4750 2450 4750
Wire Wire Line
	2550 4750 2550 4800
Wire Wire Line
	2450 4650 2450 4750
Connection ~ 2450 4750
Wire Wire Line
	2450 4750 2550 4750
$Comp
L Connector:TestPoint SCL1
U 1 1 6218CBF1
P 3150 4900
F 0 "SCL1" H 3208 5018 50  0000 L CNN
F 1 "SCL" H 3208 4927 50  0000 L CNN
F 2 "TestPoint:TestPoint_Keystone_5019_Minature" H 3350 4900 50  0001 C CNN
F 3 "~" H 3350 4900 50  0001 C CNN
	1    3150 4900
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint SDA1
U 1 1 6218D5B2
P 2850 4900
F 0 "SDA1" H 2908 5018 50  0000 L CNN
F 1 "SDA" H 2908 4927 50  0000 L CNN
F 2 "TestPoint:TestPoint_Keystone_5019_Minature" H 3050 4900 50  0001 C CNN
F 3 "~" H 3050 4900 50  0001 C CNN
	1    2850 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 3450 3250 3450
Text GLabel 1700 3500 0    50   Input ~ 0
BL_EN
Text GLabel 6650 3800 0    50   Input ~ 0
BL_EN
Wire Wire Line
	6650 3800 6700 3800
Wire Wire Line
	6700 3800 6700 3700
Connection ~ 6700 3700
$Comp
L Switch:SW_Push SW2
U 1 1 6220C541
P 2800 2950
F 0 "SW2" H 2800 3235 50  0000 C CNN
F 1 "SW_Push" H 2800 3144 50  0000 C CNN
F 2 "Button_Switch_SMD:Panasonic_EVQPUL_EVQPUC" H 2800 3150 50  0001 C CNN
F 3 "~" H 2800 3150 50  0001 C CNN
	1    2800 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 6220D2D3
P 2500 3100
F 0 "#PWR0115" H 2500 2850 50  0001 C CNN
F 1 "GND" H 2505 2927 50  0000 C CNN
F 2 "" H 2500 3100 50  0001 C CNN
F 3 "" H 2500 3100 50  0001 C CNN
	1    2500 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 2950 2500 2950
Wire Wire Line
	2500 2950 2500 3100
$Comp
L Transistor_BJT:MMBT3904 Q1
U 1 1 62190197
P 2050 3750
F 0 "Q1" H 2241 3796 50  0000 L CNN
F 1 "MMBT3904" H 2241 3705 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2250 3675 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/2N3903-D.PDF" H 2050 3750 50  0001 L CNN
	1    2050 3750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1700 3500 1950 3500
Wire Wire Line
	1950 3500 1950 3550
Wire Wire Line
	2250 3750 2350 3750
$Comp
L power:GND #PWR0114
U 1 1 62198982
P 1950 4250
F 0 "#PWR0114" H 1950 4000 50  0001 C CNN
F 1 "GND" H 1955 4077 50  0000 C CNN
F 2 "" H 1950 4250 50  0001 C CNN
F 3 "" H 1950 4250 50  0001 C CNN
	1    1950 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 6219C8A7
P 2250 4000
F 0 "R9" V 2300 4100 50  0000 L CNN
F 1 "10K0" V 2350 3900 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2180 4000 50  0001 C CNN
F 3 "~" H 2250 4000 50  0001 C CNN
	1    2250 4000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 6219CE07
P 2500 3750
F 0 "R10" V 2550 3850 50  0000 L CNN
F 1 "1K0" V 2600 3650 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2430 3750 50  0001 C CNN
F 3 "~" H 2500 3750 50  0001 C CNN
	1    2500 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	2650 3750 3900 3750
Wire Wire Line
	1950 3950 1950 4200
Wire Wire Line
	2250 4150 2250 4200
Wire Wire Line
	2250 4200 1950 4200
Connection ~ 1950 4200
Wire Wire Line
	1950 4200 1950 4250
Wire Wire Line
	2250 3850 2250 3750
Connection ~ 2250 3750
$Comp
L Device:Battery_Cell BT1
U 1 1 621A9DF2
P 6300 2650
F 0 "BT1" H 6418 2746 50  0000 L CNN
F 1 "Battery_Cell" H 6418 2655 50  0000 L CNN
F 2 "Kona1:BatteryHolder_Seiko_MS621F" V 6300 2710 50  0001 C CNN
F 3 "~" V 6300 2710 50  0001 C CNN
	1    6300 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 621AAB19
P 6300 2800
F 0 "#PWR0116" H 6300 2550 50  0001 C CNN
F 1 "GND" H 6305 2627 50  0000 C CNN
F 2 "" H 6300 2800 50  0001 C CNN
F 3 "" H 6300 2800 50  0001 C CNN
	1    6300 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 2800 6300 2750
Wire Wire Line
	5600 2050 5500 2050
$Comp
L Connector:TestPoint GND1
U 1 1 622A7AB2
P 1600 4200
F 0 "GND1" H 1658 4318 50  0000 L CNN
F 1 "TestPoint" H 1658 4227 50  0000 L CNN
F 2 "TestPoint:TestPoint_Keystone_5019_Minature" H 1800 4200 50  0001 C CNN
F 3 "~" H 1800 4200 50  0001 C CNN
	1    1600 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 4200 1950 4200
Text GLabel 5700 3550 2    50   Input ~ 0
NEOPIXEL
Wire Wire Line
	5500 3550 5700 3550
Text GLabel 2550 1400 0    50   Input ~ 0
NEOPIXEL
$Comp
L power:GND #PWR0126
U 1 1 623974DE
P 2850 1850
F 0 "#PWR0126" H 2850 1600 50  0001 C CNN
F 1 "GND" H 2855 1677 50  0000 C CNN
F 2 "" H 2850 1850 50  0001 C CNN
F 3 "" H 2850 1850 50  0001 C CNN
	1    2850 1850
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0127
U 1 1 623977E6
P 2850 1000
F 0 "#PWR0127" H 2850 850 50  0001 C CNN
F 1 "+3V3" H 2865 1173 50  0000 C CNN
F 2 "" H 2850 1000 50  0001 C CNN
F 3 "" H 2850 1000 50  0001 C CNN
	1    2850 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 1000 2850 1100
Wire Wire Line
	2850 1700 2850 1850
$Comp
L Kona_Parts:TFT_LCD U2
U 1 1 62417584
P 8300 3700
F 0 "U2" H 8778 2996 50  0000 L CNN
F 1 "TFT_LCD" H 8778 2905 50  0000 L CNN
F 2 "Kona1:TFT_DISP_2P2" H 8300 3700 118 0001 C CNN
F 3 "" H 8300 3700 118 0001 C CNN
	1    8300 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 4050 8000 3850
Wire Wire Line
	7050 4350 7050 4850
Wire Wire Line
	7050 4850 8000 4850
Wire Wire Line
	5500 4350 6700 4350
Wire Wire Line
	8000 4750 7150 4750
Wire Wire Line
	7150 3900 7150 4750
Wire Wire Line
	8000 4150 7900 4150
Wire Wire Line
	7900 4150 7900 5400
Wire Wire Line
	7500 3250 7500 3100
Wire Wire Line
	5500 4450 6700 4450
Wire Wire Line
	6950 4450 6950 4550
Wire Wire Line
	6950 4550 8000 4550
$Comp
L LED:WS2812S D2
U 1 1 624BD658
P 2850 1400
F 0 "D2" H 3194 1446 50  0000 L CNN
F 1 "WS2812S" H 3194 1355 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812_PLCC6_5.0x5.0mm_P1.6mm" H 2900 1100 50  0001 L TNN
F 3 "http://www.world-semi.com/DownLoadFile/115" H 2950 1025 50  0001 L TNN
	1    2850 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R26
U 1 1 624C7744
P 2750 950
F 0 "R26" H 2820 996 50  0000 L CNN
F 1 "100R0" V 2650 850 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2680 950 50  0001 C CNN
F 3 "~" H 2750 950 50  0001 C CNN
	1    2750 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 5150 3900 5150
Connection ~ 2850 5150
Wire Wire Line
	2850 4900 2850 5150
Wire Wire Line
	6300 2350 6300 2450
Wire Wire Line
	5500 2350 6300 2350
Text Notes 2200 7550 0    50   ~ 0
GPIO2 must also be either left unconnected/floating
$Comp
L Kona_Parts:EVQ-WKA001 SW?
U 1 1 6250D80E
P 3550 6200
AR Path="/624D43FC/6250D80E" Ref="SW?"  Part="1" 
AR Path="/624DFB62/6250D80E" Ref="SW3"  Part="1" 
F 0 "SW3" H 3828 5801 50  0000 L CNN
F 1 "EVQ-WKA001" H 3828 5710 50  0000 L CNN
F 2 "Kona1:EVQ-WKA001" H 3550 6200 50  0001 C CNN
F 3 "" H 3550 6200 50  0001 C CNN
	1    3550 6200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6250D814
P 2900 6200
AR Path="/624D43FC/6250D814" Ref="R?"  Part="1" 
AR Path="/624DFB62/6250D814" Ref="R57"  Part="1" 
F 0 "R57" V 2950 6450 50  0000 R CNN
F 1 "10K0" V 2850 6050 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2830 6200 50  0001 C CNN
F 3 "~" H 2900 6200 50  0001 C CNN
	1    2900 6200
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 6250D81A
P 2750 6200
AR Path="/624D43FC/6250D81A" Ref="R?"  Part="1" 
AR Path="/624DFB62/6250D81A" Ref="R56"  Part="1" 
F 0 "R56" V 2800 6450 50  0000 R CNN
F 1 "10K0" V 2800 6050 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2680 6200 50  0001 C CNN
F 3 "~" H 2750 6200 50  0001 C CNN
	1    2750 6200
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 6250D820
P 2600 6200
AR Path="/624D43FC/6250D820" Ref="R?"  Part="1" 
AR Path="/624DFB62/6250D820" Ref="R55"  Part="1" 
F 0 "R55" V 2650 6450 50  0000 R CNN
F 1 "10K0" V 2650 6050 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2530 6200 50  0001 C CNN
F 3 "~" H 2600 6200 50  0001 C CNN
	1    2600 6200
	-1   0    0    1   
$EndComp
Wire Wire Line
	3350 6400 2900 6400
Wire Wire Line
	2900 6400 2900 6350
Wire Wire Line
	3350 6700 2750 6700
Wire Wire Line
	3350 6900 2600 6900
Wire Wire Line
	2600 6900 2600 6500
$Comp
L power:GND #PWR?
U 1 1 6250D82B
P 3100 7000
AR Path="/624D43FC/6250D82B" Ref="#PWR?"  Part="1" 
AR Path="/624DFB62/6250D82B" Ref="#PWR0166"  Part="1" 
F 0 "#PWR0166" H 3100 6750 50  0001 C CNN
F 1 "GND" H 3105 6827 50  0000 C CNN
F 2 "" H 3100 7000 50  0001 C CNN
F 3 "" H 3100 7000 50  0001 C CNN
	1    3100 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 6500 3100 6500
Wire Wire Line
	3100 6500 3100 6600
Wire Wire Line
	3350 6600 3100 6600
Connection ~ 3100 6600
Wire Wire Line
	3100 6600 3100 6800
Connection ~ 3100 6800
Wire Wire Line
	3100 6800 3100 7000
Wire Wire Line
	3100 6800 3350 6800
$Comp
L power:+3V3 #PWR?
U 1 1 6250D839
P 2750 5950
AR Path="/624D43FC/6250D839" Ref="#PWR?"  Part="1" 
AR Path="/624DFB62/6250D839" Ref="#PWR0167"  Part="1" 
F 0 "#PWR0167" H 2750 5800 50  0001 C CNN
F 1 "+3V3" H 2765 6123 50  0000 C CNN
F 2 "" H 2750 5950 50  0001 C CNN
F 3 "" H 2750 5950 50  0001 C CNN
	1    2750 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 5950 2600 5950
Wire Wire Line
	2600 5950 2600 6050
Wire Wire Line
	2900 6050 2900 5950
Wire Wire Line
	2900 5950 2750 5950
Connection ~ 2750 5950
Wire Wire Line
	2750 6050 2750 5950
$Comp
L Device:C C?
U 1 1 6250D845
P 2050 7050
AR Path="/624D43FC/6250D845" Ref="C?"  Part="1" 
AR Path="/624DFB62/6250D845" Ref="C22"  Part="1" 
F 0 "C22" V 2302 7050 50  0000 C CNN
F 1 "C" V 2211 7050 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 2088 6900 50  0001 C CNN
F 3 "~" H 2050 7050 50  0001 C CNN
	1    2050 7050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6250D84B
P 1750 7050
AR Path="/624D43FC/6250D84B" Ref="C?"  Part="1" 
AR Path="/624DFB62/6250D84B" Ref="C21"  Part="1" 
F 0 "C21" V 2002 7050 50  0000 C CNN
F 1 "C" V 1911 7050 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1788 6900 50  0001 C CNN
F 3 "~" H 1750 7050 50  0001 C CNN
	1    1750 7050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6250D851
P 1450 7050
AR Path="/624D43FC/6250D851" Ref="C?"  Part="1" 
AR Path="/624DFB62/6250D851" Ref="C20"  Part="1" 
F 0 "C20" V 1702 7050 50  0000 C CNN
F 1 "C" V 1611 7050 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1488 6900 50  0001 C CNN
F 3 "~" H 1450 7050 50  0001 C CNN
	1    1450 7050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 6900 1450 6500
Wire Wire Line
	1450 6500 2600 6500
Connection ~ 2600 6500
Wire Wire Line
	2600 6500 2600 6350
Wire Wire Line
	1750 6900 1750 6700
Wire Wire Line
	2050 6600 2900 6600
Wire Wire Line
	2900 6600 2900 6400
Connection ~ 2900 6400
Wire Wire Line
	2050 6600 2050 6900
Text GLabel 1250 6600 0    50   Input ~ 0
ROT_A
Text GLabel 1250 6500 0    50   Input ~ 0
ROT_B
Text GLabel 1250 6700 0    50   Input ~ 0
ROT_SEL
Wire Wire Line
	1250 6500 1450 6500
Connection ~ 1450 6500
Wire Wire Line
	1250 6600 2050 6600
Connection ~ 2050 6600
Wire Wire Line
	1250 6700 1750 6700
Wire Wire Line
	2750 6350 2750 6700
Wire Wire Line
	1750 6700 2750 6700
Connection ~ 1750 6700
Connection ~ 2750 6700
$Comp
L power:GND #PWR0171
U 1 1 62524BCB
P 1750 7450
F 0 "#PWR0171" H 1750 7200 50  0001 C CNN
F 1 "GND" H 1755 7277 50  0000 C CNN
F 2 "" H 1750 7450 50  0001 C CNN
F 3 "" H 1750 7450 50  0001 C CNN
	1    1750 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 7200 1450 7300
Wire Wire Line
	1450 7300 1750 7300
Wire Wire Line
	2050 7300 2050 7200
Wire Wire Line
	1750 7200 1750 7300
Connection ~ 1750 7300
Wire Wire Line
	1750 7300 2050 7300
Wire Wire Line
	1750 7300 1750 7450
Text GLabel 3800 4850 0    50   Input ~ 0
ROT_A
Text GLabel 3800 4750 0    50   Input ~ 0
ROT_B
Text GLabel 3800 4950 0    50   Input ~ 0
ROT_SEL
Wire Wire Line
	2550 5250 3150 5250
Wire Wire Line
	3150 4900 3150 5250
Connection ~ 3150 5250
Wire Wire Line
	3150 5250 3900 5250
Wire Wire Line
	3900 4750 3800 4750
Wire Wire Line
	3900 4850 3800 4850
Wire Wire Line
	3900 4950 3800 4950
Text GLabel 6800 4200 2    50   Input ~ 0
MISO
Wire Wire Line
	6800 4200 6700 4200
Wire Wire Line
	6700 4200 6700 4350
Connection ~ 6700 4350
Wire Wire Line
	6700 4350 7050 4350
Text GLabel 6350 4650 0    50   Input ~ 0
MOSI
Wire Wire Line
	6350 4650 6700 4650
Wire Wire Line
	6700 4650 6700 4450
Connection ~ 6700 4450
Wire Wire Line
	6700 4450 6950 4450
Text GLabel 3800 3950 0    50   Input ~ 0
ENC1_HOME_OUT
Text GLabel 3800 4050 0    50   Input ~ 0
ENC1_INDEX_OUT
Text GLabel 3800 5050 0    50   Input ~ 0
GALIL_RSTn
Connection ~ 9250 3000
Wire Wire Line
	9250 3000 9050 3000
Wire Wire Line
	10100 3000 10550 3000
Connection ~ 10100 3000
Text GLabel 10550 3000 2    50   Input ~ 0
GALIL_CLK_HV
Text GLabel 9050 3000 0    50   Input ~ 0
GALIL_CLK
Connection ~ 9250 2650
Wire Wire Line
	9700 2650 9250 2650
Wire Wire Line
	9700 2700 9700 2650
Wire Wire Line
	9250 2650 9250 2600
$Comp
L power:+3V3 #PWR?
U 1 1 63089064
P 9250 2600
AR Path="/624D4519/63089064" Ref="#PWR?"  Part="1" 
AR Path="/624DFB62/63089064" Ref="#PWR0184"  Part="1" 
F 0 "#PWR0184" H 9250 2450 50  0001 C CNN
F 1 "+3V3" H 9265 2773 50  0000 C CNN
F 2 "" H 9250 2600 50  0001 C CNN
F 3 "" H 9250 2600 50  0001 C CNN
	1    9250 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 3000 10100 2950
Wire Wire Line
	9900 3000 10100 3000
Wire Wire Line
	9250 3000 9250 2950
Wire Wire Line
	9500 3000 9250 3000
$Comp
L Device:R R?
U 1 1 63089054
P 10100 2800
AR Path="/624D4519/63089054" Ref="R?"  Part="1" 
AR Path="/624DFB62/63089054" Ref="R64"  Part="1" 
F 0 "R64" H 10170 2846 50  0000 L CNN
F 1 "R" H 10170 2755 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 10030 2800 50  0001 C CNN
F 3 "~" H 10100 2800 50  0001 C CNN
	1    10100 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6308904E
P 9250 2800
AR Path="/624D4519/6308904E" Ref="R?"  Part="1" 
AR Path="/624DFB62/6308904E" Ref="R60"  Part="1" 
F 0 "R60" H 9320 2846 50  0000 L CNN
F 1 "R" H 9320 2755 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9180 2800 50  0001 C CNN
F 3 "~" H 9250 2800 50  0001 C CNN
	1    9250 2800
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 63089048
P 9700 2900
AR Path="/624D4519/63089048" Ref="Q?"  Part="1" 
AR Path="/624DFB62/63089048" Ref="Q22"  Part="1" 
F 0 "Q22" V 9949 2900 50  0000 C CNN
F 1 "BSS138" V 10040 2900 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9900 2825 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 9700 2900 50  0001 L CNN
	1    9700 2900
	0    1    1    0   
$EndComp
Connection ~ 9250 2200
Wire Wire Line
	9250 2200 9050 2200
Wire Wire Line
	10100 2200 10550 2200
Connection ~ 10100 2200
Text GLabel 10550 2200 2    50   Input ~ 0
GALIL_INC_HV
Text GLabel 9050 2200 0    50   Input ~ 0
GALIL_INC
Connection ~ 9250 1850
Wire Wire Line
	9700 1850 9250 1850
Wire Wire Line
	9700 1900 9700 1850
Wire Wire Line
	9250 1850 9250 1800
$Comp
L power:+3V3 #PWR?
U 1 1 63089038
P 9250 1800
AR Path="/624D4519/63089038" Ref="#PWR?"  Part="1" 
AR Path="/624DFB62/63089038" Ref="#PWR0186"  Part="1" 
F 0 "#PWR0186" H 9250 1650 50  0001 C CNN
F 1 "+3V3" H 9265 1973 50  0000 C CNN
F 2 "" H 9250 1800 50  0001 C CNN
F 3 "" H 9250 1800 50  0001 C CNN
	1    9250 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 2200 10100 2150
Wire Wire Line
	9900 2200 10100 2200
Wire Wire Line
	9250 2200 9250 2150
Wire Wire Line
	9500 2200 9250 2200
$Comp
L Device:R R?
U 1 1 63089028
P 10100 2000
AR Path="/624D4519/63089028" Ref="R?"  Part="1" 
AR Path="/624DFB62/63089028" Ref="R63"  Part="1" 
F 0 "R63" H 10170 2046 50  0000 L CNN
F 1 "R" H 10170 1955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 10030 2000 50  0001 C CNN
F 3 "~" H 10100 2000 50  0001 C CNN
	1    10100 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 63089022
P 9250 2000
AR Path="/624D4519/63089022" Ref="R?"  Part="1" 
AR Path="/624DFB62/63089022" Ref="R59"  Part="1" 
F 0 "R59" H 9320 2046 50  0000 L CNN
F 1 "R" H 9320 1955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9180 2000 50  0001 C CNN
F 3 "~" H 9250 2000 50  0001 C CNN
	1    9250 2000
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 6308901C
P 9700 2100
AR Path="/624D4519/6308901C" Ref="Q?"  Part="1" 
AR Path="/624DFB62/6308901C" Ref="Q21"  Part="1" 
F 0 "Q21" V 9949 2100 50  0000 C CNN
F 1 "BSS138" V 10040 2100 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9900 2025 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 9700 2100 50  0001 L CNN
	1    9700 2100
	0    1    1    0   
$EndComp
Connection ~ 9250 1450
Wire Wire Line
	9250 1450 9050 1450
Wire Wire Line
	10100 1450 10550 1450
Connection ~ 10100 1450
Text GLabel 10550 1450 2    50   Input ~ 0
GALIL_DEC_HV
Text GLabel 9050 1450 0    50   Input ~ 0
GALIL_DEC
Connection ~ 9250 1100
Wire Wire Line
	9700 1100 9250 1100
Wire Wire Line
	9700 1150 9700 1100
Wire Wire Line
	9250 1100 9250 1050
$Comp
L power:+3V3 #PWR?
U 1 1 6308900C
P 9250 1050
AR Path="/624D4519/6308900C" Ref="#PWR?"  Part="1" 
AR Path="/624DFB62/6308900C" Ref="#PWR0188"  Part="1" 
F 0 "#PWR0188" H 9250 900 50  0001 C CNN
F 1 "+3V3" H 9265 1223 50  0000 C CNN
F 2 "" H 9250 1050 50  0001 C CNN
F 3 "" H 9250 1050 50  0001 C CNN
	1    9250 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 1450 10100 1400
Wire Wire Line
	9900 1450 10100 1450
Wire Wire Line
	9250 1450 9250 1400
Wire Wire Line
	9500 1450 9250 1450
$Comp
L Device:R R?
U 1 1 63088FFC
P 10100 1250
AR Path="/624D4519/63088FFC" Ref="R?"  Part="1" 
AR Path="/624DFB62/63088FFC" Ref="R62"  Part="1" 
F 0 "R62" H 10170 1296 50  0000 L CNN
F 1 "R" H 10170 1205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 10030 1250 50  0001 C CNN
F 3 "~" H 10100 1250 50  0001 C CNN
	1    10100 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 63088FF6
P 9250 1250
AR Path="/624D4519/63088FF6" Ref="R?"  Part="1" 
AR Path="/624DFB62/63088FF6" Ref="R58"  Part="1" 
F 0 "R58" H 9320 1296 50  0000 L CNN
F 1 "R" H 9320 1205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9180 1250 50  0001 C CNN
F 3 "~" H 9250 1250 50  0001 C CNN
	1    9250 1250
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 63088FF0
P 9700 1350
AR Path="/624D4519/63088FF0" Ref="Q?"  Part="1" 
AR Path="/624DFB62/63088FF0" Ref="Q20"  Part="1" 
F 0 "Q20" V 9949 1350 50  0000 C CNN
F 1 "BSS138" V 10040 1350 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9900 1275 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 9700 1350 50  0001 L CNN
	1    9700 1350
	0    1    1    0   
$EndComp
Text GLabel 3900 3150 0    50   Input ~ 0
GALIL_CLK
Text GLabel 3800 5450 0    50   Input ~ 0
GALIL_DEC
Text GLabel 3800 5550 0    50   Input ~ 0
GALIL_INC
Wire Wire Line
	3900 5450 3800 5450
Wire Wire Line
	3900 5550 3800 5550
Wire Wire Line
	3800 5050 3900 5050
Connection ~ 9250 3750
Wire Wire Line
	9250 3750 9050 3750
Wire Wire Line
	10100 3750 10550 3750
Connection ~ 10100 3750
Text GLabel 10550 3750 2    50   Input ~ 0
GALIL_RSTn_HV
Text GLabel 9050 3750 0    50   Input ~ 0
GALIL_RSTn
Connection ~ 9250 3400
Wire Wire Line
	9700 3400 9250 3400
Wire Wire Line
	9700 3450 9700 3400
Wire Wire Line
	9250 3400 9250 3350
$Comp
L power:+3V3 #PWR?
U 1 1 6319133D
P 9250 3350
AR Path="/624D4519/6319133D" Ref="#PWR?"  Part="1" 
AR Path="/624DFB62/6319133D" Ref="#PWR0190"  Part="1" 
F 0 "#PWR0190" H 9250 3200 50  0001 C CNN
F 1 "+3V3" H 9265 3523 50  0000 C CNN
F 2 "" H 9250 3350 50  0001 C CNN
F 3 "" H 9250 3350 50  0001 C CNN
	1    9250 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 3750 10100 3700
Wire Wire Line
	9900 3750 10100 3750
Wire Wire Line
	9250 3750 9250 3700
Wire Wire Line
	9500 3750 9250 3750
$Comp
L Device:R R?
U 1 1 6319134D
P 10100 3550
AR Path="/624D4519/6319134D" Ref="R?"  Part="1" 
AR Path="/624DFB62/6319134D" Ref="R65"  Part="1" 
F 0 "R65" H 10170 3596 50  0000 L CNN
F 1 "R" H 10170 3505 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 10030 3550 50  0001 C CNN
F 3 "~" H 10100 3550 50  0001 C CNN
	1    10100 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 63191353
P 9250 3550
AR Path="/624D4519/63191353" Ref="R?"  Part="1" 
AR Path="/624DFB62/63191353" Ref="R61"  Part="1" 
F 0 "R61" H 9320 3596 50  0000 L CNN
F 1 "R" H 9320 3505 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9180 3550 50  0001 C CNN
F 3 "~" H 9250 3550 50  0001 C CNN
	1    9250 3550
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 63191359
P 9700 3650
AR Path="/624D4519/63191359" Ref="Q?"  Part="1" 
AR Path="/624DFB62/63191359" Ref="Q23"  Part="1" 
F 0 "Q23" V 9949 3650 50  0000 C CNN
F 1 "BSS138" V 10040 3650 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9900 3575 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 9700 3650 50  0001 L CNN
	1    9700 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	5950 2050 5950 2150
$Comp
L Device:R R11
U 1 1 631C2F27
P 5750 2150
F 0 "R11" H 5820 2196 50  0000 L CNN
F 1 "DNP" V 5650 2050 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5680 2150 50  0001 C CNN
F 3 "~" H 5750 2150 50  0001 C CNN
	1    5750 2150
	0    1    1    0   
$EndComp
Wire Wire Line
	5600 2150 5500 2150
Wire Wire Line
	5900 2150 5950 2150
Wire Wire Line
	5600 1500 5600 1650
Wire Wire Line
	3900 2550 3650 2550
Wire Wire Line
	3650 2550 3650 1650
Wire Wire Line
	3650 1650 5600 1650
Connection ~ 5600 1650
Wire Wire Line
	5600 1650 5600 2050
Text GLabel 3200 4350 0    50   UnSpc ~ 0
PWM_MC
Wire Wire Line
	3200 4350 3900 4350
$Comp
L Device:R R68
U 1 1 6255BEDC
P 2050 3050
F 0 "R68" V 1950 2950 50  0000 L CNN
F 1 "10K0" V 2150 2950 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1980 3050 50  0001 C CNN
F 3 "~" H 2050 3050 50  0001 C CNN
	1    2050 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 3950 3800 3950
Wire Wire Line
	3900 4050 3800 4050
Wire Wire Line
	6500 4150 6500 4050
Wire Wire Line
	6500 4050 7700 4050
Wire Wire Line
	7700 4050 7700 4250
Wire Wire Line
	5500 4150 6500 4150
Connection ~ 7700 4250
Wire Wire Line
	7700 4250 7600 4250
$Comp
L power:+3V3 #PWR0197
U 1 1 625A982D
P 3250 2800
F 0 "#PWR0197" H 3250 2650 50  0001 C CNN
F 1 "+3V3" H 3265 2973 50  0000 C CNN
F 2 "" H 3250 2800 50  0001 C CNN
F 3 "" H 3250 2800 50  0001 C CNN
	1    3250 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R69
U 1 1 625CEA4C
P 3250 3200
F 0 "R69" V 3350 3150 50  0000 L CNN
F 1 "10K0" V 3150 3100 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 3180 3200 50  0001 C CNN
F 3 "~" H 3250 3200 50  0001 C CNN
	1    3250 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3350 3250 3450
Connection ~ 3250 3450
Wire Wire Line
	3250 3450 3900 3450
Text Notes 5650 1550 0    50   ~ 0
+5VP  should +5V
$Comp
L power:+5V #PWR0192
U 1 1 62B24DE9
P 10100 1100
F 0 "#PWR0192" H 10100 950 50  0001 C CNN
F 1 "+5V" H 10115 1273 50  0000 C CNN
F 2 "" H 10100 1100 50  0001 C CNN
F 3 "" H 10100 1100 50  0001 C CNN
	1    10100 1100
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0194
U 1 1 62B254D2
P 10100 1850
F 0 "#PWR0194" H 10100 1700 50  0001 C CNN
F 1 "+5V" H 10115 2023 50  0000 C CNN
F 2 "" H 10100 1850 50  0001 C CNN
F 3 "" H 10100 1850 50  0001 C CNN
	1    10100 1850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0198
U 1 1 62B2591D
P 10100 2650
F 0 "#PWR0198" H 10100 2500 50  0001 C CNN
F 1 "+5V" H 10115 2823 50  0000 C CNN
F 2 "" H 10100 2650 50  0001 C CNN
F 3 "" H 10100 2650 50  0001 C CNN
	1    10100 2650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0199
U 1 1 62B25E6D
P 10100 3400
F 0 "#PWR0199" H 10100 3250 50  0001 C CNN
F 1 "+5V" H 10115 3573 50  0000 C CNN
F 2 "" H 10100 3400 50  0001 C CNN
F 3 "" H 10100 3400 50  0001 C CNN
	1    10100 3400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0200
U 1 1 62B2675B
P 5600 1500
F 0 "#PWR0200" H 5600 1350 50  0001 C CNN
F 1 "+5V" H 5615 1673 50  0000 C CNN
F 2 "" H 5600 1500 50  0001 C CNN
F 3 "" H 5600 1500 50  0001 C CNN
	1    5600 1500
	1    0    0    -1  
$EndComp
Text GLabel 6450 7850 2    50   UnSpc ~ 0
ENC2_A
Text GLabel 5750 5550 2    50   UnSpc ~ 0
ENC2_A_L
Text GLabel 6050 4950 2    50   UnSpc ~ 0
ENC2_INDEX_L
Text GLabel 5750 5350 2    50   UnSpc ~ 0
ENC2_HOME_L
Text GLabel 5750 5450 2    50   UnSpc ~ 0
ENC2_B_L
Wire Wire Line
	5500 5550 5750 5550
Wire Wire Line
	5500 5450 5750 5450
Wire Wire Line
	5500 5350 5750 5350
$Comp
L Transistor_BJT:MMBT3904 Q24
U 1 1 627EE647
P 1200 2450
F 0 "Q24" H 1391 2496 50  0000 L CNN
F 1 "MMBT3904" H 1391 2405 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 1400 2375 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/2N3903-D.PDF" H 1200 2450 50  0001 L CNN
	1    1200 2450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1400 2450 1500 2450
$Comp
L power:GND #PWR0201
U 1 1 627EE650
P 1100 2950
F 0 "#PWR0201" H 1100 2700 50  0001 C CNN
F 1 "GND" H 1105 2777 50  0000 C CNN
F 2 "" H 1100 2950 50  0001 C CNN
F 3 "" H 1100 2950 50  0001 C CNN
	1    1100 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R72
U 1 1 627EE656
P 1400 2700
F 0 "R72" V 1450 2800 50  0000 L CNN
F 1 "10K0" V 1500 2600 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1330 2700 50  0001 C CNN
F 3 "~" H 1400 2700 50  0001 C CNN
	1    1400 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R73
U 1 1 627EE65C
P 1650 2450
F 0 "R73" V 1700 2550 50  0000 L CNN
F 1 "1K0" V 1750 2350 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1580 2450 50  0001 C CNN
F 3 "~" H 1650 2450 50  0001 C CNN
	1    1650 2450
	0    1    1    0   
$EndComp
Wire Wire Line
	1100 2650 1100 2900
Wire Wire Line
	1400 2850 1400 2900
Wire Wire Line
	1400 2900 1100 2900
Connection ~ 1100 2900
Wire Wire Line
	1100 2900 1100 2950
Wire Wire Line
	1400 2550 1400 2450
Connection ~ 1400 2450
$Comp
L Connector:TestPoint GND2
U 1 1 627EE669
P 750 2900
F 0 "GND2" H 808 3018 50  0000 L CNN
F 1 "TestPoint" H 808 2927 50  0000 L CNN
F 2 "TestPoint:TestPoint_Keystone_5019_Minature" H 950 2900 50  0001 C CNN
F 3 "~" H 950 2900 50  0001 C CNN
	1    750  2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	750  2900 1100 2900
Wire Wire Line
	3000 2950 3900 2950
Wire Wire Line
	2300 3650 2300 2450
Wire Wire Line
	2300 2450 1800 2450
Wire Wire Line
	2300 3650 3900 3650
Text GLabel 1400 1900 2    50   Input ~ 0
CypressRST_MOT0
Wire Wire Line
	1400 1900 1100 1900
Wire Wire Line
	1100 1900 1100 2250
Text GLabel 5000 6800 2    50   UnSpc ~ 0
ENC1_A_L
Text GLabel 5750 4750 2    50   UnSpc ~ 0
ENC1_INDEX_L
Text GLabel 5750 4850 2    50   UnSpc ~ 0
ENC1_HOME_L
Text GLabel 5000 6700 2    50   UnSpc ~ 0
ENC1_B_L
Wire Wire Line
	5750 4750 5500 4750
Wire Wire Line
	5750 4850 5500 4850
Text GLabel 3800 4250 0    50   UnSpc ~ 0
PWM_DISABLE_MOT0
Wire Wire Line
	3900 4250 3800 4250
Text GLabel 3400 5350 0    50   Input ~ 0
GALIL_ERR_FLG
Wire Wire Line
	3400 5350 3900 5350
$Comp
L power:+5V #PWR0193
U 1 1 628C6FA9
P 2750 800
F 0 "#PWR0193" H 2750 650 50  0001 C CNN
F 1 "+5V" H 2765 973 50  0000 C CNN
F 2 "" H 2750 800 50  0001 C CNN
F 3 "" H 2750 800 50  0001 C CNN
	1    2750 800 
	1    0    0    -1  
$EndComp
Text GLabel 5000 6900 2    50   UnSpc ~ 0
DIRECTION
Text GLabel 3800 3850 0    50   Input ~ 0
PROBE
Text GLabel 3900 3350 0    50   Input ~ 0
LED
Text GLabel 3750 3250 0    50   Input ~ 0
MISO1
Text GLabel 6050 5250 2    50   Input ~ 0
MOSI1
Text GLabel 6050 5150 2    50   Input ~ 0
SCK1
Text GLabel 1700 3300 0    50   UnSpc ~ 0
CYP_CSn
Wire Wire Line
	5500 4950 6050 4950
Wire Wire Line
	5500 5150 6050 5150
Wire Wire Line
	3900 3850 3800 3850
Wire Wire Line
	3250 2800 3250 3050
$Comp
L power:+3V3 #PWR0196
U 1 1 62D58E91
P 2050 2850
F 0 "#PWR0196" H 2050 2700 50  0001 C CNN
F 1 "+3V3" H 2065 3023 50  0000 C CNN
F 2 "" H 2050 2850 50  0001 C CNN
F 3 "" H 2050 2850 50  0001 C CNN
	1    2050 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 2900 2050 2850
Wire Wire Line
	3900 3250 3750 3250
Wire Wire Line
	2050 3550 2050 3400
Wire Wire Line
	2050 3550 3900 3550
Wire Wire Line
	1700 3300 2050 3300
Connection ~ 2050 3300
Wire Wire Line
	2050 3300 2050 3200
Wire Wire Line
	1700 3400 2050 3400
Connection ~ 2050 3400
Wire Wire Line
	2050 3400 2050 3300
Wire Wire Line
	6050 5250 5500 5250
$EndSCHEMATC

EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 6
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
L Connector:Micro_SD_Card J2
U 1 1 60882352
P 10100 4300
F 0 "J2" H 9350 4900 50  0000 C CNN
F 1 "Micro_SD_Card" H 10450 4950 50  0000 C CNN
F 2 "Connector_Card:microSD_HC_Molex_104031-0811" H 11250 4600 50  0001 C CNN
F 3 "http://katalog.we-online.de/em/datasheet/693072010801.pdf" H 10100 4300 50  0001 C CNN
	1    10100 4300
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_B_Micro J1
U 1 1 608876E0
P 1150 5150
F 0 "J1" H 1207 5617 50  0000 C CNN
F 1 "USB_B_Micro" H 1207 5526 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Amphenol_10103594-0001LF_Horizontal" H 1300 5100 50  0001 C CNN
F 3 "~" H 1300 5100 50  0001 C CNN
	1    1150 5150
	1    0    0    -1  
$EndComp
$Comp
L WBSonar-rescue:2N2222A-Kona_Parts Q1
U 1 1 60888470
P 5250 5950
AR Path="/60888470" Ref="Q1"  Part="1" 
AR Path="/6087CF34/60888470" Ref="Q1"  Part="1" 
AR Path="/624D43FC/60888470" Ref="Q1"  Part="1" 
F 0 "Q1" H 5408 5996 50  0000 L CNN
F 1 "2N2222A" H 5408 5905 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5250 5950 50  0001 C CNN
F 3 "" H 5250 5950 50  0001 C CNN
	1    5250 5950
	1    0    0    -1  
$EndComp
$Comp
L WBSonar-rescue:2N2222A-Kona_Parts Q2
U 1 1 60888AB5
P 5250 6800
AR Path="/60888AB5" Ref="Q2"  Part="1" 
AR Path="/6087CF34/60888AB5" Ref="Q2"  Part="1" 
AR Path="/624D43FC/60888AB5" Ref="Q2"  Part="1" 
F 0 "Q2" H 5408 6754 50  0000 L CNN
F 1 "2N2222A" H 5408 6845 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5250 6800 50  0001 C CNN
F 3 "" H 5250 6800 50  0001 C CNN
	1    5250 6800
	1    0    0    1   
$EndComp
Wire Wire Line
	9200 4300 9100 4300
Wire Wire Line
	9200 4500 9100 4500
$Comp
L power:GND #PWR050
U 1 1 6088D6D9
P 9100 5200
F 0 "#PWR050" H 9100 4950 50  0001 C CNN
F 1 "GND" H 9105 5027 50  0000 C CNN
F 2 "" H 9100 5200 50  0001 C CNN
F 3 "" H 9100 5200 50  0001 C CNN
	1    9100 5200
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR049
U 1 1 6088DB2D
P 9100 3450
F 0 "#PWR049" H 9100 3300 50  0001 C CNN
F 1 "+3V3" H 9115 3623 50  0000 C CNN
F 2 "" H 9100 3450 50  0001 C CNN
F 3 "" H 9100 3450 50  0001 C CNN
	1    9100 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 3450 9100 4300
Wire Wire Line
	9100 4500 9100 5200
$Comp
L Device:R R24
U 1 1 6088F244
P 4750 5950
F 0 "R24" V 4650 5900 50  0000 C CNN
F 1 "12K0" V 4750 5950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4680 5950 50  0001 C CNN
F 3 "~" H 4750 5950 50  0001 C CNN
	1    4750 5950
	0    1    1    0   
$EndComp
$Comp
L Device:R R25
U 1 1 6088FA39
P 4800 6800
F 0 "R25" V 4700 6750 50  0000 C CNN
F 1 "12K0" V 4800 6800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4730 6800 50  0001 C CNN
F 3 "~" H 4800 6800 50  0001 C CNN
	1    4800 6800
	0    1    1    0   
$EndComp
Wire Wire Line
	5100 5950 4900 5950
Wire Wire Line
	4950 6800 5100 6800
Wire Wire Line
	5350 6250 5350 6300
Wire Wire Line
	5350 6300 4450 6300
Wire Wire Line
	4450 6300 4450 6800
Wire Wire Line
	4450 6800 4650 6800
Wire Wire Line
	5350 6500 5350 6450
Wire Wire Line
	5350 6450 4550 6450
Wire Wire Line
	4550 5950 4600 5950
Wire Wire Line
	5350 5650 5350 5550
Wire Wire Line
	5350 7100 5350 7200
Text GLabel 4150 6800 0    50   Input ~ 0
RTS
Text GLabel 4150 5950 0    50   Input ~ 0
DTR
Text GLabel 4950 5550 0    50   Input ~ 0
EN
Text GLabel 5750 7200 2    50   Input ~ 0
GPIO_0
Wire Wire Line
	5350 7200 5750 7200
Wire Wire Line
	4150 5950 4550 5950
Connection ~ 4550 5950
Wire Wire Line
	4150 6800 4450 6800
Connection ~ 4450 6800
Wire Wire Line
	3350 4900 3850 4900
Wire Wire Line
	3850 4900 3850 6300
Wire Wire Line
	3350 5300 3750 5300
Wire Wire Line
	3750 5300 3750 6200
$Comp
L Device:R R14
U 1 1 6089FDE8
P 1750 5150
F 0 "R14" V 1650 5100 50  0000 C CNN
F 1 "22R0" V 1750 5150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1680 5150 50  0001 C CNN
F 3 "~" H 1750 5150 50  0001 C CNN
	1    1750 5150
	0    1    1    0   
$EndComp
$Comp
L Device:R R15
U 1 1 608A0494
P 1750 5250
F 0 "R15" V 1850 5200 50  0000 C CNN
F 1 "22R0" V 1750 5250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1680 5250 50  0001 C CNN
F 3 "~" H 1750 5250 50  0001 C CNN
	1    1750 5250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR039
U 1 1 608A0687
P 2850 7450
F 0 "#PWR039" H 2850 7200 50  0001 C CNN
F 1 "GND" H 2855 7277 50  0000 C CNN
F 2 "" H 2850 7450 50  0001 C CNN
F 3 "" H 2850 7450 50  0001 C CNN
	1    2850 7450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR034
U 1 1 608A0FA5
P 1150 5750
F 0 "#PWR034" H 1150 5500 50  0001 C CNN
F 1 "GND" H 1155 5577 50  0000 C CNN
F 2 "" H 1150 5750 50  0001 C CNN
F 3 "" H 1150 5750 50  0001 C CNN
	1    1150 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 5550 1150 5650
Wire Wire Line
	1050 5550 1050 5650
Wire Wire Line
	1050 5650 1150 5650
Connection ~ 1150 5650
Wire Wire Line
	1150 5650 1150 5750
Wire Wire Line
	1900 5150 2050 5150
Wire Wire Line
	2050 5150 2050 5300
Wire Wire Line
	2050 5300 2350 5300
Wire Wire Line
	1900 5250 2000 5250
Wire Wire Line
	2000 5250 2000 5400
Wire Wire Line
	2000 5400 2350 5400
Wire Wire Line
	1600 5150 1500 5150
Wire Wire Line
	1600 5250 1550 5250
$Comp
L power:+3V3 #PWR037
U 1 1 608A892D
P 2800 750
F 0 "#PWR037" H 2800 600 50  0001 C CNN
F 1 "+3V3" H 2815 923 50  0000 C CNN
F 2 "" H 2800 750 50  0001 C CNN
F 3 "" H 2800 750 50  0001 C CNN
	1    2800 750 
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR045
U 1 1 608B03A4
P 5850 1000
F 0 "#PWR045" H 5850 850 50  0001 C CNN
F 1 "+3V3" H 5865 1173 50  0000 C CNN
F 2 "" H 5850 1000 50  0001 C CNN
F 3 "" H 5850 1000 50  0001 C CNN
	1    5850 1000
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR051
U 1 1 608B4726
P 9100 5750
F 0 "#PWR051" H 9100 5600 50  0001 C CNN
F 1 "+3V3" H 9115 5923 50  0000 C CNN
F 2 "" H 9100 5750 50  0001 C CNN
F 3 "" H 9100 5750 50  0001 C CNN
	1    9100 5750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR052
U 1 1 608B49EE
P 9100 6200
F 0 "#PWR052" H 9100 5950 50  0001 C CNN
F 1 "GND" H 9105 6027 50  0000 C CNN
F 2 "" H 9100 6200 50  0001 C CNN
F 3 "" H 9100 6200 50  0001 C CNN
	1    9100 6200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C24
U 1 1 608B532F
P 8800 5950
F 0 "C24" H 8915 5996 50  0000 L CNN
F 1 "0U1" H 8915 5905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 8838 5800 50  0001 C CNN
F 3 "~" H 8800 5950 50  0001 C CNN
	1    8800 5950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C25
U 1 1 608B576B
P 9100 5950
F 0 "C25" H 9215 5996 50  0000 L CNN
F 1 "0U1" H 9215 5905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 9138 5800 50  0001 C CNN
F 3 "~" H 9100 5950 50  0001 C CNN
	1    9100 5950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C26
U 1 1 608B5A0D
P 9400 5950
F 0 "C26" H 9515 5996 50  0000 L CNN
F 1 "0U1" H 9515 5905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 9438 5800 50  0001 C CNN
F 3 "~" H 9400 5950 50  0001 C CNN
	1    9400 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 6200 8800 6200
Wire Wire Line
	8800 6200 8800 6100
Wire Wire Line
	9100 6200 9400 6200
Wire Wire Line
	9400 6200 9400 6100
Connection ~ 9100 6200
Wire Wire Line
	9100 6100 9100 6200
Wire Wire Line
	8800 5800 8800 5750
Wire Wire Line
	8800 5750 9100 5750
Wire Wire Line
	9400 5800 9400 5750
Wire Wire Line
	9400 5750 9100 5750
Connection ~ 9100 5750
Wire Wire Line
	9100 5800 9100 5750
Text GLabel 900  1700 0    50   Input ~ 0
EN
Text GLabel 900  3100 0    50   Input ~ 0
GPIO_0
$Comp
L Device:C C28
U 1 1 608D6267
P 9700 5950
F 0 "C28" H 9815 5996 50  0000 L CNN
F 1 "10U0" H 9815 5905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 9738 5800 50  0001 C CNN
F 3 "~" H 9700 5950 50  0001 C CNN
	1    9700 5950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C30
U 1 1 608D63E0
P 10000 5950
F 0 "C30" H 10115 5996 50  0000 L CNN
F 1 "10U0" H 10115 5905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 10038 5800 50  0001 C CNN
F 3 "~" H 10000 5950 50  0001 C CNN
	1    10000 5950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C31
U 1 1 608D65EA
P 10300 5950
F 0 "C31" H 10415 5996 50  0000 L CNN
F 1 "10U0" H 10415 5905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 10338 5800 50  0001 C CNN
F 3 "~" H 10300 5950 50  0001 C CNN
	1    10300 5950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C23
U 1 1 608D6A17
P 8500 5950
F 0 "C23" H 8615 5996 50  0000 L CNN
F 1 "0U1" H 8615 5905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 8538 5800 50  0001 C CNN
F 3 "~" H 8500 5950 50  0001 C CNN
	1    8500 5950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C22
U 1 1 608D6C55
P 8200 5950
F 0 "C22" H 8315 5996 50  0000 L CNN
F 1 "0U1" H 8315 5905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 8238 5800 50  0001 C CNN
F 3 "~" H 8200 5950 50  0001 C CNN
	1    8200 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 5800 8200 5750
Wire Wire Line
	8200 5750 8500 5750
Connection ~ 8800 5750
Wire Wire Line
	8500 5800 8500 5750
Connection ~ 8500 5750
Wire Wire Line
	8500 5750 8800 5750
Wire Wire Line
	8200 6100 8200 6200
Wire Wire Line
	8200 6200 8500 6200
Connection ~ 8800 6200
Wire Wire Line
	8500 6100 8500 6200
Connection ~ 8500 6200
Wire Wire Line
	8500 6200 8800 6200
Wire Wire Line
	9400 5750 9700 5750
Wire Wire Line
	10300 5750 10300 5800
Connection ~ 9400 5750
Wire Wire Line
	10000 5800 10000 5750
Connection ~ 10000 5750
Wire Wire Line
	10000 5750 10300 5750
Wire Wire Line
	9700 5800 9700 5750
Connection ~ 9700 5750
Wire Wire Line
	9700 5750 10000 5750
Wire Wire Line
	10300 6100 10300 6200
Wire Wire Line
	10300 6200 10000 6200
Connection ~ 9400 6200
Wire Wire Line
	9700 6100 9700 6200
Connection ~ 9700 6200
Wire Wire Line
	9700 6200 9400 6200
Wire Wire Line
	10000 6100 10000 6200
Connection ~ 10000 6200
Wire Wire Line
	10000 6200 9700 6200
$Comp
L Device:C C27
U 1 1 609402CD
P 9500 3450
F 0 "C27" V 9752 3450 50  0000 C CNN
F 1 "C" V 9661 3450 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 9538 3300 50  0001 C CNN
F 3 "~" H 9500 3450 50  0001 C CNN
	1    9500 3450
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR053
U 1 1 609402D3
P 9800 3550
F 0 "#PWR053" H 9800 3300 50  0001 C CNN
F 1 "GND" H 9700 3550 50  0000 C CNN
F 2 "" H 9800 3550 50  0001 C CNN
F 3 "" H 9800 3550 50  0001 C CNN
	1    9800 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R18
U 1 1 609586D8
P 2350 4750
F 0 "R18" H 2500 4650 50  0000 R CNN
F 1 "10K0" V 2350 4850 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2280 4750 50  0001 C CNN
F 3 "~" H 2350 4750 50  0001 C CNN
	1    2350 4750
	-1   0    0    1   
$EndComp
Wire Wire Line
	2850 4400 2850 4600
Wire Wire Line
	2850 7450 2850 7200
Wire Wire Line
	2750 4600 2750 4500
Wire Wire Line
	2750 4500 2200 4500
$Comp
L Device:C C17
U 1 1 60974463
P 2200 5950
F 0 "C17" H 2350 5850 50  0000 R CNN
F 1 "4U7" H 2400 6050 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 2238 5800 50  0001 C CNN
F 3 "~" H 2200 5950 50  0001 C CNN
	1    2200 5950
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR036
U 1 1 6097A9A4
P 2200 6200
F 0 "#PWR036" H 2200 5950 50  0001 C CNN
F 1 "GND" H 2205 6027 50  0000 C CNN
F 2 "" H 2200 6200 50  0001 C CNN
F 3 "" H 2200 6200 50  0001 C CNN
	1    2200 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 6200 2200 6150
$Comp
L Device:R R23
U 1 1 60981187
P 4250 5100
F 0 "R23" V 4350 4900 50  0000 C CNN
F 1 "470R0" V 4350 5250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4180 5100 50  0001 C CNN
F 3 "~" H 4250 5100 50  0001 C CNN
	1    4250 5100
	0    1    1    0   
$EndComp
Wire Wire Line
	4100 5100 3350 5100
Text GLabel 4750 5100 2    50   Input ~ 0
TXD
Wire Wire Line
	4750 5100 4400 5100
Text GLabel 4750 5000 2    50   Input ~ 0
RXD
Wire Wire Line
	3350 5000 4750 5000
$Comp
L Device:C C18
U 1 1 60994CA3
P 3250 4400
F 0 "C18" V 3502 4400 50  0000 C CNN
F 1 "4U7" V 3411 4400 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 3288 4250 50  0001 C CNN
F 3 "~" H 3250 4400 50  0001 C CNN
	1    3250 4400
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR040
U 1 1 6099546F
P 3700 4500
F 0 "#PWR040" H 3700 4250 50  0001 C CNN
F 1 "GND" H 3705 4327 50  0000 C CNN
F 2 "" H 3700 4500 50  0001 C CNN
F 3 "" H 3700 4500 50  0001 C CNN
	1    3700 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 4400 2850 4400
Wire Wire Line
	3400 4400 3700 4400
Wire Wire Line
	3700 4400 3700 4500
Connection ~ 2200 4950
Wire Wire Line
	2200 4500 2200 4950
Wire Wire Line
	1450 4950 2200 4950
$Comp
L power:GND #PWR057
U 1 1 609B4653
P 10950 5150
F 0 "#PWR057" H 10950 4900 50  0001 C CNN
F 1 "GND" H 10955 4977 50  0000 C CNN
F 2 "" H 10950 5150 50  0001 C CNN
F 3 "" H 10950 5150 50  0001 C CNN
	1    10950 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	10900 4900 10950 4900
Wire Wire Line
	10950 4900 10950 5150
$Comp
L Diode:BAT54A D3
U 1 1 60AC6906
P 1350 6400
F 0 "D3" H 1350 6625 50  0000 C CNN
F 1 "BAT54A" H 1350 6534 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 1425 6525 50  0001 L CNN
F 3 "http://www.diodes.com/_files/datasheets/ds11005.pdf" H 1230 6400 50  0001 C CNN
	1    1350 6400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR035
U 1 1 60AC9918
P 1350 6700
F 0 "#PWR035" H 1350 6450 50  0001 C CNN
F 1 "GND" H 1355 6527 50  0000 C CNN
F 2 "" H 1350 6700 50  0001 C CNN
F 3 "" H 1350 6700 50  0001 C CNN
	1    1350 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 6600 1350 6700
Wire Wire Line
	1050 6400 1000 6400
Wire Wire Line
	1000 6400 1000 6000
Wire Wire Line
	1000 6000 1500 6000
Wire Wire Line
	1500 6000 1500 5150
Connection ~ 1500 5150
Wire Wire Line
	1500 5150 1450 5150
Wire Wire Line
	1650 6400 1750 6400
Wire Wire Line
	1750 6400 1750 6000
Wire Wire Line
	1750 6000 1550 6000
Wire Wire Line
	1550 6000 1550 5250
Connection ~ 1550 5250
Wire Wire Line
	1550 5250 1450 5250
$Comp
L Device:R R11
U 1 1 60AF0621
P 1100 1400
F 0 "R11" V 1150 1650 50  0000 R CNN
F 1 "12K0" V 1100 1500 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1030 1400 50  0001 C CNN
F 3 "~" H 1100 1400 50  0001 C CNN
	1    1100 1400
	-1   0    0    1   
$EndComp
Connection ~ 1100 1700
Wire Wire Line
	1100 1700 900  1700
Wire Wire Line
	1100 1850 1100 1800
$Comp
L Device:R R12
U 1 1 60B0A0EB
P 1100 2900
F 0 "R12" V 1200 2950 50  0000 R CNN
F 1 "12K0" V 1100 3000 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1030 2900 50  0001 C CNN
F 3 "~" H 1100 2900 50  0001 C CNN
	1    1100 2900
	-1   0    0    1   
$EndComp
$Comp
L power:+3V3 #PWR032
U 1 1 60B0A559
P 1100 2700
F 0 "#PWR032" H 1100 2550 50  0001 C CNN
F 1 "+3V3" H 1115 2873 50  0000 C CNN
F 2 "" H 1100 2700 50  0001 C CNN
F 3 "" H 1100 2700 50  0001 C CNN
	1    1100 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 2750 1100 2700
Wire Wire Line
	1100 3050 1100 3100
Connection ~ 1100 3100
Wire Wire Line
	1100 3100 900  3100
$Comp
L power:+3V3 #PWR030
U 1 1 60B25BC1
P 1100 1000
F 0 "#PWR030" H 1100 850 50  0001 C CNN
F 1 "+3V3" H 1115 1173 50  0000 C CNN
F 2 "" H 1100 1000 50  0001 C CNN
F 3 "" H 1100 1000 50  0001 C CNN
	1    1100 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 1000 1100 1250
Wire Wire Line
	1100 1550 1100 1700
Text Notes 10050 5150 0    50   ~ 0
MICRO SD
Text GLabel 8100 4600 0    50   Input ~ 0
MISO
Text GLabel 8100 4200 0    50   Input ~ 0
MOSI
Text GLabel 8100 4400 0    50   Input ~ 0
SCLK
Text GLabel 8200 4100 0    50   Input ~ 0
SD_CSn
Wire Wire Line
	9200 4100 8350 4100
Wire Wire Line
	9200 4200 8450 4200
Wire Wire Line
	9200 4600 8650 4600
Wire Wire Line
	9650 3450 9800 3450
Wire Wire Line
	9800 3450 9800 3550
$Comp
L Device:R R28
U 1 1 60BD29B8
P 8350 3850
F 0 "R28" V 8400 3700 50  0000 R CNN
F 1 "10K0" V 8350 3950 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 8280 3850 50  0001 C CNN
F 3 "~" H 8350 3850 50  0001 C CNN
	1    8350 3850
	-1   0    0    1   
$EndComp
$Comp
L Device:R R29
U 1 1 60BD2DFC
P 8450 3850
F 0 "R29" V 8500 3700 50  0000 R CNN
F 1 "10K0" V 8450 3950 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 8380 3850 50  0001 C CNN
F 3 "~" H 8450 3850 50  0001 C CNN
	1    8450 3850
	-1   0    0    1   
$EndComp
$Comp
L Device:R R30
U 1 1 60BD3023
P 8550 3850
F 0 "R30" V 8600 3700 50  0000 R CNN
F 1 "10K0" V 8550 3950 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 8480 3850 50  0001 C CNN
F 3 "~" H 8550 3850 50  0001 C CNN
	1    8550 3850
	-1   0    0    1   
$EndComp
$Comp
L Device:R R31
U 1 1 60BD32AD
P 8650 3850
F 0 "R31" V 8700 3700 50  0000 R CNN
F 1 "10K0" V 8650 3950 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 8580 3850 50  0001 C CNN
F 3 "~" H 8650 3850 50  0001 C CNN
	1    8650 3850
	-1   0    0    1   
$EndComp
$Comp
L Device:R R32
U 1 1 60BD340C
P 8900 4400
F 0 "R32" H 9050 4300 50  0000 R CNN
F 1 "10K0" V 8900 4500 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 8830 4400 50  0001 C CNN
F 3 "~" H 8900 4400 50  0001 C CNN
	1    8900 4400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9200 4400 9050 4400
Wire Wire Line
	8350 4000 8350 4100
Connection ~ 8350 4100
Wire Wire Line
	8350 4100 8200 4100
Wire Wire Line
	8450 4000 8450 4200
Connection ~ 8450 4200
Wire Wire Line
	8450 4200 8100 4200
Wire Wire Line
	8550 4000 8550 4400
Wire Wire Line
	8100 4400 8550 4400
Connection ~ 8550 4400
Wire Wire Line
	8550 4400 8750 4400
Wire Wire Line
	8650 4000 8650 4600
Connection ~ 8650 4600
Wire Wire Line
	8650 4600 8100 4600
Wire Wire Line
	9350 3450 9100 3450
Connection ~ 9100 3450
Wire Wire Line
	8350 3700 8350 3450
Wire Wire Line
	8350 3450 8450 3450
Wire Wire Line
	8450 3700 8450 3450
Connection ~ 8450 3450
Wire Wire Line
	8450 3450 8550 3450
Wire Wire Line
	8550 3700 8550 3450
Connection ~ 8550 3450
Wire Wire Line
	8550 3450 8650 3450
Wire Wire Line
	8650 3700 8650 3450
Connection ~ 8650 3450
Wire Wire Line
	8650 3450 9100 3450
$Comp
L Device:C C21
U 1 1 60CC96FA
P 1500 750
F 0 "C21" H 1385 704 50  0000 R CNN
F 1 "10U0" H 1385 795 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1538 600 50  0001 C CNN
F 3 "~" H 1500 750 50  0001 C CNN
	1    1500 750 
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR044
U 1 1 60CCA002
P 1500 1050
F 0 "#PWR044" H 1500 800 50  0001 C CNN
F 1 "GND" H 1505 877 50  0000 C CNN
F 2 "" H 1500 1050 50  0001 C CNN
F 3 "" H 1500 1050 50  0001 C CNN
	1    1500 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 1050 1500 900 
Text Notes 7400 6950 0    118  ~ 24
ESP32 MICROCONTROLLER
$Comp
L WBSonar-rescue:TFT_LCD-Kona_Parts U13
U 1 1 60DB1762
P 10450 1800
F 0 "U13" H 10500 1600 50  0000 L CNN
F 1 "TFT_LCD" H 10450 450 50  0000 L CNN
F 2 "Kona:TFT_DISP_2P2" H 10450 1800 118 0001 C CNN
F 3 "" H 10450 1800 118 0001 C CNN
	1    10450 1800
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR055
U 1 1 60DB2A80
P 9950 2100
F 0 "#PWR055" H 9950 1950 50  0001 C CNN
F 1 "+3V3" H 9965 2273 50  0000 C CNN
F 2 "" H 9950 2100 50  0001 C CNN
F 3 "" H 9950 2100 50  0001 C CNN
	1    9950 2100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR054
U 1 1 60DB2F5A
P 9900 3100
F 0 "#PWR054" H 9900 2850 50  0001 C CNN
F 1 "GND" H 9905 2927 50  0000 C CNN
F 2 "" H 9900 3100 50  0001 C CNN
F 3 "" H 9900 3100 50  0001 C CNN
	1    9900 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 2250 9900 2250
Wire Wire Line
	9900 2250 9900 3100
Wire Wire Line
	10150 2150 9950 2150
Wire Wire Line
	9950 2150 9950 2100
Text GLabel 9350 2450 0    50   Input ~ 0
LCD_RSTn
Wire Wire Line
	10150 2450 9350 2450
Text GLabel 9350 2550 0    50   Input ~ 0
LCD_DC
Text GLabel 9350 2350 0    50   Input ~ 0
LCD_CSn
Wire Wire Line
	10150 2350 9350 2350
Text GLabel 9400 2950 0    50   Input ~ 0
MISO
Wire Wire Line
	10150 2950 9400 2950
Text GLabel 9400 2750 0    50   Input ~ 0
SCLK
Text GLabel 9400 2650 0    50   Input ~ 0
MOSI
Wire Wire Line
	9350 2550 10150 2550
Wire Wire Line
	10150 2650 9400 2650
Wire Wire Line
	10150 2750 9400 2750
$Comp
L Device:R R16
U 1 1 60EA13F2
P 2050 1000
F 0 "R16" V 2100 1250 50  0000 R CNN
F 1 "10K0" V 2050 1100 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1980 1000 50  0001 C CNN
F 3 "~" H 2050 1000 50  0001 C CNN
	1    2050 1000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R19
U 1 1 60F6ECE5
P 2150 1000
F 0 "R19" V 2200 1250 50  0000 R CNN
F 1 "10K0" V 2150 1100 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2080 1000 50  0001 C CNN
F 3 "~" H 2150 1000 50  0001 C CNN
	1    2150 1000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R20
U 1 1 60F6EF1E
P 2250 1000
F 0 "R20" V 2300 1250 50  0000 R CNN
F 1 "10K0" V 2250 1100 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2180 1000 50  0001 C CNN
F 3 "~" H 2250 1000 50  0001 C CNN
	1    2250 1000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R21
U 1 1 60F6F087
P 2350 1000
F 0 "R21" V 2400 1250 50  0000 R CNN
F 1 "10K0" V 2350 1100 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2280 1000 50  0001 C CNN
F 3 "~" H 2350 1000 50  0001 C CNN
	1    2350 1000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R22
U 1 1 60F6F1CB
P 2450 1000
F 0 "R22" V 2500 1250 50  0000 R CNN
F 1 "10K0" V 2450 1100 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2380 1000 50  0001 C CNN
F 3 "~" H 2450 1000 50  0001 C CNN
	1    2450 1000
	-1   0    0    1   
$EndComp
Wire Wire Line
	2050 850  2050 800 
Wire Wire Line
	1950 800  2050 800 
Wire Wire Line
	2800 800  2800 750 
Connection ~ 2050 800 
Wire Wire Line
	2050 800  2150 800 
Wire Wire Line
	2150 850  2150 800 
Connection ~ 2150 800 
Wire Wire Line
	2150 800  2250 800 
Wire Wire Line
	2250 850  2250 800 
Connection ~ 2250 800 
Wire Wire Line
	2250 800  2350 800 
Wire Wire Line
	2350 850  2350 800 
Connection ~ 2350 800 
Text GLabel 7250 2400 2    50   BiDi ~ 0
I2C_SDA
Text GLabel 7250 2100 2    50   Output ~ 0
I2C_SCL
$Comp
L Device:R R26
U 1 1 61080A3F
P 5800 1400
F 0 "R26" V 5850 1250 50  0000 R CNN
F 1 "4K7" V 5800 1500 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5730 1400 50  0001 C CNN
F 3 "~" H 5800 1400 50  0001 C CNN
	1    5800 1400
	-1   0    0    1   
$EndComp
$Comp
L Device:R R27
U 1 1 610811DE
P 5900 1400
F 0 "R27" V 5950 1250 50  0000 R CNN
F 1 "4K7" V 5900 1450 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5830 1400 50  0001 C CNN
F 3 "~" H 5900 1400 50  0001 C CNN
	1    5900 1400
	-1   0    0    1   
$EndComp
Wire Wire Line
	4550 5950 4550 6200
Wire Wire Line
	3750 6200 4550 6200
Connection ~ 4550 6200
Wire Wire Line
	4550 6200 4550 6450
Wire Wire Line
	3850 6300 4450 6300
Connection ~ 4450 6300
Text GLabel 7350 2800 2    50   Input ~ 0
GALIL_RSTn
Wire Wire Line
	2350 800  2450 800 
Wire Wire Line
	2450 850  2450 800 
Connection ~ 2450 800 
Wire Wire Line
	2450 800  2550 800 
Wire Wire Line
	1950 850  1950 800 
$Comp
L Device:R R40
U 1 1 608D7DC2
P 6600 5050
F 0 "R40" V 6650 4900 50  0000 R CNN
F 1 "10K0" V 6600 5150 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6530 5050 50  0001 C CNN
F 3 "~" H 6600 5050 50  0001 C CNN
	1    6600 5050
	-1   0    0    1   
$EndComp
$Comp
L Device:R R39
U 1 1 608D9037
P 6450 5050
F 0 "R39" V 6500 4900 50  0000 R CNN
F 1 "10K0" V 6450 5150 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6380 5050 50  0001 C CNN
F 3 "~" H 6450 5050 50  0001 C CNN
	1    6450 5050
	-1   0    0    1   
$EndComp
$Comp
L Device:R R10
U 1 1 608D922D
P 6300 5050
F 0 "R10" V 6350 4900 50  0000 R CNN
F 1 "10K0" V 6300 5150 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6230 5050 50  0001 C CNN
F 3 "~" H 6300 5050 50  0001 C CNN
	1    6300 5050
	-1   0    0    1   
$EndComp
Wire Wire Line
	6450 5550 6450 5200
Wire Wire Line
	6600 5300 6600 5200
Wire Wire Line
	6300 5200 6300 5800
$Comp
L power:GND #PWR0121
U 1 1 6094C1BE
P 7450 6000
F 0 "#PWR0121" H 7450 5750 50  0001 C CNN
F 1 "GND" H 7455 5827 50  0000 C CNN
F 2 "" H 7450 6000 50  0001 C CNN
F 3 "" H 7450 6000 50  0001 C CNN
	1    7450 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 4900 6300 4700
Wire Wire Line
	6300 4700 6450 4700
Wire Wire Line
	6600 4700 6600 4900
Wire Wire Line
	6450 4900 6450 4700
Connection ~ 6450 4700
Wire Wire Line
	6450 4700 6600 4700
$Comp
L power:+3V3 #PWR0122
U 1 1 609C3C76
P 6450 4650
F 0 "#PWR0122" H 6450 4500 50  0001 C CNN
F 1 "+3V3" H 6465 4823 50  0000 C CNN
F 2 "" H 6450 4650 50  0001 C CNN
F 3 "" H 6450 4650 50  0001 C CNN
	1    6450 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 4650 6450 4700
Wire Wire Line
	4950 5550 5350 5550
Text GLabel 6150 5300 0    50   Input ~ 0
BUTA
Text GLabel 6150 5550 0    50   Input ~ 0
BUTB
Text GLabel 6150 5800 0    50   Input ~ 0
BUTC
Wire Wire Line
	6150 5300 6600 5300
Connection ~ 6600 5300
Wire Wire Line
	6150 5550 6450 5550
Connection ~ 6450 5550
Wire Wire Line
	6150 5800 6300 5800
Connection ~ 6300 5800
$Comp
L Switch:SW_Push SW5
U 1 1 60C10D76
P 800 3450
F 0 "SW5" V 846 3402 50  0000 R CNN
F 1 "SW_Push" V 755 3402 50  0000 R CNN
F 2 "Button_Switch_SMD:Panasonic_EVQPUM_EVQPUD" H 800 3650 50  0001 C CNN
F 3 "~" H 800 3650 50  0001 C CNN
	1    800  3450
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0126
U 1 1 60C11893
P 800 3750
F 0 "#PWR0126" H 800 3500 50  0001 C CNN
F 1 "GND" H 805 3577 50  0000 C CNN
F 2 "" H 800 3750 50  0001 C CNN
F 3 "" H 800 3750 50  0001 C CNN
	1    800  3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	800  3250 800  3200
Wire Wire Line
	800  3200 1100 3200
Wire Wire Line
	1100 3200 1100 3100
Wire Wire Line
	750  1850 750  1800
Wire Wire Line
	750  1800 1100 1800
Connection ~ 1100 1800
Wire Wire Line
	1100 1800 1100 1700
$Comp
L power:GND #PWR0130
U 1 1 60DDF56C
P 3350 1500
F 0 "#PWR0130" H 3350 1250 50  0001 C CNN
F 1 "GND" H 3355 1327 50  0000 C CNN
F 2 "" H 3350 1500 50  0001 C CNN
F 3 "" H 3350 1500 50  0001 C CNN
	1    3350 1500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0131
U 1 1 60CDB74A
P 3400 3800
F 0 "#PWR0131" H 3400 3550 50  0001 C CNN
F 1 "GND" H 3405 3627 50  0000 C CNN
F 2 "" H 3400 3800 50  0001 C CNN
F 3 "" H 3400 3800 50  0001 C CNN
	1    3400 3800
	1    0    0    -1  
$EndComp
Text GLabel 6050 2200 2    50   Input ~ 0
RXD
Text GLabel 6050 2300 2    50   Input ~ 0
TXD
Text GLabel 7350 3100 2    50   Input ~ 0
SD_CSn
Text GLabel 6050 2600 2    50   Input ~ 0
MISO
Text GLabel 6050 2700 2    50   Input ~ 0
SCLK
Text GLabel 6050 2000 2    50   Input ~ 0
MOSI
$Comp
L Device:C C19
U 1 1 610191DE
P 1100 3450
F 0 "C19" H 985 3404 50  0000 R CNN
F 1 "C" H 985 3495 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1138 3300 50  0001 C CNN
F 3 "~" H 1100 3450 50  0001 C CNN
	1    1100 3450
	-1   0    0    1   
$EndComp
Wire Wire Line
	1100 3300 1100 3200
Connection ~ 1100 3200
Wire Wire Line
	800  3750 800  3700
Wire Wire Line
	1100 3600 1100 3700
Wire Wire Line
	1100 3700 800  3700
Connection ~ 800  3700
Wire Wire Line
	800  3700 800  3650
$Comp
L power:GND #PWR0125
U 1 1 60C11558
P 750 2250
F 0 "#PWR0125" H 750 2000 50  0001 C CNN
F 1 "GND" H 755 2077 50  0000 C CNN
F 2 "" H 750 2250 50  0001 C CNN
F 3 "" H 750 2250 50  0001 C CNN
	1    750  2250
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW4
U 1 1 60C0EEF4
P 750 2050
F 0 "SW4" V 796 2002 50  0000 R CNN
F 1 "SW_Push" V 705 2002 50  0000 R CNN
F 2 "Button_Switch_SMD:Panasonic_EVQPUM_EVQPUD" H 750 2250 50  0001 C CNN
F 3 "~" H 750 2250 50  0001 C CNN
	1    750  2050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1100 2300 1100 2150
$Comp
L power:GND #PWR031
U 1 1 60AE842C
P 1100 2300
F 0 "#PWR031" H 1100 2050 50  0001 C CNN
F 1 "GND" H 1105 2127 50  0000 C CNN
F 2 "" H 1100 2300 50  0001 C CNN
F 3 "" H 1100 2300 50  0001 C CNN
	1    1100 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C16
U 1 1 60AE8426
P 1100 2000
F 0 "C16" H 985 1954 50  0000 R CNN
F 1 "10U0" H 985 2045 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1138 1850 50  0001 C CNN
F 3 "~" H 1100 2000 50  0001 C CNN
	1    1100 2000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R45
U 1 1 6110B658
P 2550 1000
F 0 "R45" V 2600 1250 50  0000 R CNN
F 1 "10K0" V 2550 1100 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2480 1000 50  0001 C CNN
F 3 "~" H 2550 1000 50  0001 C CNN
	1    2550 1000
	-1   0    0    1   
$EndComp
Wire Wire Line
	1500 600  1500 550 
Wire Wire Line
	1500 550  1950 550 
Wire Wire Line
	1950 550  1950 800 
Connection ~ 1950 800 
Wire Wire Line
	2550 850  2550 800 
Connection ~ 2550 800 
Text GLabel 3100 2300 0    50   Input ~ 0
BUTA
Text GLabel 3100 2200 0    50   Input ~ 0
BUTB
Text GLabel 3100 2100 0    50   Input ~ 0
BUTC
$Comp
L Kona_Parts:ESP32-WROOM-32DM113DH6400PH3Q0 U11
U 1 1 617449BE
P 3650 1800
F 0 "U11" H 4650 2187 60  0000 C CNN
F 1 "ESP32-WROOM-32DM113DH6400PH3Q0" H 4650 2081 60  0000 C CNN
F 2 "Kona:ESP32-WROOM-32DM113DH6400PH3Q0" H 4650 2040 60  0001 C CNN
F 3 "" H 3650 1800 60  0000 C CNN
	1    3650 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 1550 5800 2100
Connection ~ 5800 2100
Wire Wire Line
	5800 2100 5650 2100
Wire Wire Line
	5900 1550 5900 2400
Connection ~ 5900 2400
Wire Wire Line
	5900 2400 5650 2400
Wire Wire Line
	5900 1250 5900 1100
Wire Wire Line
	5800 1100 5800 1250
Wire Wire Line
	5800 1100 5850 1100
Wire Wire Line
	5850 1000 5850 1100
Connection ~ 5850 1100
Wire Wire Line
	5850 1100 5900 1100
$Comp
L power:GND #PWR0132
U 1 1 61883AA7
P 6200 1650
F 0 "#PWR0132" H 6200 1400 50  0001 C CNN
F 1 "GND" H 6205 1477 50  0000 C CNN
F 2 "" H 6200 1650 50  0001 C CNN
F 3 "" H 6200 1650 50  0001 C CNN
	1    6200 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 1900 5750 1900
Wire Wire Line
	6200 1650 6200 1600
Wire Wire Line
	6200 1600 5750 1600
Wire Wire Line
	5750 1900 5750 1800
Wire Wire Line
	5650 1800 5750 1800
Connection ~ 5750 1800
Wire Wire Line
	5750 1800 5750 1600
Wire Wire Line
	6050 2700 5650 2700
Wire Wire Line
	6050 2600 5650 2600
Wire Wire Line
	3650 1800 3650 1400
Wire Wire Line
	3650 1400 3350 1400
Wire Wire Line
	3350 1400 3350 1500
Wire Wire Line
	6050 2200 5650 2200
Wire Wire Line
	6050 2300 5650 2300
Text GLabel 1750 2900 0    50   Input ~ 0
LCD_DC
Text GLabel 1750 3000 0    50   Input ~ 0
LCD_CSn
Text GLabel 1750 3100 0    50   Input ~ 0
LCD_RSTn
Wire Wire Line
	3650 2000 1500 2000
Wire Wire Line
	1500 2000 1500 1700
Wire Wire Line
	1500 1700 1100 1700
Wire Wire Line
	3650 1900 2800 1900
Wire Wire Line
	2800 1900 2800 800 
Connection ~ 2800 800 
Wire Wire Line
	3650 2100 3100 2100
Wire Wire Line
	3650 2200 3100 2200
Wire Wire Line
	3650 2300 3100 2300
Wire Wire Line
	3650 3200 3400 3200
Wire Wire Line
	3400 3200 3400 3700
$Comp
L Device:C C20
U 1 1 61B25563
P 6300 6200
F 0 "C20" V 6552 6200 50  0000 C CNN
F 1 "C" V 6461 6200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 6338 6050 50  0001 C CNN
F 3 "~" H 6300 6200 50  0001 C CNN
	1    6300 6200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C29
U 1 1 61B25C07
P 6500 6200
F 0 "C29" V 6752 6200 50  0000 C CNN
F 1 "C" V 6661 6200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 6538 6050 50  0001 C CNN
F 3 "~" H 6500 6200 50  0001 C CNN
	1    6500 6200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C32
U 1 1 61B26005
P 6700 6200
F 0 "C32" V 6952 6200 50  0000 C CNN
F 1 "C" V 6861 6200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 6738 6050 50  0001 C CNN
F 3 "~" H 6700 6200 50  0001 C CNN
	1    6700 6200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0133
U 1 1 61B262A3
P 6500 6550
F 0 "#PWR0133" H 6500 6300 50  0001 C CNN
F 1 "GND" H 6505 6377 50  0000 C CNN
F 2 "" H 6500 6550 50  0001 C CNN
F 3 "" H 6500 6550 50  0001 C CNN
	1    6500 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 6350 6300 6450
Wire Wire Line
	6300 6450 6500 6450
Wire Wire Line
	6700 6450 6700 6350
Wire Wire Line
	6500 6350 6500 6450
Connection ~ 6500 6450
Wire Wire Line
	6500 6450 6700 6450
Wire Wire Line
	6500 6550 6500 6450
Wire Wire Line
	6300 6050 6300 5800
Wire Wire Line
	6500 6050 6500 5550
Connection ~ 6500 5550
Wire Wire Line
	6500 5550 6450 5550
Wire Wire Line
	6700 6050 6700 5300
Connection ~ 6700 5300
Wire Wire Line
	6700 5300 6600 5300
$Comp
L Device:R R17
U 1 1 61CA72D9
P 1950 1000
F 0 "R17" V 2000 1250 50  0000 R CNN
F 1 "10K0" V 1950 1100 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1880 1000 50  0001 C CNN
F 3 "~" H 1950 1000 50  0001 C CNN
	1    1950 1000
	-1   0    0    1   
$EndComp
Wire Wire Line
	1950 1150 1950 2400
Wire Wire Line
	1950 2400 3650 2400
Wire Wire Line
	2050 1150 2050 2500
Wire Wire Line
	2050 2500 3650 2500
Wire Wire Line
	2150 1150 2150 2600
Wire Wire Line
	2150 2600 3650 2600
Wire Wire Line
	2250 1150 2250 2700
Wire Wire Line
	2250 2700 3650 2700
Wire Wire Line
	2350 1150 2350 2800
Wire Wire Line
	2350 2800 3650 2800
Wire Wire Line
	2450 1150 2450 2900
Wire Wire Line
	1750 2900 2450 2900
Connection ~ 2450 2900
Wire Wire Line
	2450 2900 3650 2900
Wire Wire Line
	2550 1150 2550 3000
Wire Wire Line
	1750 3000 2550 3000
Connection ~ 2550 3000
Wire Wire Line
	2550 3000 3650 3000
$Comp
L Device:R R47
U 1 1 61D5548A
P 6750 1400
F 0 "R47" V 6800 1650 50  0000 R CNN
F 1 "10K0" V 6750 1500 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6680 1400 50  0001 C CNN
F 3 "~" H 6750 1400 50  0001 C CNN
	1    6750 1400
	-1   0    0    1   
$EndComp
Wire Wire Line
	5650 3400 7050 3400
Wire Wire Line
	6750 1550 6750 2800
Wire Wire Line
	6750 2800 7350 2800
$Comp
L Device:R R48
U 1 1 61DC96C7
P 6850 1400
F 0 "R48" V 6900 1650 50  0000 R CNN
F 1 "10K0" V 6850 1500 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6780 1400 50  0001 C CNN
F 3 "~" H 6850 1400 50  0001 C CNN
	1    6850 1400
	-1   0    0    1   
$EndComp
$Comp
L Device:R R49
U 1 1 61DC98E9
P 6950 1400
F 0 "R49" V 7000 1650 50  0000 R CNN
F 1 "DNP" V 6950 1500 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6880 1400 50  0001 C CNN
F 3 "~" H 6950 1400 50  0001 C CNN
	1    6950 1400
	-1   0    0    1   
$EndComp
$Comp
L Device:R R50
U 1 1 61DC9AC2
P 7050 1400
F 0 "R50" V 7100 1650 50  0000 R CNN
F 1 "10K0" V 7050 1500 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6980 1400 50  0001 C CNN
F 3 "~" H 7050 1400 50  0001 C CNN
	1    7050 1400
	-1   0    0    1   
$EndComp
Wire Wire Line
	6850 1550 6850 3100
Wire Wire Line
	5650 3100 6850 3100
Connection ~ 6850 3100
Wire Wire Line
	6850 3100 7350 3100
Wire Wire Line
	6950 1550 6950 3300
Wire Wire Line
	5650 3300 6950 3300
Wire Wire Line
	7050 1550 7050 3400
$Comp
L power:+3V3 #PWR0134
U 1 1 61E10F3B
P 6900 1000
F 0 "#PWR0134" H 6900 850 50  0001 C CNN
F 1 "+3V3" H 6915 1173 50  0000 C CNN
F 2 "" H 6900 1000 50  0001 C CNN
F 3 "" H 6900 1000 50  0001 C CNN
	1    6900 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 1250 6750 1100
Wire Wire Line
	6750 1100 6850 1100
Wire Wire Line
	7050 1100 7050 1250
Wire Wire Line
	6900 1000 6900 1100
Connection ~ 6900 1100
Wire Wire Line
	6900 1100 6950 1100
Wire Wire Line
	6950 1250 6950 1100
Connection ~ 6950 1100
Wire Wire Line
	6950 1100 7050 1100
Wire Wire Line
	6850 1250 6850 1100
Connection ~ 6850 1100
Wire Wire Line
	6850 1100 6900 1100
Wire Wire Line
	6050 2000 5650 2000
$Comp
L Connector:TestPoint SCL1
U 1 1 60C30855
P 6400 2100
F 0 "SCL1" H 6458 2218 50  0000 L CNN
F 1 "SCL" H 6458 2127 50  0000 L CNN
F 2 "TestPoint:TestPoint_Keystone_5015_Micro-Minature" H 6600 2100 50  0001 C CNN
F 3 "~" H 6600 2100 50  0001 C CNN
	1    6400 2100
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint SDA1
U 1 1 60C322AD
P 6400 2400
F 0 "SDA1" H 6458 2518 50  0000 L CNN
F 1 "SDA" H 6458 2427 50  0000 L CNN
F 2 "TestPoint:TestPoint_Keystone_5015_Micro-Minature" H 6600 2400 50  0001 C CNN
F 3 "~" H 6600 2400 50  0001 C CNN
	1    6400 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 2400 6400 2400
Wire Wire Line
	5800 2100 6400 2100
Connection ~ 6400 2100
Wire Wire Line
	6400 2100 7250 2100
Connection ~ 6400 2400
Wire Wire Line
	6400 2400 7250 2400
Wire Wire Line
	2200 4950 2200 5450
$Comp
L Device:R R52
U 1 1 60DB40D9
P 1850 5650
F 0 "R52" H 2000 5550 50  0000 R CNN
F 1 "24K0" V 1850 5750 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1780 5650 50  0001 C CNN
F 3 "~" H 1850 5650 50  0001 C CNN
	1    1850 5650
	-1   0    0    1   
$EndComp
$Comp
L Device:R R53
U 1 1 60DB587D
P 1850 6000
F 0 "R53" H 2000 5900 50  0000 R CNN
F 1 "47K0" V 1850 6100 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1780 6000 50  0001 C CNN
F 3 "~" H 1850 6000 50  0001 C CNN
	1    1850 6000
	-1   0    0    1   
$EndComp
Wire Wire Line
	1850 6150 2200 6150
Connection ~ 2200 6150
Wire Wire Line
	2200 6150 2200 6100
Wire Wire Line
	1850 5850 1850 5800
Wire Wire Line
	1850 5500 1850 5450
Wire Wire Line
	1850 5450 2200 5450
Connection ~ 2200 5450
Wire Wire Line
	2200 5450 2200 5800
Wire Wire Line
	1850 5800 2050 5800
Wire Wire Line
	2050 5800 2050 5650
Wire Wire Line
	2050 5650 2250 5650
Wire Wire Line
	2250 5650 2250 5200
Wire Wire Line
	2250 5200 2350 5200
Connection ~ 1850 5800
$Comp
L Interface_USB:CP2102N-A01-GQFN28 U10
U 1 1 60883F21
P 2850 5900
F 0 "U10" H 3050 4600 50  0000 C CNN
F 1 "CP2102N-A01-GQFN28" H 3450 4500 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-28-1EP_5x5mm_P0.5mm_EP3.35x3.35mm" H 3300 4700 50  0001 L CNN
F 3 "https://www.silabs.com/documents/public/data-sheets/cp2102n-datasheet.pdf" H 2900 5150 50  0001 C CNN
	1    2850 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 5000 2350 4900
Wire Wire Line
	2350 4400 2850 4400
Wire Wire Line
	2350 4400 2350 4600
Connection ~ 2850 4400
$Comp
L Device:R R69
U 1 1 6119BCBB
P 9600 2850
F 0 "R69" V 9650 2700 50  0000 R CNN
F 1 "10K0" V 9600 2950 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9530 2850 50  0001 C CNN
F 3 "~" H 9600 2850 50  0001 C CNN
	1    9600 2850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10150 2850 9750 2850
Wire Wire Line
	9450 2850 9450 2150
Wire Wire Line
	9450 2150 9950 2150
Connection ~ 9950 2150
Wire Wire Line
	2550 800  2800 800 
$Comp
L Connector:TestPoint GND1
U 1 1 616A8870
P 3200 3700
F 0 "GND1" H 3258 3818 50  0000 L CNN
F 1 "GND" H 3258 3727 50  0000 L CNN
F 2 "TestPoint:TestPoint_Keystone_5015_Micro-Minature" H 3400 3700 50  0001 C CNN
F 3 "~" H 3400 3700 50  0001 C CNN
	1    3200 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 3700 3400 3700
Connection ~ 3400 3700
Wire Wire Line
	3400 3700 3400 3800
Text Notes 6500 750  0    50   ~ 0
GPIO2 must also be either left unconnected/floating
Text Notes 1500 4000 0    50   ~ 0
Added 10K Pulldown to IO12
$Comp
L Device:R R80
U 1 1 61592AD5
P 2450 3350
F 0 "R80" V 2550 3400 50  0000 R CNN
F 1 "10K0" V 2450 3450 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2380 3350 50  0001 C CNN
F 3 "~" H 2450 3350 50  0001 C CNN
	1    2450 3350
	-1   0    0    1   
$EndComp
Wire Wire Line
	2450 3100 3650 3100
Wire Wire Line
	2450 3100 2450 3200
$Comp
L power:GND #PWR0156
U 1 1 615C911A
P 2450 3700
F 0 "#PWR0156" H 2450 3450 50  0001 C CNN
F 1 "GND" H 2455 3527 50  0000 C CNN
F 2 "" H 2450 3700 50  0001 C CNN
F 3 "" H 2450 3700 50  0001 C CNN
	1    2450 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 3500 2450 3700
Wire Wire Line
	2450 3100 1750 3100
Connection ~ 2450 3100
Wire Wire Line
	1650 2800 2350 2800
Connection ~ 2350 2800
$Comp
L Kona_Parts:SEL_SW SW?
U 1 1 626D7B88
P 7700 5150
F 0 "SW?" H 7928 4801 50  0000 L CNN
F 1 "SEL_SW" H 7928 4710 50  0000 L CNN
F 2 "" H 7700 5150 50  0001 C CNN
F 3 "" H 7700 5150 50  0001 C CNN
	1    7700 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 5450 7250 5450
Wire Wire Line
	7250 5450 7250 5300
Wire Wire Line
	6700 5300 7250 5300
Wire Wire Line
	6500 5550 7550 5550
Wire Wire Line
	7550 5650 7250 5650
Wire Wire Line
	7250 5650 7250 5800
Wire Wire Line
	6300 5800 7250 5800
Wire Wire Line
	7550 5750 7450 5750
Wire Wire Line
	7450 5750 7450 6000
$Comp
L Kona_Parts:EVQ-WKA001 SW?
U 1 1 6277A55A
P 10200 950
F 0 "SW?" H 10478 551 50  0000 L CNN
F 1 "EVQ-WKA001" H 10478 460 50  0000 L CNN
F 2 "" H 10200 950 50  0001 C CNN
F 3 "" H 10200 950 50  0001 C CNN
	1    10200 950 
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6277D3AC
P 9550 950
F 0 "R?" V 9600 1200 50  0000 R CNN
F 1 "10K0" V 9550 1050 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9480 950 50  0001 C CNN
F 3 "~" H 9550 950 50  0001 C CNN
	1    9550 950 
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 6277DB85
P 9400 950
F 0 "R?" V 9450 1200 50  0000 R CNN
F 1 "10K0" V 9400 1050 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9330 950 50  0001 C CNN
F 3 "~" H 9400 950 50  0001 C CNN
	1    9400 950 
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 6277DC8C
P 9250 950
F 0 "R?" V 9300 1200 50  0000 R CNN
F 1 "10K0" V 9250 1050 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9180 950 50  0001 C CNN
F 3 "~" H 9250 950 50  0001 C CNN
	1    9250 950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	10000 1150 9550 1150
Wire Wire Line
	9550 1150 9550 1100
Wire Wire Line
	10000 1450 9400 1450
Wire Wire Line
	10000 1650 9250 1650
Wire Wire Line
	9250 1650 9250 1250
$Comp
L power:GND #PWR?
U 1 1 627CF482
P 9750 1750
F 0 "#PWR?" H 9750 1500 50  0001 C CNN
F 1 "GND" H 9755 1577 50  0000 C CNN
F 2 "" H 9750 1750 50  0001 C CNN
F 3 "" H 9750 1750 50  0001 C CNN
	1    9750 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 1250 9750 1250
Wire Wire Line
	9750 1250 9750 1350
Wire Wire Line
	10000 1350 9750 1350
Connection ~ 9750 1350
Wire Wire Line
	9750 1350 9750 1550
Connection ~ 9750 1550
Wire Wire Line
	9750 1550 9750 1750
Wire Wire Line
	9750 1550 10000 1550
$Comp
L power:+3V3 #PWR?
U 1 1 6283F25F
P 9400 700
F 0 "#PWR?" H 9400 550 50  0001 C CNN
F 1 "+3V3" H 9415 873 50  0000 C CNN
F 2 "" H 9400 700 50  0001 C CNN
F 3 "" H 9400 700 50  0001 C CNN
	1    9400 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 700  9250 700 
Wire Wire Line
	9250 700  9250 800 
Wire Wire Line
	9550 800  9550 700 
Wire Wire Line
	9550 700  9400 700 
Connection ~ 9400 700 
Wire Wire Line
	9400 800  9400 700 
$Comp
L Device:C C?
U 1 1 62895249
P 8700 1800
F 0 "C?" V 8952 1800 50  0000 C CNN
F 1 "C" V 8861 1800 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 8738 1650 50  0001 C CNN
F 3 "~" H 8700 1800 50  0001 C CNN
	1    8700 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 628961E9
P 8400 1800
F 0 "C?" V 8652 1800 50  0000 C CNN
F 1 "C" V 8561 1800 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 8438 1650 50  0001 C CNN
F 3 "~" H 8400 1800 50  0001 C CNN
	1    8400 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 628963D4
P 8100 1800
F 0 "C?" V 8352 1800 50  0000 C CNN
F 1 "C" V 8261 1800 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 8138 1650 50  0001 C CNN
F 3 "~" H 8100 1800 50  0001 C CNN
	1    8100 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 1650 8100 1250
Wire Wire Line
	8100 1250 9250 1250
Connection ~ 9250 1250
Wire Wire Line
	9250 1250 9250 1100
Wire Wire Line
	8400 1650 8400 1450
Wire Wire Line
	8700 1350 9550 1350
Wire Wire Line
	9550 1350 9550 1150
Connection ~ 9550 1150
Wire Wire Line
	8700 1350 8700 1650
$Comp
L power:GND #PWR?
U 1 1 6290D1B7
P 8400 2100
F 0 "#PWR?" H 8400 1850 50  0001 C CNN
F 1 "GND" H 8405 1927 50  0000 C CNN
F 2 "" H 8400 2100 50  0001 C CNN
F 3 "" H 8400 2100 50  0001 C CNN
	1    8400 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 2000 8400 2000
Wire Wire Line
	8400 2000 8400 2100
Wire Wire Line
	8100 2000 8100 1950
Wire Wire Line
	8400 1950 8400 2000
Connection ~ 8400 2000
Wire Wire Line
	8700 1950 8700 2000
Wire Wire Line
	8700 2000 8400 2000
Text GLabel 7900 1350 0    50   Input ~ 0
ROT_A
Text GLabel 7900 1250 0    50   Input ~ 0
ROT_B
Text GLabel 7900 1450 0    50   Input ~ 0
ROT_SEL
Wire Wire Line
	7900 1250 8100 1250
Connection ~ 8100 1250
Wire Wire Line
	7900 1350 8700 1350
Connection ~ 8700 1350
Wire Wire Line
	7900 1450 8400 1450
Text GLabel 7400 3400 2    50   Input ~ 0
ROT_B
Text GLabel 7400 3300 2    50   Input ~ 0
ROT_A
Wire Wire Line
	7400 3300 6950 3300
Connection ~ 6950 3300
Wire Wire Line
	7400 3400 7050 3400
Connection ~ 7050 3400
Wire Wire Line
	9400 1100 9400 1450
Wire Wire Line
	8400 1450 9400 1450
Connection ~ 8400 1450
Connection ~ 9400 1450
Text GLabel 7400 3200 2    50   Input ~ 0
ROT_SEL
Wire Wire Line
	5650 3200 7400 3200
Text GLabel 3250 3300 0    50   Input ~ 0
CypressRST_MOT0
Wire Wire Line
	3650 3300 3250 3300
Text GLabel 1650 2800 0    50   Input ~ 0
CYP_CSn
Text GLabel 1950 2600 0    50   Input ~ 0
ENC1_HOME_OUT
Text GLabel 1950 2700 0    50   Input ~ 0
ENC1_INDEX_OUT
Wire Wire Line
	1950 2600 2150 2600
Connection ~ 2150 2600
Wire Wire Line
	1950 2700 2250 2700
Connection ~ 2250 2700
Text GLabel 4850 4500 0    50   Input ~ 0
GALIL_DEC
Text GLabel 4850 4600 0    50   Input ~ 0
GALIL_INC
Text GLabel 4850 4200 0    50   Input ~ 0
GALIL_CLK
$EndSCHEMATC

EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 5
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
L Kona_Parts:GALIL U?
U 1 1 624D79D6
P 2350 1500
AR Path="/624D79D6" Ref="U?"  Part="1" 
AR Path="/624D4519/624D79D6" Ref="U3"  Part="1" 
F 0 "U3" H 2475 1615 50  0000 C CNN
F 1 "GALIL" H 2475 1524 50  0000 C CNN
F 2 "Package_DIP:DIP-28_W15.24mm_LongPads" H 2350 1500 50  0001 C CNN
F 3 "" H 2350 1500 50  0001 C CNN
	1    2350 1500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 624D79DC
P 1650 3000
AR Path="/624D79DC" Ref="#PWR?"  Part="1" 
AR Path="/624D4519/624D79DC" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 1650 2750 50  0001 C CNN
F 1 "GND" H 1655 2827 50  0000 C CNN
F 2 "" H 1650 3000 50  0001 C CNN
F 3 "" H 1650 3000 50  0001 C CNN
	1    1650 3000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 624D79E2
P 3400 3000
AR Path="/624D79E2" Ref="#PWR?"  Part="1" 
AR Path="/624D4519/624D79E2" Ref="#PWR0102"  Part="1" 
F 0 "#PWR0102" H 3400 2750 50  0001 C CNN
F 1 "GND" H 3405 2827 50  0000 C CNN
F 2 "" H 3400 3000 50  0001 C CNN
F 3 "" H 3400 3000 50  0001 C CNN
	1    3400 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 1650 1650 1650
Wire Wire Line
	1650 1650 1650 2950
Wire Wire Line
	3400 1750 3400 1850
Wire Wire Line
	2950 1750 3400 1750
Wire Wire Line
	2950 1850 3400 1850
Connection ~ 3400 1850
Wire Wire Line
	3400 1850 3400 2050
Wire Wire Line
	2950 2050 3400 2050
Connection ~ 3400 2050
Wire Wire Line
	3400 2050 3400 2950
Wire Wire Line
	2950 2950 3400 2950
Wire Wire Line
	2000 2950 1650 2950
Text GLabel 1350 2850 0    50   Input ~ 0
GALIL_RSTn_HV
Text GLabel 1300 2350 0    50   Input ~ 0
GALIL_DEC_HV
Text GLabel 1300 2450 0    50   Input ~ 0
GALIL_INC_HV
$Comp
L Amplifier_Operational:TL081 U4
U 1 1 624DD6B4
P 5450 2050
F 0 "U4" H 5794 2096 50  0000 L CNN
F 1 "TL081" H 5794 2005 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 5500 2100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 5600 2200 50  0001 C CNN
	1    5450 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 1600 6350 2050
Wire Wire Line
	6350 2600 6700 2600
Wire Wire Line
	5750 2050 6350 2050
Connection ~ 6350 2050
Wire Wire Line
	6350 2050 6350 2600
$Comp
L Device:R R31
U 1 1 624E1A31
P 5350 1300
F 0 "R31" V 5143 1300 50  0000 C CNN
F 1 "68K" V 5234 1300 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5280 1300 50  0001 C CNN
F 3 "~" H 5350 1300 50  0001 C CNN
	1    5350 1300
	0    1    1    0   
$EndComp
$Comp
L Device:R R23
U 1 1 624E2007
P 4250 1050
F 0 "R23" H 4180 1004 50  0000 R CNN
F 1 "130K" H 4180 1095 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4180 1050 50  0001 C CNN
F 3 "~" H 4250 1050 50  0001 C CNN
	1    4250 1050
	-1   0    0    1   
$EndComp
$Comp
L Device:R R24
U 1 1 624E23C7
P 4250 1500
F 0 "R24" H 4180 1454 50  0000 R CNN
F 1 "10K" H 4180 1545 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4180 1500 50  0001 C CNN
F 3 "~" H 4250 1500 50  0001 C CNN
	1    4250 1500
	-1   0    0    1   
$EndComp
Wire Wire Line
	5150 2150 4850 2150
Wire Wire Line
	4850 2150 4850 1300
Wire Wire Line
	4850 1300 4250 1300
Wire Wire Line
	4250 1300 4250 1200
Wire Wire Line
	4250 1350 4250 1300
Connection ~ 4250 1300
Connection ~ 4850 1300
Wire Wire Line
	4850 1300 5200 1300
$Comp
L power:-5V #PWR0107
U 1 1 624E45F2
P 6750 3050
F 0 "#PWR0107" H 6750 3150 50  0001 C CNN
F 1 "-5V" H 6765 3223 50  0000 C CNN
F 2 "" H 6750 3050 50  0001 C CNN
F 3 "" H 6750 3050 50  0001 C CNN
	1    6750 3050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0108
U 1 1 624E4F5F
P 7000 1150
F 0 "#PWR0108" H 7000 1000 50  0001 C CNN
F 1 "+5V" H 7015 1323 50  0000 C CNN
F 2 "" H 7000 1150 50  0001 C CNN
F 3 "" H 7000 1150 50  0001 C CNN
	1    7000 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 1400 7000 1350
Wire Wire Line
	6750 3050 6750 3150
Wire Wire Line
	6750 3150 7000 3150
Wire Wire Line
	7000 3150 7000 3050
$Comp
L Device:CP C7
U 1 1 624E63B7
P 7600 1350
F 0 "C7" V 7855 1350 50  0000 C CNN
F 1 "CP" V 7764 1350 50  0000 C CNN
F 2 "Capacitor_SMD:CP_Elec_10x10.5" H 7638 1200 50  0001 C CNN
F 3 "~" H 7600 1350 50  0001 C CNN
	1    7600 1350
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP C6
U 1 1 624E68A8
P 7000 3400
F 0 "C6" H 6882 3354 50  0000 R CNN
F 1 "CP" H 6882 3445 50  0000 R CNN
F 2 "Capacitor_SMD:CP_Elec_10x10.5" H 7038 3250 50  0001 C CNN
F 3 "~" H 7000 3400 50  0001 C CNN
	1    7000 3400
	-1   0    0    1   
$EndComp
Wire Wire Line
	7450 1350 7100 1350
Connection ~ 7000 1350
Wire Wire Line
	7000 1350 7000 1150
$Comp
L power:GNDPWR #PWR0117
U 1 1 624E95AC
P 7950 1500
F 0 "#PWR0117" H 7950 1300 50  0001 C CNN
F 1 "GNDPWR" H 7954 1346 50  0000 C CNN
F 2 "" H 7950 1450 50  0001 C CNN
F 3 "" H 7950 1450 50  0001 C CNN
	1    7950 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 1350 7950 1350
Wire Wire Line
	7950 1350 7950 1500
$Comp
L power:GNDPWR #PWR0118
U 1 1 624EAA35
P 7000 3650
F 0 "#PWR0118" H 7000 3450 50  0001 C CNN
F 1 "GNDPWR" H 7004 3496 50  0000 C CNN
F 2 "" H 7000 3600 50  0001 C CNN
F 3 "" H 7000 3600 50  0001 C CNN
	1    7000 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 624EB645
P 4250 1650
F 0 "#PWR0119" H 4250 1400 50  0001 C CNN
F 1 "GND" H 4255 1477 50  0000 C CNN
F 2 "" H 4250 1650 50  0001 C CNN
F 3 "" H 4250 1650 50  0001 C CNN
	1    4250 1650
	1    0    0    -1  
$EndComp
Text GLabel 1100 1850 0    50   Input ~ 0
Motor_Cntrl
Wire Wire Line
	3850 1950 3850 1250
Wire Wire Line
	3850 1250 1500 1250
Wire Wire Line
	1500 1250 1500 1850
Wire Wire Line
	3850 1950 5150 1950
Wire Wire Line
	1100 1850 1500 1850
Connection ~ 1500 1850
Wire Wire Line
	1500 1850 2000 1850
$Comp
L power:+15V #PWR0120
U 1 1 624EE569
P 5350 1600
F 0 "#PWR0120" H 5350 1450 50  0001 C CNN
F 1 "+15V" H 5365 1773 50  0000 C CNN
F 2 "" H 5350 1600 50  0001 C CNN
F 3 "" H 5350 1600 50  0001 C CNN
	1    5350 1600
	1    0    0    -1  
$EndComp
$Comp
L power:-15V #PWR0121
U 1 1 624EEBB4
P 4950 2650
F 0 "#PWR0121" H 4950 2750 50  0001 C CNN
F 1 "-15V" H 4965 2823 50  0000 C CNN
F 2 "" H 4950 2650 50  0001 C CNN
F 3 "" H 4950 2650 50  0001 C CNN
	1    4950 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 2350 5350 2800
Wire Wire Line
	5350 2800 4950 2800
Wire Wire Line
	4950 2800 4950 2650
Wire Wire Line
	5500 1300 6350 1300
Wire Wire Line
	6350 1300 6350 1600
Connection ~ 6350 1600
$Comp
L power:+15V #PWR0122
U 1 1 624F1322
P 4250 800
F 0 "#PWR0122" H 4250 650 50  0001 C CNN
F 1 "+15V" H 4265 973 50  0000 C CNN
F 2 "" H 4250 800 50  0001 C CNN
F 3 "" H 4250 800 50  0001 C CNN
	1    4250 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 900  4250 800 
Wire Wire Line
	5350 1750 5350 1700
$Comp
L Device:CP C5
U 1 1 624F352E
P 5700 1700
F 0 "C5" V 5955 1700 50  0000 C CNN
F 1 "CP" V 5864 1700 50  0000 C CNN
F 2 "Capacitor_SMD:CP_Elec_10x10.5" H 5738 1550 50  0001 C CNN
F 3 "~" H 5700 1700 50  0001 C CNN
	1    5700 1700
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP C4
U 1 1 624F3ED0
P 5650 2800
F 0 "C4" V 5395 2800 50  0000 C CNN
F 1 "CP" V 5486 2800 50  0000 C CNN
F 2 "Capacitor_SMD:CP_Elec_10x10.5" H 5688 2650 50  0001 C CNN
F 3 "~" H 5650 2800 50  0001 C CNN
	1    5650 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	5500 2800 5350 2800
Connection ~ 5350 2800
Wire Wire Line
	5550 1700 5350 1700
Connection ~ 5350 1700
Wire Wire Line
	5350 1700 5350 1600
$Comp
L power:GND #PWR0123
U 1 1 624F6123
P 6050 1800
F 0 "#PWR0123" H 6050 1550 50  0001 C CNN
F 1 "GND" H 6055 1627 50  0000 C CNN
F 2 "" H 6050 1800 50  0001 C CNN
F 3 "" H 6050 1800 50  0001 C CNN
	1    6050 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 1700 6050 1700
Wire Wire Line
	6050 1700 6050 1800
$Comp
L power:GND #PWR0124
U 1 1 624F739D
P 6000 2900
F 0 "#PWR0124" H 6000 2650 50  0001 C CNN
F 1 "GND" H 6005 2727 50  0000 C CNN
F 2 "" H 6000 2900 50  0001 C CNN
F 3 "" H 6000 2900 50  0001 C CNN
	1    6000 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 2800 6000 2800
Wire Wire Line
	6000 2800 6000 2900
$Comp
L power:GND #PWR0125
U 1 1 624F87A7
P 10950 850
F 0 "#PWR0125" H 10950 600 50  0001 C CNN
F 1 "GND" H 10955 677 50  0000 C CNN
F 2 "" H 10950 850 50  0001 C CNN
F 3 "" H 10950 850 50  0001 C CNN
	1    10950 850 
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0128
U 1 1 624F8C5F
P 10500 900
F 0 "#PWR0128" H 10500 700 50  0001 C CNN
F 1 "GNDPWR" H 10504 746 50  0000 C CNN
F 2 "" H 10500 850 50  0001 C CNN
F 3 "" H 10500 850 50  0001 C CNN
	1    10500 900 
	1    0    0    -1  
$EndComp
$Comp
L Device:R R41
U 1 1 624F9059
P 10700 700
F 0 "R41" V 10493 700 50  0000 C CNN
F 1 "0R0" V 10584 700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 10630 700 50  0001 C CNN
F 3 "~" H 10700 700 50  0001 C CNN
	1    10700 700 
	0    1    1    0   
$EndComp
Wire Wire Line
	10550 700  10500 700 
Wire Wire Line
	10500 700  10500 900 
Wire Wire Line
	10850 700  10950 700 
Wire Wire Line
	10950 700  10950 850 
Wire Wire Line
	2950 1650 3000 1650
Text GLabel 1350 2050 0    50   Input ~ 0
GALIL_CLK_HV
$Comp
L Device:R R18
U 1 1 624FF937
P 3200 1500
F 0 "R18" H 3130 1454 50  0000 R CNN
F 1 "10K" H 3130 1545 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 3130 1500 50  0001 C CNN
F 3 "~" H 3200 1500 50  0001 C CNN
	1    3200 1500
	-1   0    0    1   
$EndComp
Wire Wire Line
	2950 1950 3200 1950
Wire Wire Line
	3200 1950 3200 1650
Wire Wire Line
	3200 1350 3200 1000
Wire Wire Line
	3200 1000 3000 1000
Wire Wire Line
	3000 1000 3000 1650
Text GLabel 1350 2650 0    50   Input ~ 0
ENC2_A
Text GLabel 1350 2750 0    50   Input ~ 0
ENC2_B
Wire Wire Line
	2000 2650 1350 2650
Wire Wire Line
	2000 2750 1350 2750
Wire Wire Line
	1350 2850 2000 2850
$Comp
L Transistor_FET:BSS138 Q2
U 1 1 6252C98D
P 1850 3600
F 0 "Q2" V 2099 3600 50  0000 C CNN
F 1 "BSS138" V 2190 3600 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2050 3525 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 1850 3600 50  0001 L CNN
	1    1850 3600
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 6252D00A
P 1400 3500
F 0 "R7" H 1470 3546 50  0000 L CNN
F 1 "R" H 1470 3455 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1330 3500 50  0001 C CNN
F 3 "~" H 1400 3500 50  0001 C CNN
	1    1400 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R14
U 1 1 6252D7EC
P 2250 3500
F 0 "R14" H 2320 3546 50  0000 L CNN
F 1 "R" H 2320 3455 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2180 3500 50  0001 C CNN
F 3 "~" H 2250 3500 50  0001 C CNN
	1    2250 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 3700 1400 3700
Wire Wire Line
	1400 3700 1400 3650
Wire Wire Line
	2050 3700 2250 3700
Wire Wire Line
	2250 3700 2250 3650
$Comp
L power:+3V3 #PWR0131
U 1 1 625393D1
P 1400 3300
F 0 "#PWR0131" H 1400 3150 50  0001 C CNN
F 1 "+3V3" H 1415 3473 50  0000 C CNN
F 2 "" H 1400 3300 50  0001 C CNN
F 3 "" H 1400 3300 50  0001 C CNN
	1    1400 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 3350 1400 3300
Wire Wire Line
	1850 3400 1850 3350
Wire Wire Line
	1850 3350 1400 3350
Connection ~ 1400 3350
Text GLabel 1200 3700 0    50   Input ~ 0
GALIL_PE0
Text GLabel 2700 3700 2    50   Input ~ 0
HV_GALIL_PE0
Connection ~ 2250 3700
Wire Wire Line
	2250 3700 2700 3700
Wire Wire Line
	1400 3700 1200 3700
Connection ~ 1400 3700
Text GLabel 3500 2150 2    50   Input ~ 0
HV_GALIL_PE0
Wire Wire Line
	3500 2150 2950 2150
Text GLabel 3500 2250 2    50   Input ~ 0
HV_GALIL_PE1
Text GLabel 3500 2350 2    50   Input ~ 0
HV_GALIL_PE2
Text GLabel 3500 2450 2    50   Input ~ 0
HV_GALIL_PE3
Text GLabel 3500 2550 2    50   Input ~ 0
HV_GALIL_PE4
Text GLabel 3500 2650 2    50   Input ~ 0
HV_GALIL_PE5
Text GLabel 3500 2750 2    50   Input ~ 0
HV_GALIL_PE6
Text GLabel 3500 2850 2    50   Input ~ 0
HV_GALIL_PE7
Wire Wire Line
	3500 2250 2950 2250
Wire Wire Line
	2950 2350 3500 2350
Wire Wire Line
	2950 2450 3500 2450
Wire Wire Line
	2950 2550 3500 2550
Wire Wire Line
	2950 2650 3500 2650
Wire Wire Line
	2950 2750 3500 2750
Wire Wire Line
	3500 2850 2950 2850
$Comp
L Transistor_FET:BSS138 Q3
U 1 1 625732AE
P 1850 4350
F 0 "Q3" V 2099 4350 50  0000 C CNN
F 1 "BSS138" V 2190 4350 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2050 4275 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 1850 4350 50  0001 L CNN
	1    1850 4350
	0    1    1    0   
$EndComp
$Comp
L Device:R R8
U 1 1 625732B4
P 1400 4250
F 0 "R8" H 1470 4296 50  0000 L CNN
F 1 "R" H 1470 4205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1330 4250 50  0001 C CNN
F 3 "~" H 1400 4250 50  0001 C CNN
	1    1400 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R15
U 1 1 625732BA
P 2250 4250
F 0 "R15" H 2320 4296 50  0000 L CNN
F 1 "R" H 2320 4205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2180 4250 50  0001 C CNN
F 3 "~" H 2250 4250 50  0001 C CNN
	1    2250 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 4450 1400 4450
Wire Wire Line
	1400 4450 1400 4400
Wire Wire Line
	2050 4450 2250 4450
Wire Wire Line
	2250 4450 2250 4400
$Comp
L power:+3V3 #PWR0133
U 1 1 625732CA
P 1400 4050
F 0 "#PWR0133" H 1400 3900 50  0001 C CNN
F 1 "+3V3" H 1415 4223 50  0000 C CNN
F 2 "" H 1400 4050 50  0001 C CNN
F 3 "" H 1400 4050 50  0001 C CNN
	1    1400 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 4100 1400 4050
Wire Wire Line
	1850 4150 1850 4100
Wire Wire Line
	1850 4100 1400 4100
Connection ~ 1400 4100
Text GLabel 1200 4450 0    50   Input ~ 0
GALIL_PE1
Text GLabel 2700 4450 2    50   Input ~ 0
HV_GALIL_PE1
Connection ~ 2250 4450
Wire Wire Line
	2250 4450 2700 4450
Wire Wire Line
	1400 4450 1200 4450
Connection ~ 1400 4450
$Comp
L Transistor_FET:BSS138 Q4
U 1 1 62578921
P 1850 5100
F 0 "Q4" V 2099 5100 50  0000 C CNN
F 1 "BSS138" V 2190 5100 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2050 5025 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 1850 5100 50  0001 L CNN
	1    1850 5100
	0    1    1    0   
$EndComp
$Comp
L Device:R R12
U 1 1 62578927
P 1400 5000
F 0 "R12" H 1470 5046 50  0000 L CNN
F 1 "R" H 1470 4955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1330 5000 50  0001 C CNN
F 3 "~" H 1400 5000 50  0001 C CNN
	1    1400 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R16
U 1 1 6257892D
P 2250 5000
F 0 "R16" H 2320 5046 50  0000 L CNN
F 1 "R" H 2320 4955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2180 5000 50  0001 C CNN
F 3 "~" H 2250 5000 50  0001 C CNN
	1    2250 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 5200 1400 5200
Wire Wire Line
	1400 5200 1400 5150
Wire Wire Line
	2050 5200 2250 5200
Wire Wire Line
	2250 5200 2250 5150
$Comp
L power:+3V3 #PWR0135
U 1 1 6257893D
P 1400 4800
F 0 "#PWR0135" H 1400 4650 50  0001 C CNN
F 1 "+3V3" H 1415 4973 50  0000 C CNN
F 2 "" H 1400 4800 50  0001 C CNN
F 3 "" H 1400 4800 50  0001 C CNN
	1    1400 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 4850 1400 4800
Wire Wire Line
	1850 4900 1850 4850
Wire Wire Line
	1850 4850 1400 4850
Connection ~ 1400 4850
Text GLabel 1200 5200 0    50   Input ~ 0
GALIL_PE2
Text GLabel 2700 5200 2    50   Input ~ 0
HV_GALIL_PE2
Connection ~ 2250 5200
Wire Wire Line
	2250 5200 2700 5200
Wire Wire Line
	1400 5200 1200 5200
Connection ~ 1400 5200
$Comp
L Transistor_FET:BSS138 Q5
U 1 1 62582589
P 1900 5900
F 0 "Q5" V 2149 5900 50  0000 C CNN
F 1 "BSS138" V 2240 5900 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2100 5825 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 1900 5900 50  0001 L CNN
	1    1900 5900
	0    1    1    0   
$EndComp
$Comp
L Device:R R13
U 1 1 6258258F
P 1450 5800
F 0 "R13" H 1520 5846 50  0000 L CNN
F 1 "R" H 1520 5755 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1380 5800 50  0001 C CNN
F 3 "~" H 1450 5800 50  0001 C CNN
	1    1450 5800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R17
U 1 1 62582595
P 2300 5800
F 0 "R17" H 2370 5846 50  0000 L CNN
F 1 "R" H 2370 5755 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2230 5800 50  0001 C CNN
F 3 "~" H 2300 5800 50  0001 C CNN
	1    2300 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 6000 1450 6000
Wire Wire Line
	1450 6000 1450 5950
Wire Wire Line
	2100 6000 2300 6000
Wire Wire Line
	2300 6000 2300 5950
$Comp
L power:+3V3 #PWR0137
U 1 1 625825A5
P 1450 5600
F 0 "#PWR0137" H 1450 5450 50  0001 C CNN
F 1 "+3V3" H 1465 5773 50  0000 C CNN
F 2 "" H 1450 5600 50  0001 C CNN
F 3 "" H 1450 5600 50  0001 C CNN
	1    1450 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 5650 1450 5600
Wire Wire Line
	1900 5700 1900 5650
Wire Wire Line
	1900 5650 1450 5650
Connection ~ 1450 5650
Text GLabel 1250 6000 0    50   Input ~ 0
GALIL_PE3
Text GLabel 2750 6000 2    50   Input ~ 0
HV_GALIL_PE3
Connection ~ 2300 6000
Wire Wire Line
	2300 6000 2750 6000
Wire Wire Line
	1450 6000 1250 6000
Connection ~ 1450 6000
$Comp
L Transistor_FET:BSS138 Q6
U 1 1 62592CED
P 4450 3600
F 0 "Q6" V 4699 3600 50  0000 C CNN
F 1 "BSS138" V 4790 3600 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4650 3525 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 4450 3600 50  0001 L CNN
	1    4450 3600
	0    1    1    0   
$EndComp
$Comp
L Device:R R19
U 1 1 62592CF3
P 4000 3500
F 0 "R19" H 4070 3546 50  0000 L CNN
F 1 "R" H 4070 3455 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 3930 3500 50  0001 C CNN
F 3 "~" H 4000 3500 50  0001 C CNN
	1    4000 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R27
U 1 1 62592CF9
P 4850 3500
F 0 "R27" H 4920 3546 50  0000 L CNN
F 1 "R" H 4920 3455 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4780 3500 50  0001 C CNN
F 3 "~" H 4850 3500 50  0001 C CNN
	1    4850 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 3700 4000 3700
Wire Wire Line
	4000 3700 4000 3650
Wire Wire Line
	4650 3700 4850 3700
Wire Wire Line
	4850 3700 4850 3650
$Comp
L power:+3V3 #PWR0139
U 1 1 62592D09
P 4000 3300
F 0 "#PWR0139" H 4000 3150 50  0001 C CNN
F 1 "+3V3" H 4015 3473 50  0000 C CNN
F 2 "" H 4000 3300 50  0001 C CNN
F 3 "" H 4000 3300 50  0001 C CNN
	1    4000 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 3350 4000 3300
Wire Wire Line
	4450 3400 4450 3350
Wire Wire Line
	4450 3350 4000 3350
Connection ~ 4000 3350
Text GLabel 3800 3700 0    50   Input ~ 0
GALIL_PE4
Text GLabel 5300 3700 2    50   Input ~ 0
HV_GALIL_PE4
Connection ~ 4850 3700
Wire Wire Line
	4850 3700 5300 3700
Wire Wire Line
	4000 3700 3800 3700
Connection ~ 4000 3700
$Comp
L Transistor_FET:BSS138 Q7
U 1 1 625B7E26
P 4450 4350
F 0 "Q7" V 4699 4350 50  0000 C CNN
F 1 "BSS138" V 4790 4350 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4650 4275 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 4450 4350 50  0001 L CNN
	1    4450 4350
	0    1    1    0   
$EndComp
$Comp
L Device:R R20
U 1 1 625B7E2C
P 4000 4250
F 0 "R20" H 4070 4296 50  0000 L CNN
F 1 "R" H 4070 4205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 3930 4250 50  0001 C CNN
F 3 "~" H 4000 4250 50  0001 C CNN
	1    4000 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R28
U 1 1 625B7E32
P 4850 4250
F 0 "R28" H 4920 4296 50  0000 L CNN
F 1 "R" H 4920 4205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4780 4250 50  0001 C CNN
F 3 "~" H 4850 4250 50  0001 C CNN
	1    4850 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 4450 4000 4450
Wire Wire Line
	4000 4450 4000 4400
Wire Wire Line
	4650 4450 4850 4450
Wire Wire Line
	4850 4450 4850 4400
$Comp
L power:+3V3 #PWR0141
U 1 1 625B7E42
P 4000 4050
F 0 "#PWR0141" H 4000 3900 50  0001 C CNN
F 1 "+3V3" H 4015 4223 50  0000 C CNN
F 2 "" H 4000 4050 50  0001 C CNN
F 3 "" H 4000 4050 50  0001 C CNN
	1    4000 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 4100 4000 4050
Wire Wire Line
	4450 4150 4450 4100
Wire Wire Line
	4450 4100 4000 4100
Connection ~ 4000 4100
Text GLabel 3800 4450 0    50   Input ~ 0
GALIL_PE5
Text GLabel 5300 4450 2    50   Input ~ 0
HV_GALIL_PE5
Connection ~ 4850 4450
Wire Wire Line
	4850 4450 5300 4450
Wire Wire Line
	4000 4450 3800 4450
Connection ~ 4000 4450
$Comp
L Transistor_FET:BSS138 Q8
U 1 1 625BFC71
P 4450 5100
F 0 "Q8" V 4699 5100 50  0000 C CNN
F 1 "BSS138" V 4790 5100 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4650 5025 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 4450 5100 50  0001 L CNN
	1    4450 5100
	0    1    1    0   
$EndComp
$Comp
L Device:R R21
U 1 1 625BFC77
P 4000 5000
F 0 "R21" H 4070 5046 50  0000 L CNN
F 1 "R" H 4070 4955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 3930 5000 50  0001 C CNN
F 3 "~" H 4000 5000 50  0001 C CNN
	1    4000 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R29
U 1 1 625BFC7D
P 4850 5000
F 0 "R29" H 4920 5046 50  0000 L CNN
F 1 "R" H 4920 4955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4780 5000 50  0001 C CNN
F 3 "~" H 4850 5000 50  0001 C CNN
	1    4850 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 5200 4000 5200
Wire Wire Line
	4000 5200 4000 5150
Wire Wire Line
	4650 5200 4850 5200
Wire Wire Line
	4850 5200 4850 5150
$Comp
L power:+3V3 #PWR0143
U 1 1 625BFC8D
P 4000 4800
F 0 "#PWR0143" H 4000 4650 50  0001 C CNN
F 1 "+3V3" H 4015 4973 50  0000 C CNN
F 2 "" H 4000 4800 50  0001 C CNN
F 3 "" H 4000 4800 50  0001 C CNN
	1    4000 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 4850 4000 4800
Wire Wire Line
	4450 4900 4450 4850
Wire Wire Line
	4450 4850 4000 4850
Connection ~ 4000 4850
Text GLabel 3800 5200 0    50   Input ~ 0
GALIL_PE6
Text GLabel 5300 5200 2    50   Input ~ 0
HV_GALIL_PE6
Connection ~ 4850 5200
Wire Wire Line
	4850 5200 5300 5200
Wire Wire Line
	4000 5200 3800 5200
Connection ~ 4000 5200
$Comp
L Transistor_FET:BSS138 Q9
U 1 1 625C8F98
P 4450 5900
F 0 "Q9" V 4699 5900 50  0000 C CNN
F 1 "BSS138" V 4790 5900 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4650 5825 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 4450 5900 50  0001 L CNN
	1    4450 5900
	0    1    1    0   
$EndComp
$Comp
L Device:R R22
U 1 1 625C8F9E
P 4000 5800
F 0 "R22" H 4070 5846 50  0000 L CNN
F 1 "R" H 4070 5755 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 3930 5800 50  0001 C CNN
F 3 "~" H 4000 5800 50  0001 C CNN
	1    4000 5800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R30
U 1 1 625C8FA4
P 4850 5800
F 0 "R30" H 4920 5846 50  0000 L CNN
F 1 "R" H 4920 5755 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4780 5800 50  0001 C CNN
F 3 "~" H 4850 5800 50  0001 C CNN
	1    4850 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 6000 4000 6000
Wire Wire Line
	4000 6000 4000 5950
Wire Wire Line
	4650 6000 4850 6000
Wire Wire Line
	4850 6000 4850 5950
$Comp
L power:+3V3 #PWR0145
U 1 1 625C8FB4
P 4000 5600
F 0 "#PWR0145" H 4000 5450 50  0001 C CNN
F 1 "+3V3" H 4015 5773 50  0000 C CNN
F 2 "" H 4000 5600 50  0001 C CNN
F 3 "" H 4000 5600 50  0001 C CNN
	1    4000 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 5650 4000 5600
Wire Wire Line
	4450 5700 4450 5650
Wire Wire Line
	4450 5650 4000 5650
Connection ~ 4000 5650
Text GLabel 3800 6000 0    50   Input ~ 0
GALIL_PE7
Text GLabel 5300 6000 2    50   Input ~ 0
HV_GALIL_PE7
Connection ~ 4850 6000
Wire Wire Line
	4850 6000 5300 6000
Wire Wire Line
	4000 6000 3800 6000
Connection ~ 4000 6000
Wire Wire Line
	7000 3250 7000 3150
Connection ~ 7000 3150
Wire Wire Line
	7000 3550 7000 3650
Wire Wire Line
	7150 2150 7000 2150
Wire Wire Line
	7000 1800 7000 2150
Connection ~ 7000 2150
Wire Wire Line
	7000 2150 7000 2400
$Comp
L Device:R R32
U 1 1 62C4ED5D
P 8400 1050
F 0 "R32" V 8193 1050 50  0000 C CNN
F 1 "1R0" V 8284 1050 50  0000 C CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.40x3.35mm_HandSolder" V 8330 1050 50  0001 C CNN
F 3 "~" H 8400 1050 50  0001 C CNN
	1    8400 1050
	0    1    1    0   
$EndComp
$Comp
L Analog_ADC:INA219AxDCN U5
U 1 1 62C4F73B
P 9300 1750
F 0 "U5" H 9050 2100 50  0000 C CNN
F 1 "INA219AxDCN" H 9650 2100 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-8" H 9950 1400 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/ina219.pdf" H 9650 1650 50  0001 C CNN
	1    9300 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 1050 8200 1050
Wire Wire Line
	8900 1850 8200 1850
Wire Wire Line
	8200 1850 8200 1050
Connection ~ 8200 1050
Wire Wire Line
	8200 1050 7950 1050
Wire Wire Line
	8700 1650 8700 1050
Wire Wire Line
	8700 1050 8550 1050
Wire Wire Line
	8700 1650 8900 1650
Wire Wire Line
	8900 1050 8700 1050
Connection ~ 8700 1050
$Comp
L power:GND #PWR0146
U 1 1 62C83E4A
P 9300 2250
F 0 "#PWR0146" H 9300 2000 50  0001 C CNN
F 1 "GND" H 9305 2077 50  0000 C CNN
F 2 "" H 9300 2250 50  0001 C CNN
F 3 "" H 9300 2250 50  0001 C CNN
	1    9300 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0147
U 1 1 62C84542
P 9750 2250
F 0 "#PWR0147" H 9750 2000 50  0001 C CNN
F 1 "GND" H 9755 2077 50  0000 C CNN
F 2 "" H 9750 2250 50  0001 C CNN
F 3 "" H 9750 2250 50  0001 C CNN
	1    9750 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 2250 9300 2150
Wire Wire Line
	9700 1950 9750 1950
Wire Wire Line
	9750 1950 9750 2250
Text GLabel 10000 1550 2    50   Input ~ 0
I2C_SDA
Text GLabel 10000 1650 2    50   Input ~ 0
I2C_SCL
Wire Wire Line
	10000 1650 9700 1650
Wire Wire Line
	10000 1550 9700 1550
Connection ~ 8600 4550
Wire Wire Line
	8600 4550 8600 3700
Connection ~ 8600 5400
Wire Wire Line
	8600 4550 8600 5400
Wire Wire Line
	8600 6250 8600 5400
Connection ~ 8700 3950
Connection ~ 8700 4250
Wire Wire Line
	8700 4250 8700 3950
Connection ~ 8700 4800
Wire Wire Line
	8700 4800 8700 4250
Connection ~ 8700 5100
Wire Wire Line
	8700 5100 8700 4800
Connection ~ 8700 5650
Wire Wire Line
	8700 5650 8700 5100
Wire Wire Line
	8700 5950 8700 5650
Connection ~ 8700 3400
Wire Wire Line
	8700 3950 8700 3400
Wire Wire Line
	10300 6250 10300 6300
Wire Wire Line
	10200 6250 10300 6250
$Comp
L power:GND #PWR?
U 1 1 62CEF8BE
P 10300 6300
AR Path="/5F8DD708/62CEF8BE" Ref="#PWR?"  Part="1" 
AR Path="/5FA975DA/62CEF8BE" Ref="#PWR?"  Part="1" 
AR Path="/5FA97622/62CEF8BE" Ref="#PWR?"  Part="1" 
AR Path="/62A8FB07/62CEF8BE" Ref="#PWR?"  Part="1" 
AR Path="/624D4519/62CEF8BE" Ref="#PWR0148"  Part="1" 
F 0 "#PWR0148" H 10300 6050 50  0001 C CNN
F 1 "GND" H 10400 6300 50  0000 C CNN
F 2 "" H 10300 6300 50  0001 C CNN
F 3 "" H 10300 6300 50  0001 C CNN
	1    10300 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 6150 10600 6150
Connection ~ 9850 6150
Wire Wire Line
	9850 6250 9900 6250
Connection ~ 9850 6250
Wire Wire Line
	9850 6250 9850 6150
Wire Wire Line
	9800 6250 9850 6250
Wire Wire Line
	8600 6250 9500 6250
Wire Wire Line
	9500 5750 10600 5750
Connection ~ 9500 5750
Wire Wire Line
	9500 5650 9500 5750
Wire Wire Line
	9300 5650 9500 5650
Wire Wire Line
	9250 5750 9500 5750
Wire Wire Line
	9000 5650 8700 5650
Wire Wire Line
	9250 6150 9850 6150
Wire Wire Line
	8700 5950 8950 5950
$Comp
L Device:R R?
U 1 1 62CEF8D3
P 9650 6250
AR Path="/5F8DD708/62CEF8D3" Ref="R?"  Part="1" 
AR Path="/5FA975DA/62CEF8D3" Ref="R?"  Part="1" 
AR Path="/5FA97622/62CEF8D3" Ref="R?"  Part="1" 
AR Path="/62A8FB07/62CEF8D3" Ref="R?"  Part="1" 
AR Path="/624D4519/62CEF8D3" Ref="R40"  Part="1" 
F 0 "R40" V 9450 6150 50  0000 C CNN
F 1 "10K" V 9550 6150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9580 6250 50  0001 C CNN
F 3 "~" H 9650 6250 50  0001 C CNN
	1    9650 6250
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 62CEF8D9
P 10050 6250
AR Path="/5F8DD708/62CEF8D9" Ref="C?"  Part="1" 
AR Path="/5FA975DA/62CEF8D9" Ref="C?"  Part="1" 
AR Path="/5FA97622/62CEF8D9" Ref="C?"  Part="1" 
AR Path="/62A8FB07/62CEF8D9" Ref="C?"  Part="1" 
AR Path="/624D4519/62CEF8D9" Ref="C11"  Part="1" 
F 0 "C11" V 10302 6250 50  0000 C CNN
F 1 "C" V 10211 6250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 10088 6100 50  0001 C CNN
F 3 "~" H 10050 6250 50  0001 C CNN
	1    10050 6250
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 62CEF8DF
P 9150 5650
AR Path="/5F8DD708/62CEF8DF" Ref="R?"  Part="1" 
AR Path="/5FA975DA/62CEF8DF" Ref="R?"  Part="1" 
AR Path="/5FA97622/62CEF8DF" Ref="R?"  Part="1" 
AR Path="/62A8FB07/62CEF8DF" Ref="R?"  Part="1" 
AR Path="/624D4519/62CEF8DF" Ref="R36"  Part="1" 
F 0 "R36" V 8950 5550 50  0000 C CNN
F 1 "10K" V 9050 5550 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9080 5650 50  0001 C CNN
F 3 "~" H 9150 5650 50  0001 C CNN
	1    9150 5650
	0    1    1    0   
$EndComp
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 62CEF8E5
P 9150 5950
AR Path="/5F8DD708/62CEF8E5" Ref="Q?"  Part="1" 
AR Path="/5FA975DA/62CEF8E5" Ref="Q?"  Part="1" 
AR Path="/5FA97622/62CEF8E5" Ref="Q?"  Part="1" 
AR Path="/62A8FB07/62CEF8E5" Ref="Q?"  Part="1" 
AR Path="/624D4519/62CEF8E5" Ref="Q15"  Part="1" 
F 0 "Q15" H 8750 6000 50  0000 L CNN
F 1 "BSS138" H 8750 5900 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9350 5875 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/BS/BSS138.pdf" H 9150 5950 50  0001 L CNN
	1    9150 5950
	1    0    0    1   
$EndComp
Wire Wire Line
	10300 5400 10300 5450
Wire Wire Line
	10200 5400 10300 5400
$Comp
L power:GND #PWR?
U 1 1 62CEF8ED
P 10300 5450
AR Path="/5F8DD708/62CEF8ED" Ref="#PWR?"  Part="1" 
AR Path="/5FA975DA/62CEF8ED" Ref="#PWR?"  Part="1" 
AR Path="/5FA97622/62CEF8ED" Ref="#PWR?"  Part="1" 
AR Path="/62A8FB07/62CEF8ED" Ref="#PWR?"  Part="1" 
AR Path="/624D4519/62CEF8ED" Ref="#PWR0149"  Part="1" 
F 0 "#PWR0149" H 10300 5200 50  0001 C CNN
F 1 "GND" H 10400 5450 50  0000 C CNN
F 2 "" H 10300 5450 50  0001 C CNN
F 3 "" H 10300 5450 50  0001 C CNN
	1    10300 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 5300 10600 5300
Connection ~ 9850 5300
Wire Wire Line
	9850 5400 9900 5400
Connection ~ 9850 5400
Wire Wire Line
	9850 5400 9850 5300
Wire Wire Line
	9800 5400 9850 5400
Wire Wire Line
	8600 5400 9500 5400
Wire Wire Line
	9500 4900 10600 4900
Connection ~ 9500 4900
Wire Wire Line
	9500 4800 9500 4900
Wire Wire Line
	9300 4800 9500 4800
Wire Wire Line
	9250 4900 9500 4900
Wire Wire Line
	9000 4800 8700 4800
Wire Wire Line
	9250 5300 9850 5300
Wire Wire Line
	8700 5100 8950 5100
$Comp
L Device:R R?
U 1 1 62CEF902
P 9650 5400
AR Path="/5F8DD708/62CEF902" Ref="R?"  Part="1" 
AR Path="/5FA975DA/62CEF902" Ref="R?"  Part="1" 
AR Path="/5FA97622/62CEF902" Ref="R?"  Part="1" 
AR Path="/62A8FB07/62CEF902" Ref="R?"  Part="1" 
AR Path="/624D4519/62CEF902" Ref="R39"  Part="1" 
F 0 "R39" V 9450 5300 50  0000 C CNN
F 1 "10K" V 9550 5300 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9580 5400 50  0001 C CNN
F 3 "~" H 9650 5400 50  0001 C CNN
	1    9650 5400
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 62CEF908
P 10050 5400
AR Path="/5F8DD708/62CEF908" Ref="C?"  Part="1" 
AR Path="/5FA975DA/62CEF908" Ref="C?"  Part="1" 
AR Path="/5FA97622/62CEF908" Ref="C?"  Part="1" 
AR Path="/62A8FB07/62CEF908" Ref="C?"  Part="1" 
AR Path="/624D4519/62CEF908" Ref="C10"  Part="1" 
F 0 "C10" V 10302 5400 50  0000 C CNN
F 1 "C" V 10211 5400 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 10088 5250 50  0001 C CNN
F 3 "~" H 10050 5400 50  0001 C CNN
	1    10050 5400
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 62CEF90E
P 9150 4800
AR Path="/5F8DD708/62CEF90E" Ref="R?"  Part="1" 
AR Path="/5FA975DA/62CEF90E" Ref="R?"  Part="1" 
AR Path="/5FA97622/62CEF90E" Ref="R?"  Part="1" 
AR Path="/62A8FB07/62CEF90E" Ref="R?"  Part="1" 
AR Path="/624D4519/62CEF90E" Ref="R35"  Part="1" 
F 0 "R35" V 8950 4700 50  0000 C CNN
F 1 "10K" V 9050 4700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9080 4800 50  0001 C CNN
F 3 "~" H 9150 4800 50  0001 C CNN
	1    9150 4800
	0    1    1    0   
$EndComp
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 62CEF914
P 9150 5100
AR Path="/5F8DD708/62CEF914" Ref="Q?"  Part="1" 
AR Path="/5FA975DA/62CEF914" Ref="Q?"  Part="1" 
AR Path="/5FA97622/62CEF914" Ref="Q?"  Part="1" 
AR Path="/62A8FB07/62CEF914" Ref="Q?"  Part="1" 
AR Path="/624D4519/62CEF914" Ref="Q14"  Part="1" 
F 0 "Q14" H 8750 5150 50  0000 L CNN
F 1 "BSS138" H 8750 5050 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9350 5025 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/BS/BSS138.pdf" H 9150 5100 50  0001 L CNN
	1    9150 5100
	1    0    0    1   
$EndComp
Wire Wire Line
	10300 4550 10300 4600
Wire Wire Line
	10200 4550 10300 4550
$Comp
L power:GND #PWR?
U 1 1 62CEF91C
P 10300 4600
AR Path="/5F8DD708/62CEF91C" Ref="#PWR?"  Part="1" 
AR Path="/5FA975DA/62CEF91C" Ref="#PWR?"  Part="1" 
AR Path="/5FA97622/62CEF91C" Ref="#PWR?"  Part="1" 
AR Path="/62A8FB07/62CEF91C" Ref="#PWR?"  Part="1" 
AR Path="/624D4519/62CEF91C" Ref="#PWR0150"  Part="1" 
F 0 "#PWR0150" H 10300 4350 50  0001 C CNN
F 1 "GND" H 10400 4600 50  0000 C CNN
F 2 "" H 10300 4600 50  0001 C CNN
F 3 "" H 10300 4600 50  0001 C CNN
	1    10300 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 4450 10600 4450
Connection ~ 9850 4450
Wire Wire Line
	9850 4550 9900 4550
Connection ~ 9850 4550
Wire Wire Line
	9850 4550 9850 4450
Wire Wire Line
	9800 4550 9850 4550
Wire Wire Line
	8600 4550 9500 4550
Wire Wire Line
	9500 4050 10600 4050
Connection ~ 9500 4050
Wire Wire Line
	9500 3950 9500 4050
Wire Wire Line
	9300 3950 9500 3950
Wire Wire Line
	9250 4050 9500 4050
Wire Wire Line
	9000 3950 8700 3950
Wire Wire Line
	9250 4450 9850 4450
Wire Wire Line
	8700 4250 8950 4250
$Comp
L Device:R R?
U 1 1 62CEF931
P 9650 4550
AR Path="/5F8DD708/62CEF931" Ref="R?"  Part="1" 
AR Path="/5FA975DA/62CEF931" Ref="R?"  Part="1" 
AR Path="/5FA97622/62CEF931" Ref="R?"  Part="1" 
AR Path="/62A8FB07/62CEF931" Ref="R?"  Part="1" 
AR Path="/624D4519/62CEF931" Ref="R38"  Part="1" 
F 0 "R38" V 9450 4450 50  0000 C CNN
F 1 "10K" V 9550 4450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9580 4550 50  0001 C CNN
F 3 "~" H 9650 4550 50  0001 C CNN
	1    9650 4550
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 62CEF937
P 10050 4550
AR Path="/5F8DD708/62CEF937" Ref="C?"  Part="1" 
AR Path="/5FA975DA/62CEF937" Ref="C?"  Part="1" 
AR Path="/5FA97622/62CEF937" Ref="C?"  Part="1" 
AR Path="/62A8FB07/62CEF937" Ref="C?"  Part="1" 
AR Path="/624D4519/62CEF937" Ref="C9"  Part="1" 
F 0 "C9" V 10302 4550 50  0000 C CNN
F 1 "C" V 10211 4550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 10088 4400 50  0001 C CNN
F 3 "~" H 10050 4550 50  0001 C CNN
	1    10050 4550
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 62CEF93D
P 9150 3950
AR Path="/5F8DD708/62CEF93D" Ref="R?"  Part="1" 
AR Path="/5FA975DA/62CEF93D" Ref="R?"  Part="1" 
AR Path="/5FA97622/62CEF93D" Ref="R?"  Part="1" 
AR Path="/62A8FB07/62CEF93D" Ref="R?"  Part="1" 
AR Path="/624D4519/62CEF93D" Ref="R34"  Part="1" 
F 0 "R34" V 8950 3850 50  0000 C CNN
F 1 "10K" V 9050 3850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9080 3950 50  0001 C CNN
F 3 "~" H 9150 3950 50  0001 C CNN
	1    9150 3950
	0    1    1    0   
$EndComp
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 62CEF943
P 9150 4250
AR Path="/5F8DD708/62CEF943" Ref="Q?"  Part="1" 
AR Path="/5FA975DA/62CEF943" Ref="Q?"  Part="1" 
AR Path="/5FA97622/62CEF943" Ref="Q?"  Part="1" 
AR Path="/62A8FB07/62CEF943" Ref="Q?"  Part="1" 
AR Path="/624D4519/62CEF943" Ref="Q13"  Part="1" 
F 0 "Q13" H 8750 4300 50  0000 L CNN
F 1 "BSS138" H 8750 4200 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9350 4175 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/BS/BSS138.pdf" H 9150 4250 50  0001 L CNN
	1    9150 4250
	1    0    0    1   
$EndComp
Wire Wire Line
	10300 3700 10300 3750
Wire Wire Line
	10200 3700 10300 3700
$Comp
L power:GND #PWR?
U 1 1 62CEF94B
P 10300 3750
AR Path="/5F8DD708/62CEF94B" Ref="#PWR?"  Part="1" 
AR Path="/5FA975DA/62CEF94B" Ref="#PWR?"  Part="1" 
AR Path="/5FA97622/62CEF94B" Ref="#PWR?"  Part="1" 
AR Path="/62A8FB07/62CEF94B" Ref="#PWR?"  Part="1" 
AR Path="/624D4519/62CEF94B" Ref="#PWR0151"  Part="1" 
F 0 "#PWR0151" H 10300 3500 50  0001 C CNN
F 1 "GND" H 10400 3750 50  0000 C CNN
F 2 "" H 10300 3750 50  0001 C CNN
F 3 "" H 10300 3750 50  0001 C CNN
	1    10300 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 3600 10600 3600
Connection ~ 9850 3600
Wire Wire Line
	9850 3700 9900 3700
Connection ~ 9850 3700
Wire Wire Line
	9850 3700 9850 3600
Wire Wire Line
	9800 3700 9850 3700
Wire Wire Line
	8600 3700 9500 3700
Wire Wire Line
	9500 3200 10600 3200
Connection ~ 9500 3200
Wire Wire Line
	9500 3100 9500 3200
Wire Wire Line
	9300 3100 9500 3100
Wire Wire Line
	9250 3200 9500 3200
Wire Wire Line
	8700 3100 8700 3400
Wire Wire Line
	9000 3100 8700 3100
Wire Wire Line
	9250 3600 9850 3600
Wire Wire Line
	8700 3400 8950 3400
$Comp
L Device:R R?
U 1 1 62CEF966
P 9650 3700
AR Path="/5F8DD708/62CEF966" Ref="R?"  Part="1" 
AR Path="/5FA975DA/62CEF966" Ref="R?"  Part="1" 
AR Path="/5FA97622/62CEF966" Ref="R?"  Part="1" 
AR Path="/62A8FB07/62CEF966" Ref="R?"  Part="1" 
AR Path="/624D4519/62CEF966" Ref="R37"  Part="1" 
F 0 "R37" V 9450 3600 50  0000 C CNN
F 1 "10K" V 9550 3600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9580 3700 50  0001 C CNN
F 3 "~" H 9650 3700 50  0001 C CNN
	1    9650 3700
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 62CEF96C
P 10050 3700
AR Path="/5F8DD708/62CEF96C" Ref="C?"  Part="1" 
AR Path="/5FA975DA/62CEF96C" Ref="C?"  Part="1" 
AR Path="/5FA97622/62CEF96C" Ref="C?"  Part="1" 
AR Path="/62A8FB07/62CEF96C" Ref="C?"  Part="1" 
AR Path="/624D4519/62CEF96C" Ref="C8"  Part="1" 
F 0 "C8" V 10302 3700 50  0000 C CNN
F 1 "C" V 10211 3700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 10088 3550 50  0001 C CNN
F 3 "~" H 10050 3700 50  0001 C CNN
	1    10050 3700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 62CEF972
P 9150 3100
AR Path="/5F8DD708/62CEF972" Ref="R?"  Part="1" 
AR Path="/5FA975DA/62CEF972" Ref="R?"  Part="1" 
AR Path="/5FA97622/62CEF972" Ref="R?"  Part="1" 
AR Path="/62A8FB07/62CEF972" Ref="R?"  Part="1" 
AR Path="/624D4519/62CEF972" Ref="R33"  Part="1" 
F 0 "R33" V 8950 3000 50  0000 C CNN
F 1 "10K" V 9050 3000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9080 3100 50  0001 C CNN
F 3 "~" H 9150 3100 50  0001 C CNN
	1    9150 3100
	0    1    1    0   
$EndComp
Text GLabel 10600 6150 2    50   UnSpc ~ 0
ENC2_A
Text GLabel 10600 5750 2    50   UnSpc ~ 0
ENC2_A_L
Text GLabel 10600 5300 2    50   UnSpc ~ 0
ENC2_INDEX
Text GLabel 10600 4900 2    50   UnSpc ~ 0
ENC2_INDEX_L
Text GLabel 10600 4450 2    50   UnSpc ~ 0
ENC2_HOME
Text GLabel 10600 4050 2    50   UnSpc ~ 0
ENC2_HOME_L
Text GLabel 10600 3600 2    50   UnSpc ~ 0
ENC2_B
Text GLabel 10600 3200 2    50   UnSpc ~ 0
ENC2_B_L
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 62CEF982
P 9150 3400
AR Path="/5F8DD708/62CEF982" Ref="Q?"  Part="1" 
AR Path="/5FA975DA/62CEF982" Ref="Q?"  Part="1" 
AR Path="/5FA97622/62CEF982" Ref="Q?"  Part="1" 
AR Path="/62A8FB07/62CEF982" Ref="Q?"  Part="1" 
AR Path="/624D4519/62CEF982" Ref="Q12"  Part="1" 
F 0 "Q12" H 8750 3450 50  0000 L CNN
F 1 "BSS138" H 8750 3350 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9350 3325 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/BS/BSS138.pdf" H 9150 3400 50  0001 L CNN
	1    9150 3400
	1    0    0    1   
$EndComp
Text Notes 10950 2700 2    79   ~ 16
ENCODER (A/B/Z/HOME) LEVEL SHIFTERS
Wire Wire Line
	7950 1050 7950 1350
Connection ~ 7950 1350
$Comp
L Connector_Generic:Conn_01x10 J?
U 1 1 62D9E0CF
P 2500 7000
AR Path="/5F8DD708/62D9E0CF" Ref="J?"  Part="1" 
AR Path="/5FA975DA/62D9E0CF" Ref="J?"  Part="1" 
AR Path="/5FA97622/62D9E0CF" Ref="J?"  Part="1" 
AR Path="/62A8FB07/62D9E0CF" Ref="J?"  Part="1" 
AR Path="/624D4519/62D9E0CF" Ref="J1"  Part="1" 
F 0 "J1" H 2650 6950 50  0000 C CNN
F 1 "Conn_01x10" H 2300 6350 50  0000 C CNN
F 2 "Kona1:StrutConn" H 2500 7000 50  0001 C CNN
F 3 "~" H 2500 7000 50  0001 C CNN
	1    2500 7000
	-1   0    0    -1  
$EndComp
Text GLabel 3050 6800 2    50   UnSpc ~ 0
+5V
Text GLabel 3050 6950 2    50   UnSpc ~ 0
ENC2_A
Text GLabel 3050 7100 2    50   UnSpc ~ 0
ENC2_B
$Comp
L Device:R R?
U 1 1 62D9E0D8
P 3000 7500
AR Path="/5F8DD708/62D9E0D8" Ref="R?"  Part="1" 
AR Path="/5FA975DA/62D9E0D8" Ref="R?"  Part="1" 
AR Path="/5FA97622/62D9E0D8" Ref="R?"  Part="1" 
AR Path="/62A8FB07/62D9E0D8" Ref="R?"  Part="1" 
AR Path="/624D4519/62D9E0D8" Ref="R25"  Part="1" 
F 0 "R25" V 3100 7450 50  0000 C CNN
F 1 "120ohms 1/4W" V 3100 7950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2930 7500 50  0001 C CNN
F 3 "~" H 3000 7500 50  0001 C CNN
	1    3000 7500
	0    1    1    0   
$EndComp
Text GLabel 3300 7500 2    50   UnSpc ~ 0
+5V
Wire Wire Line
	2700 6700 2800 6700
Wire Wire Line
	2800 6700 2800 6500
Wire Wire Line
	2800 6500 3050 6500
Wire Wire Line
	2700 6800 2850 6800
Wire Wire Line
	2850 6800 2850 6650
Wire Wire Line
	2850 6650 3050 6650
Wire Wire Line
	2700 6900 2900 6900
Wire Wire Line
	2900 6900 2900 6800
Wire Wire Line
	2900 6800 3050 6800
Wire Wire Line
	2700 7000 2950 7000
Wire Wire Line
	2950 7000 2950 6950
Wire Wire Line
	2950 6950 3050 6950
Wire Wire Line
	2700 7100 3050 7100
Wire Wire Line
	2700 7200 2950 7200
Wire Wire Line
	2950 7200 2950 7250
Wire Wire Line
	2950 7250 3050 7250
Text GLabel 3050 7250 2    50   UnSpc ~ 0
ENC2_INDEX
Text GLabel 3050 6650 2    50   UnSpc ~ 0
ENC2_HOME
Text GLabel 3050 6500 2    50   UnSpc ~ 0
ENC2_MTR2
Wire Wire Line
	2750 6600 2700 6600
Wire Wire Line
	2700 7300 2900 7300
Wire Wire Line
	2900 7300 2900 7400
Wire Wire Line
	2700 7400 2850 7400
Text Notes 900  7450 0    50   ~ 10
Connections to Actuator\n1. Common (A)\n2.  Motor 2 (H)\n3.  Home (C)\n4.  +5V (D)\n5.  A (E)\n6.  B (F)\n7.  Index Strobe (G)\n8.  Motor 1 (B)\n9.  +5V LED (J)\n10. NC
$Comp
L power:GND #PWR?
U 1 1 62D9E130
P 2200 6550
AR Path="/5F8DD708/62D9E130" Ref="#PWR?"  Part="1" 
AR Path="/5FA975DA/62D9E130" Ref="#PWR?"  Part="1" 
AR Path="/5FA97622/62D9E130" Ref="#PWR?"  Part="1" 
AR Path="/62A8FB07/62D9E130" Ref="#PWR?"  Part="1" 
AR Path="/624D4519/62D9E130" Ref="#PWR0152"  Part="1" 
F 0 "#PWR0152" H 2200 6300 50  0001 C CNN
F 1 "GND" H 2100 6550 50  0000 C CNN
F 2 "" H 2200 6550 50  0001 C CNN
F 3 "" H 2200 6550 50  0001 C CNN
	1    2200 6550
	1    0    0    -1  
$EndComp
Text Notes 2000 7650 2    79   ~ 16
ACTUATOR ENCODER
Wire Wire Line
	1650 3000 1650 2950
Connection ~ 1650 2950
Wire Wire Line
	3400 3000 3400 2950
Connection ~ 3400 2950
Wire Wire Line
	2200 6550 2200 6450
Wire Wire Line
	2200 6450 2750 6450
Wire Wire Line
	2750 6450 2750 6600
Wire Wire Line
	2850 7400 2850 7500
Text GLabel 7150 2150 2    50   UnSpc ~ 0
ENC2_MTR1
Text GLabel 3300 7400 2    50   UnSpc ~ 0
ENC2_MTR1
Text GLabel 8900 1050 2    50   Input ~ 0
ENC2_MTR2
$Comp
L Kona_Parts:IRFD110 Q10
U 1 1 626A675D
P 7000 1000
F 0 "Q10" H 7158 446 50  0000 L CNN
F 1 "IRFD110" H 7158 355 50  0000 L CNN
F 2 "Package_DIP:DIP-4_W7.62mm_LongPads" H 7000 1000 50  0001 C CNN
F 3 "" H 7000 1000 50  0001 C CNN
	1    7000 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 1400 7100 1350
Connection ~ 7100 1350
Wire Wire Line
	7100 1350 7000 1350
Wire Wire Line
	6350 1600 6750 1600
$Comp
L Kona_Parts:IRFD9102 Q11
U 1 1 626E741C
P 7000 3100
F 0 "Q11" H 7158 2554 50  0000 L CNN
F 1 "IRFD9102" H 7158 2645 50  0000 L CNN
F 2 "Package_DIP:DIP-4_W7.62mm_LongPads" H 7000 3100 50  0001 C CNN
F 3 "" H 7000 3100 50  0001 C CNN
	1    7000 3100
	1    0    0    1   
$EndComp
Wire Wire Line
	7100 2800 7100 3050
Wire Wire Line
	7100 3050 7000 3050
Connection ~ 7000 3050
Wire Wire Line
	7000 3050 7000 2800
$Comp
L power:+3V3 #PWR0176
U 1 1 6271326D
P 8700 3100
F 0 "#PWR0176" H 8700 2950 50  0001 C CNN
F 1 "+3V3" H 8715 3273 50  0000 C CNN
F 2 "" H 8700 3100 50  0001 C CNN
F 3 "" H 8700 3100 50  0001 C CNN
	1    8700 3100
	1    0    0    -1  
$EndComp
Connection ~ 8700 3100
Wire Wire Line
	8350 3600 8350 3700
Wire Wire Line
	8350 3700 8600 3700
Connection ~ 8600 3700
$Comp
L Interface_Expansion:PCF8574ATS U13
U 1 1 6272F083
P 7150 5050
F 0 "U13" H 6800 5900 50  0000 C CNN
F 1 "PCF8574ATS" H 6800 5750 50  0000 C CNN
F 2 "Package_SO:SSOP-20_4.4x6.5mm_P0.65mm" H 7150 5050 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/PCF8574_PCF8574A.pdf" H 7150 5050 50  0001 C CNN
	1    7150 5050
	1    0    0    -1  
$EndComp
Text GLabel 6350 4650 0    50   Input ~ 0
I2C_SCL
Text GLabel 6350 4750 0    50   Input ~ 0
I2C_SDA
$Comp
L power:+3V3 #PWR0178
U 1 1 6273088E
P 7150 4200
F 0 "#PWR0178" H 7150 4050 50  0001 C CNN
F 1 "+3V3" H 7165 4373 50  0000 C CNN
F 2 "" H 7150 4200 50  0001 C CNN
F 3 "" H 7150 4200 50  0001 C CNN
	1    7150 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0179
U 1 1 62730BC4
P 7150 5900
F 0 "#PWR0179" H 7150 5650 50  0001 C CNN
F 1 "GND" H 7155 5727 50  0000 C CNN
F 2 "" H 7150 5900 50  0001 C CNN
F 3 "" H 7150 5900 50  0001 C CNN
	1    7150 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 5750 7150 5900
$Comp
L power:GND #PWR0180
U 1 1 62744223
P 6450 5900
F 0 "#PWR0180" H 6450 5650 50  0001 C CNN
F 1 "GND" H 6455 5727 50  0000 C CNN
F 2 "" H 6450 5900 50  0001 C CNN
F 3 "" H 6450 5900 50  0001 C CNN
	1    6450 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 4950 6450 4950
Wire Wire Line
	6450 4950 6450 5050
Wire Wire Line
	6650 5050 6450 5050
Connection ~ 6450 5050
Wire Wire Line
	6450 5050 6450 5150
Wire Wire Line
	6650 5150 6450 5150
Connection ~ 6450 5150
Wire Wire Line
	6450 5150 6450 5900
Wire Wire Line
	6650 4650 6350 4650
Wire Wire Line
	6650 4750 6350 4750
Wire Wire Line
	7150 4350 7150 4250
Text GLabel 8000 4650 2    50   Input ~ 0
GALIL_PE0
Text GLabel 8000 4750 2    50   Input ~ 0
GALIL_PE1
Text GLabel 8000 4850 2    50   Input ~ 0
GALIL_PE2
Text GLabel 8000 4950 2    50   Input ~ 0
GALIL_PE3
Text GLabel 8000 5050 2    50   Input ~ 0
GALIL_PE4
Text GLabel 8000 5150 2    50   Input ~ 0
GALIL_PE5
Text GLabel 8000 5250 2    50   Input ~ 0
GALIL_PE6
Text GLabel 8000 5350 2    50   Input ~ 0
GALIL_PE7
Wire Wire Line
	8000 4650 7650 4650
Wire Wire Line
	8000 4750 7650 4750
Wire Wire Line
	8000 4850 7650 4850
Wire Wire Line
	8000 4950 7650 4950
Wire Wire Line
	8000 5050 7650 5050
Wire Wire Line
	8000 5150 7650 5150
Wire Wire Line
	8000 5250 7650 5250
Wire Wire Line
	8000 5350 7650 5350
$Comp
L Device:C C?
U 1 1 62867FC9
P 7600 4250
AR Path="/5F8DD708/62867FC9" Ref="C?"  Part="1" 
AR Path="/5FA975DA/62867FC9" Ref="C?"  Part="1" 
AR Path="/5FA97622/62867FC9" Ref="C?"  Part="1" 
AR Path="/62A8FB07/62867FC9" Ref="C?"  Part="1" 
AR Path="/624D4519/62867FC9" Ref="C24"  Part="1" 
F 0 "C24" V 7852 4250 50  0000 C CNN
F 1 "C" V 7761 4250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 7638 4100 50  0001 C CNN
F 3 "~" H 7600 4250 50  0001 C CNN
	1    7600 4250
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0181
U 1 1 628682CE
P 7900 4350
F 0 "#PWR0181" H 7900 4100 50  0001 C CNN
F 1 "GND" H 7905 4177 50  0000 C CNN
F 2 "" H 7900 4350 50  0001 C CNN
F 3 "" H 7900 4350 50  0001 C CNN
	1    7900 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 4250 7900 4350
Wire Wire Line
	7900 4250 7750 4250
Wire Wire Line
	7450 4250 7150 4250
Connection ~ 7150 4250
Wire Wire Line
	7150 4250 7150 4200
Wire Wire Line
	1300 2350 2000 2350
Wire Wire Line
	2000 2050 1350 2050
Text Notes 8600 6900 2    79   ~ 16
GALIL MOTOR DRIVER
$Comp
L Connector:TestPoint GND?
U 1 1 631F41AD
P 1500 1250
AR Path="/624DFB62/631F41AD" Ref="GND?"  Part="1" 
AR Path="/624D4519/631F41AD" Ref="MC1"  Part="1" 
F 0 "MC1" H 1558 1368 50  0000 L CNN
F 1 "TestPoint" H 1558 1277 50  0000 L CNN
F 2 "TestPoint:TestPoint_Keystone_5019_Minature" H 1700 1250 50  0001 C CNN
F 3 "~" H 1700 1250 50  0001 C CNN
	1    1500 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 2450 1300 2450
$Comp
L Device:R R70
U 1 1 6284287A
P 10550 1600
F 0 "R70" H 10480 1554 50  0000 R CNN
F 1 "10K" H 10480 1645 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 10480 1600 50  0001 C CNN
F 3 "~" H 10550 1600 50  0001 C CNN
	1    10550 1600
	-1   0    0    1   
$EndComp
Wire Wire Line
	10550 1850 10550 1750
Wire Wire Line
	9700 1850 10550 1850
$Comp
L power:+3V3 #PWR0129
U 1 1 6285A350
P 9300 1350
F 0 "#PWR0129" H 9300 1200 50  0001 C CNN
F 1 "+3V3" H 9315 1523 50  0000 C CNN
F 2 "" H 9300 1350 50  0001 C CNN
F 3 "" H 9300 1350 50  0001 C CNN
	1    9300 1350
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0130
U 1 1 6285CA76
P 10550 1450
F 0 "#PWR0130" H 10550 1300 50  0001 C CNN
F 1 "+3V3" H 10565 1623 50  0000 C CNN
F 2 "" H 10550 1450 50  0001 C CNN
F 3 "" H 10550 1450 50  0001 C CNN
	1    10550 1450
	1    0    0    -1  
$EndComp
Text Notes 9450 1200 0    50   Italic 10
No Cypress3V3
Text Notes 9800 1850 0    50   Italic 10
I2C same ADDR
$Comp
L power:+5V #PWR0132
U 1 1 62B1780F
P 8350 3600
F 0 "#PWR0132" H 8350 3450 50  0001 C CNN
F 1 "+5V" H 8365 3773 50  0000 C CNN
F 2 "" H 8350 3600 50  0001 C CNN
F 3 "" H 8350 3600 50  0001 C CNN
	1    8350 3600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0134
U 1 1 62B18060
P 2250 3350
F 0 "#PWR0134" H 2250 3200 50  0001 C CNN
F 1 "+5V" H 2265 3523 50  0000 C CNN
F 2 "" H 2250 3350 50  0001 C CNN
F 3 "" H 2250 3350 50  0001 C CNN
	1    2250 3350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0136
U 1 1 62B18B26
P 4850 3350
F 0 "#PWR0136" H 4850 3200 50  0001 C CNN
F 1 "+5V" H 4865 3523 50  0000 C CNN
F 2 "" H 4850 3350 50  0001 C CNN
F 3 "" H 4850 3350 50  0001 C CNN
	1    4850 3350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0138
U 1 1 62B19241
P 2250 4100
F 0 "#PWR0138" H 2250 3950 50  0001 C CNN
F 1 "+5V" H 2265 4273 50  0000 C CNN
F 2 "" H 2250 4100 50  0001 C CNN
F 3 "" H 2250 4100 50  0001 C CNN
	1    2250 4100
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0140
U 1 1 62B1A7B5
P 4850 4100
F 0 "#PWR0140" H 4850 3950 50  0001 C CNN
F 1 "+5V" H 4865 4273 50  0000 C CNN
F 2 "" H 4850 4100 50  0001 C CNN
F 3 "" H 4850 4100 50  0001 C CNN
	1    4850 4100
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0142
U 1 1 62B1BC06
P 2250 4850
F 0 "#PWR0142" H 2250 4700 50  0001 C CNN
F 1 "+5V" H 2265 5023 50  0000 C CNN
F 2 "" H 2250 4850 50  0001 C CNN
F 3 "" H 2250 4850 50  0001 C CNN
	1    2250 4850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0144
U 1 1 62B1CF7E
P 4850 4850
F 0 "#PWR0144" H 4850 4700 50  0001 C CNN
F 1 "+5V" H 4865 5023 50  0000 C CNN
F 2 "" H 4850 4850 50  0001 C CNN
F 3 "" H 4850 4850 50  0001 C CNN
	1    4850 4850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0170
U 1 1 62B1D963
P 4850 5650
F 0 "#PWR0170" H 4850 5500 50  0001 C CNN
F 1 "+5V" H 4865 5823 50  0000 C CNN
F 2 "" H 4850 5650 50  0001 C CNN
F 3 "" H 4850 5650 50  0001 C CNN
	1    4850 5650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0173
U 1 1 62B1DF36
P 2300 5650
F 0 "#PWR0173" H 2300 5500 50  0001 C CNN
F 1 "+5V" H 2315 5823 50  0000 C CNN
F 2 "" H 2300 5650 50  0001 C CNN
F 3 "" H 2300 5650 50  0001 C CNN
	1    2300 5650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0177
U 1 1 62B1E82D
P 3000 1000
F 0 "#PWR0177" H 3000 850 50  0001 C CNN
F 1 "+5V" H 3015 1173 50  0000 C CNN
F 2 "" H 3000 1000 50  0001 C CNN
F 3 "" H 3000 1000 50  0001 C CNN
	1    3000 1000
	1    0    0    -1  
$EndComp
Connection ~ 3000 1000
$Comp
L Transistor_FET:BSS138 Q25
U 1 1 6298E29A
P 5200 6700
F 0 "Q25" V 5449 6700 50  0000 C CNN
F 1 "BSS138" V 5540 6700 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5400 6625 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 5200 6700 50  0001 L CNN
	1    5200 6700
	0    1    1    0   
$EndComp
$Comp
L Device:R R74
U 1 1 6298E2A0
P 4750 6600
F 0 "R74" H 4820 6646 50  0000 L CNN
F 1 "R" H 4820 6555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4680 6600 50  0001 C CNN
F 3 "~" H 4750 6600 50  0001 C CNN
	1    4750 6600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R75
U 1 1 6298E2A6
P 5600 6600
F 0 "R75" H 5670 6646 50  0000 L CNN
F 1 "R" H 5670 6555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5530 6600 50  0001 C CNN
F 3 "~" H 5600 6600 50  0001 C CNN
	1    5600 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 6800 4750 6800
Wire Wire Line
	4750 6800 4750 6750
Wire Wire Line
	5400 6800 5600 6800
Wire Wire Line
	5600 6800 5600 6750
$Comp
L power:+3V3 #PWR0203
U 1 1 6298E2B0
P 4750 6400
F 0 "#PWR0203" H 4750 6250 50  0001 C CNN
F 1 "+3V3" H 4765 6573 50  0000 C CNN
F 2 "" H 4750 6400 50  0001 C CNN
F 3 "" H 4750 6400 50  0001 C CNN
	1    4750 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 6450 4750 6400
Wire Wire Line
	5200 6500 5200 6450
Wire Wire Line
	5200 6450 4750 6450
Connection ~ 4750 6450
Text GLabel 4550 6800 0    50   Input ~ 0
GALIL_ERR_FLG
Wire Wire Line
	4750 6800 4550 6800
Connection ~ 4750 6800
$Comp
L power:+5V #PWR0204
U 1 1 6298E2C0
P 5600 6450
F 0 "#PWR0204" H 5600 6300 50  0001 C CNN
F 1 "+5V" H 5615 6623 50  0000 C CNN
F 2 "" H 5600 6450 50  0001 C CNN
F 3 "" H 5600 6450 50  0001 C CNN
	1    5600 6450
	1    0    0    -1  
$EndComp
Text Notes 7600 6300 2    79   ~ 16
I2C ADDR = 0x70
Text GLabel 1300 1650 0    50   Input ~ 0
GALIL_ERR_FLG_HV
Text GLabel 5850 6800 2    50   Input ~ 0
GALIL_ERR_FLG_HV
Wire Wire Line
	5850 6800 5600 6800
Connection ~ 5600 6800
Wire Wire Line
	2000 1750 1400 1750
Wire Wire Line
	1400 1750 1400 1650
Wire Wire Line
	1400 1650 1300 1650
Wire Wire Line
	3300 7500 3150 7500
Wire Wire Line
	3300 7400 2900 7400
$Comp
L Device:R R76
U 1 1 62E08E00
P 650 2250
F 0 "R76" H 720 2296 50  0000 L CNN
F 1 "10K0" V 550 2150 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 580 2250 50  0001 C CNN
F 3 "~" H 650 2250 50  0001 C CNN
	1    650  2250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0205
U 1 1 62E095B2
P 650 2100
F 0 "#PWR0205" H 650 1950 50  0001 C CNN
F 1 "+5V" H 665 2273 50  0000 C CNN
F 2 "" H 650 2100 50  0001 C CNN
F 3 "" H 650 2100 50  0001 C CNN
	1    650  2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 2550 650  2550
Wire Wire Line
	650  2550 650  2400
$EndSCHEMATC

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
L MCU_Module:WeMos_D1_mini U1
U 1 1 60B1ABDB
P 2050 2800
F 0 "U1" H 2050 1911 50  0000 C CNN
F 1 "WeMos_D1_mini" H 2050 1820 50  0000 C CNN
F 2 "Module:WEMOS_D1_mini_light" H 2050 1650 50  0001 C CNN
F 3 "https://wiki.wemos.cc/products:d1:d1_mini#documentation" H 200 1650 50  0001 C CNN
	1    2050 2800
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0101
U 1 1 60B28C7D
P 1950 2000
F 0 "#PWR0101" H 1950 1850 50  0001 C CNN
F 1 "+5V" H 1965 2173 50  0000 C CNN
F 2 "" H 1950 2000 50  0001 C CNN
F 3 "" H 1950 2000 50  0001 C CNN
	1    1950 2000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 60B3828E
P 2050 3600
F 0 "#PWR0102" H 2050 3350 50  0001 C CNN
F 1 "GND" H 2055 3427 50  0000 C CNN
F 2 "" H 2050 3600 50  0001 C CNN
F 3 "" H 2050 3600 50  0001 C CNN
	1    2050 3600
	1    0    0    -1  
$EndComp
Text GLabel 2450 2500 2    50   Input ~ 0
scl
Text GLabel 2450 2600 2    50   Input ~ 0
sda
$Comp
L power:GND #PWR0106
U 1 1 60B432E9
P 2950 2800
F 0 "#PWR0106" H 2950 2550 50  0001 C CNN
F 1 "GND" V 2955 2672 50  0000 R CNN
F 2 "" H 2950 2800 50  0001 C CNN
F 3 "" H 2950 2800 50  0001 C CNN
	1    2950 2800
	0    -1   -1   0   
$EndComp
Text GLabel 2950 2900 2    50   Input ~ 0
scl
Text GLabel 2950 3000 2    50   Input ~ 0
sda
$Comp
L power:GND #PWR0107
U 1 1 60B45515
P 2950 3100
F 0 "#PWR0107" H 2950 2850 50  0001 C CNN
F 1 "GND" V 2955 2972 50  0000 R CNN
F 2 "" H 2950 3100 50  0001 C CNN
F 3 "" H 2950 3100 50  0001 C CNN
	1    2950 3100
	0    -1   -1   0   
$EndComp
$Comp
L LED:WS2812B D1
U 1 1 60B45FFC
P 3150 3850
F 0 "D1" H 3494 3896 50  0000 L CNN
F 1 "WS2812B" H 3494 3805 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 3200 3550 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 3250 3475 50  0001 L TNN
	1    3150 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 60B4A589
P 3150 3550
F 0 "#PWR0108" H 3150 3300 50  0001 C CNN
F 1 "GND" V 3155 3422 50  0000 R CNN
F 2 "" H 3150 3550 50  0001 C CNN
F 3 "" H 3150 3550 50  0001 C CNN
	1    3150 3550
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR0109
U 1 1 60B4EE1B
P 3150 4150
F 0 "#PWR0109" H 3150 4000 50  0001 C CNN
F 1 "+5V" H 3165 4323 50  0000 C CNN
F 2 "" H 3150 4150 50  0001 C CNN
F 3 "" H 3150 4150 50  0001 C CNN
	1    3150 4150
	-1   0    0    1   
$EndComp
Text GLabel 2850 3850 0    50   Input ~ 0
din
Text GLabel 2450 2800 2    50   Input ~ 0
din
$Comp
L power:+5V #PWR0105
U 1 1 60B432E3
P 2950 2700
F 0 "#PWR0105" H 2950 2550 50  0001 C CNN
F 1 "+5V" V 2965 2828 50  0000 L CNN
F 2 "" H 2950 2700 50  0001 C CNN
F 3 "" H 2950 2700 50  0001 C CNN
	1    2950 2700
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x08_Male J2
U 1 1 60B25397
P 2750 3000
F 0 "J2" H 2858 3481 50  0000 C CNN
F 1 "CCS811" H 2858 3390 50  0000 C CNN
F 2 "Monitor:CCS811" H 2750 3000 50  0001 C CNN
F 3 "~" H 2750 3000 50  0001 C CNN
	1    2750 3000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Male J1
U 1 1 60B1AB60
P 2750 2100
F 0 "J1" H 2858 2481 50  0000 C CNN
F 1 "BMP280" H 2858 2390 50  0000 C CNN
F 2 "Monitor:BMP280" H 2750 2100 50  0001 C CNN
F 3 "~" H 2750 2100 50  0001 C CNN
	1    2750 2100
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR01
U 1 1 60B1CACD
P 2950 1900
F 0 "#PWR01" H 2950 1750 50  0001 C CNN
F 1 "+3.3V" V 2965 2028 50  0000 L CNN
F 2 "" H 2950 1900 50  0001 C CNN
F 3 "" H 2950 1900 50  0001 C CNN
	1    2950 1900
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 60B1D47D
P 2950 2000
F 0 "#PWR02" H 2950 1750 50  0001 C CNN
F 1 "GND" V 2955 1872 50  0000 R CNN
F 2 "" H 2950 2000 50  0001 C CNN
F 3 "" H 2950 2000 50  0001 C CNN
	1    2950 2000
	0    -1   -1   0   
$EndComp
Text GLabel 2950 2100 2    50   Input ~ 0
scl
Text GLabel 2950 2200 2    50   Input ~ 0
sda
$EndSCHEMATC

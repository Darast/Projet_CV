#!/bin/bash

imd="test.png"

path=$1

## Log 1
echo "######### Log 1 #########"
log1[0]="log1/003-rgb.png"
log1[1]="log1/010-rgb.png"
log1[2]="log1/105-rgb.png"
log1[3]="log1/120-rgb.png"
log1[4]="log1/151-rgb.png"
log1[5]="log1/163-rgb.png"
log1_verite[0]="../data/verites/log1/003-rgb.png"
log1_verite[1]="../data/verites/log1/010-rgb.png"
log1_verite[2]="../data/verites/log1/105-rgb.png"
log1_verite[3]="../data/verites/log1/120-rgb.png"
log1_verite[4]="../data/verites/log1/151-rgb.png"
log1_verite[5]="../data/verites/log1/163-rgb.png"

for (( i = 0; i < 6; i++ )); do
	../build/terrain $path${log1[$i]} $imd 
	../build/difference $imd ${log1_verite[$i]}
done

## Log 2
echo "######### Log 2 #########"
log2[0]="log2/005-rgb.png"
log2[1]="log2/158-rgb.png"
log2[2]="log2/175-rgb.png"
log2_verite[0]="../data/verites/log2/005-rgb.png"
log2_verite[1]="../data/verites/log2/158-rgb.png"
log2_verite[2]="../data/verites/log2/175-rgb.png"

for (( i = 0; i < 3; i++ )); do
	../build/terrain $path${log2[$i]} $imd 
	../build/difference $imd ${log2_verite[$i]}
done

## Log 
echo "######### Log 3 #########"
log3[0]="log3/005-rgb.png"
log3[1]="log3/143-rgb.png"
log3_verite[0]="../data/verites/log3/005-rgb.png"
log3_verite[1]="../data/verites/log3/143-rgb.png"

for (( i = 0; i < 2; i++ )); do
	../build/terrain $path${log3[$i]} $imd 
	../build/difference $imd ${log3_verite[$i]}
done

## Log 
echo "######### Log 4 #########"
log4[0]="log4/21-rgb.png"
log4[1]="log4/46-rgb.png"
log4_verite[0]="../data/verites/log4/21-rgb.png"
log4_verite[1]="../data/verites/log4/46-rgb.png"

for (( i = 0; i < 2; i++ )); do
	../build/terrain $path${log4[$i]} $imd 
	../build/difference $imd ${log4_verite[$i]}
done
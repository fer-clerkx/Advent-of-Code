#!/bin/bash

readarray -t input < input/input01.txt

sum=0
for line in ${input[@]}; do
    readarray -t numbers < <(echo "$line" | grep -o [0-9])
    sum=$(( $sum + "${numbers[0]}${numbers[-1]}" ))
done
echo "Solution 1: $sum"

number_dict=([1]=one \
             [2]=two \
             [3]=three \
             [4]=four \
             [5]=five \
             [6]=six \
             [7]=seven \
             [8]=eight \
             [9]=nine)
sum=0
for line in ${input[@]}; do
    for ((i=1; i<=9; i++)); do
        line=${line//${number_dict[$i]}/${number_dict[$i]}$i${number_dict[$i]}}
    done
    readarray -t numbers < <(echo "$line" | grep -o [0-9])
    sum=$(( $sum + "${numbers[0]}${numbers[-1]}" ))
done
echo "Solution 2: $sum"
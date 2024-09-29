#!/bin/bash

echo -n "Solution 1: " &&
    # Duplicate digit for lines with signle digit
    pcregrep -o1 -o2 "(\d.*\d|(\d))" input/input01.txt |
    pcregrep -o1 -o2 "(\d).*(\d)" |
    paste -sd+ | bc

echo -n "Solution 2: " && cat input/input01.txt |
    sed 's/one/one1one/g' |
    sed 's/two/two2two/g' |
    sed 's/three/three3three/g' |
    sed 's/four/four4four/g' |
    sed 's/five/five5five/g' |
    sed 's/six/six6six/g' |
    sed 's/seven/seven7seven/g' |
    sed 's/eight/eight8eight/g' |
    sed 's/nine/nine9nine/g' |
    pcregrep -o1 -o2 "(\d.*\d|(\d))" |
    pcregrep -o1 -o2 "(\d).*(\d)" |
    paste -sd+ | bc
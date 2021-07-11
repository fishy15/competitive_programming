#!/bin/zsh

sz=100
for ((i=1;;i++)); do
    echo "$i"
    ./gen "$i" "$sz" > input
    ./sol < input > output1
    ./brute < input > output2
    if (! diff output1 output2); then
        break
    fi
done

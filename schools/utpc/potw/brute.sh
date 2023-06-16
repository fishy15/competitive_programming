#!/bin/zsh

sz=5
for ((i=1;;i++)); do
    echo "$i"
    ./gen "$sz" "$i" > input
    ./sol < input > output1
    ./brute < input > output2
    if (! diff output1 output2); then
        break
    fi
done

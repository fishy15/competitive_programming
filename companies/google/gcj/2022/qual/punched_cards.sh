#!/bin/bash

read N

for ((t=1; t <= $N; t++)); do
    echo "Case #$t:"

    read -a words
    R=${words[0]}
    C=${words[1]}

    for ((r=0; r < $((2 * R + 1)); r++)); do
        for((c=0; c < $C; c++)); do
            if [ $r -lt 2 ] && [ $c == 0 ]; then
                echo -n ".."
            else
                if [ $(($r % 2)) == 0 ]; then
                    echo -n "+-"
                else
                    echo -n "|."
                fi
            fi
        done

        if [ $(($r % 2)) == 0 ]; then
            echo "+"
        else
            echo "|"
        fi
    done
done

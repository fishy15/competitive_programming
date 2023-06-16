#!/usr/local/bin/python3.9

import sys

def main():
    n = int(sys.stdin.readline())
    rolls = list(map(int, sys.stdin.readline().split()))

    count = [0] * 7
    for roll in rolls:
        count[roll] += 1

    for i in range(6, 0, -1):
        if count[i] == 1:
            print(rolls.index(i) + 1)
            return

    print('none')

if __name__ == '__main__':
    main()



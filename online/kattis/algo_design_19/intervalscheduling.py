#!/usr/local/bin/python3.9

import sys

def main():
    n = int(sys.stdin.readline())
    intervals = [list(map(int, sys.stdin.readline().split())) for _ in range(n)]
    intervals.sort(key=lambda pair: (pair[1], pair[0]))

    counter = 0
    end = 0

    for x, y in intervals:
        if end <= x:
            counter += 1
            end = y

    print(counter)

if __name__ == '__main__':
    main()

#!/usr/local/bin/python3.9

import sys

def solve(sides):
    sides.sort()
    if sides[0] ** 2 + sides[1] ** 2 == sides[2] ** 2:
        print('right')
    else:
        print('wrong')

def main():
    while True:
        line = list(map(int, sys.stdin.readline().split()))
        if line[0] == 0:
            break
        solve(line)

if __name__ == '__main__':
    main()

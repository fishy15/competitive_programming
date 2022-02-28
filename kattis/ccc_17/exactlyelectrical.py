#!/usr/local/bin/python3.9

import sys

def main():
    a, b = map(int, sys.stdin.readline().split())
    c, d = map(int, sys.stdin.readline().split())
    t = int(sys.stdin.readline())

    dist = abs(a - c) + abs(b - d)
    print('NY'[t >= dist and t % 2 == dist % 2])

if __name__ == '__main__':
    main()

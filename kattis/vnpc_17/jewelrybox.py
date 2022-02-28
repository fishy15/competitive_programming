#!/usr/local/bin/python3.9

import math
import sys

def solve():
    x, y = map(int, sys.stdin.readline().split())
    h = (4 * (x + y) - math.sqrt(16 * (x + y) ** 2 - 48 * x * y)) / 24
    v = (x - 2 * h) * (y - 2 * h) * h
    print(f'{v:.10f}')

def main():
    t = int(sys.stdin.readline())
    for _ in range(t):
        solve()

if __name__ == '__main__':
    main()

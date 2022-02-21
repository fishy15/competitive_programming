#!/usr/local/bin/python3.9

import itertools
import math
import sys

def main():
    x, y, x1, y1, x2, y2 = map(int, sys.stdin.readline().split())
    d = min(math.hypot(x - xn, y - yn) for xn, yn in itertools.product([x1, x2], [y1, y2]))

    if x1 <= x <= x2:
        d = min(d, abs(y - y1), abs(y - y2))

    if y1 <= y <= y2:
        d = min(d, abs(x - x1), abs(x - x2))

    print(d)

if __name__ == '__main__':
    main()

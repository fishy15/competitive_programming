#!/usr/local/bin/python3.9

import math
import sys

def main():
    n, d = map(int, sys.stdin.readline().split('/'))
    n -= d * 32
    n *= 5
    d *= 9

    g = math.gcd(n, d)
    n //= g
    d //= g

    print(f'{n}/{d}')

if __name__ == '__main__':
    main()

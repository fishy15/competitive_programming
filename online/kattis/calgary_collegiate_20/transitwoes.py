#!/usr/local/bin/python3.9

import sys

def main():
    s, t, n = map(int, sys.stdin.readline().split())
    d = list(map(int, sys.stdin.readline().split()))
    b = list(map(int, sys.stdin.readline().split()))
    c = list(map(int, sys.stdin.readline().split()))

    time = s
    for i in range(n):
        time += d[i]
        # rounds up to nearest multiple of c
        time = (time + c[i] - 1) // c[i] * c[i]
        time += b[i]

    time += d[n]
    print('yneos'[time > t::2])

if __name__ == '__main__':
    main()

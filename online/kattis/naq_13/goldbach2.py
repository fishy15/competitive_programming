#!/usr/local/bin/python3.9

import sys

def solve(sieve):
    x = int(sys.stdin.readline())

    ok = []
    for i in range(2, x // 2 + 1):
        if sieve[i] and sieve[x - i]:
            ok.append((i, x - i))

    print(f'{x} has {len(ok)} representation(s)')
    for a, b in ok:
        print(f'{a}+{b}')
    print()

def main():
    n = int(sys.stdin.readline())

    max = 32000
    sieve = [True] * (max + 1)
    sieve[0] = False
    sieve[1] = False

    for i in range(2, max + 1):
        if sieve[i]:
            for j in range(i * i, max + 1, i):
                sieve[j] = False

    for _ in range(n):
        solve(sieve)

if __name__ == '__main__':
    main()

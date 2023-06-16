#!/usr/local/bin/python3.9

import sys

def solve(len):
    a = [int(sys.stdin.readline()) for _ in range(len)]
    b = [int(sys.stdin.readline()) for _ in range(len)]

    match = dict()
    for x, y in zip(sorted(a), sorted(b)):
        match[x] = y

    for x in a:
        print(match[x])
    print()

def main():
    while True:
        len = int(sys.stdin.readline());
        if len == 0:
            break

        solve(len)

if __name__ == '__main__':
    main()

#!/usr/local/bin/python3.9

import sys

def solve(idx, line):
    e, m = map(int, line.split())
    for i in range(365 * 687):
        if (e + i) % 365 == 0 and (m + i) % 687 == 0:
            print(f'Case {idx + 1}: {i}')
            return

def main():
    lines = sys.stdin.readlines()
    for idx, line in enumerate(lines):
        solve(idx, line)

if __name__ == '__main__':
    main()

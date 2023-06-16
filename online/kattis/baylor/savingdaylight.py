#!/usr/local/bin/python3.9

import sys

def solve(line):
    line = line.split()
    h1, m1 = map(int, line[3].split(':'))
    h2, m2 = map(int, line[4].split(':'))

    h2 -= h1
    m2 -= m1

    if m2 < 0:
        m2 += 60
        h2 -= 1

    print(line[0], line[1], line[2], f'{h2} hours {m2} minutes')

def main():
    for line in sys.stdin.readlines():
        solve(line)

if __name__ == '__main__':
    main()

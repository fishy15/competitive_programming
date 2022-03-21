#!/usr/local/bin/python3.9

import sys

NONE = 0
INC = 1
DESC = 2

def solve(names):
    if names[0] < names[1]:
        ans = INC
    else:
        ans = DESC

    if len(names) > 2:
        rest = solve(names[1:])

        if rest != ans:
            ans = NONE

    return ans

def main():
    n = int(sys.stdin.readline())
    names = [sys.stdin.readline().strip() for _ in range(n)]

    res = solve(names)
    if res == NONE:
        print('NEITHER')
    elif res == INC:
        print('INCREASING')
    else:
        print('DECREASING')

if __name__ == '__main__':
    main()

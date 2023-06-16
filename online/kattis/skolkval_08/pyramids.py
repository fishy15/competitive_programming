#!/usr/local/bin/python3.9

import sys

def main():
    n = int(sys.stdin.readline())
    height = 1
    sum = 1

    while sum + (height + 2) ** 2 <= n:
        height += 2
        sum += height ** 2

    height = (height + 1) // 2
    print(height)

if __name__ == '__main__':
    main()

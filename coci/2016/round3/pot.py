#!/usr/local/bin/python3.9

import sys

def main():
    n = int(sys.stdin.readline())
    sum = 0
    for i in range(n):
        p = sys.stdin.readline().strip()
        num = int(p[:-1])
        pow = int(p[-1:])
        sum += num ** pow
    print(sum)

if __name__ == '__main__':
    main()

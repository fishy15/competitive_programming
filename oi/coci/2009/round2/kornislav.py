#!/usr/local/bin/python3.9

import sys

def main():
    l = list(map(int, sys.stdin.readline().split()))
    l.sort()
    print(l[0] * l[2])

if __name__ == '__main__':
    main()

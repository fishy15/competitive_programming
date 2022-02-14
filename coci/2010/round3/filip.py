#!/usr/local/bin/python3.9

import sys

def main():
    first, second = sys.stdin.readline().split()
    a = int(first[::-1])
    b = int(second[::-1])
    print(max(a, b))

if __name__ == '__main__':
    main()

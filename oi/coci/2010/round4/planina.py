#!/usr/local/bin/python3.9

import sys

def main():
    n = int(sys.stdin.readline())
    side = 2 ** n + 1
    print(side ** 2)

if __name__ == '__main__':
    main()

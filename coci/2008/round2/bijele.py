#!/usr/local/bin/python3.9

import sys

def main():
    intended = [1, 1, 2, 2, 2, 8]
    has = map(int, sys.stdin.readline().split())
    print(' '.join(str(intended[i] - x) for i, x in enumerate(has)))

if __name__ == '__main__':
    main()

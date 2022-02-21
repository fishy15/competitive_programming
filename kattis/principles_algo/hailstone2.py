#!/usr/local/bin/python3.9

import sys

def main():
    n = int(sys.stdin.readline())

    counter = 1
    while n != 1:
        if n % 2 == 0:
            n /= 2
        else:
            n = 3 * n + 1
        counter += 1

    print(counter)

if __name__ == '__main__':
    main()

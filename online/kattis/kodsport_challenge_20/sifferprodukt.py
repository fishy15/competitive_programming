#!/usr/local/bin/python3.9

import sys

def main():
    x = sys.stdin.readline().strip()

    while len(x) > 1:
        prod = 1

        for c in x:
            if c != '0':
                prod *= int(c)

        x = str(prod)

    print(x)

if __name__ == '__main__':
    main()

#!/usr/local/bin/python3.9

import sys

def solve(counter, len):
    names = [sys.stdin.readline().strip() for _ in range(len)]

    print(f'SET {counter}')

    if len == 1:
        print(names[0])
        return

    for name in names[::2]:
        print(name)

    end = len - 1 if len % 2 == 0 else len - 2

    for name in names[end::-2]:
        print(name)

def main():
    counter = 1
    while True:
        len = int(sys.stdin.readline())
        if len == 0:
            break

        solve(counter, len)
        counter += 1

if __name__ == '__main__':
    main()

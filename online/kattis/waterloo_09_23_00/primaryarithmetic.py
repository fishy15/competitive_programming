#!/usr/local/bin/python3.9

import sys

def count_carry(a, b, c=0):
    if a == 0 and b == 0:
        return 0

    dig = a % 10 + b % 10 + c
    if dig >= 10:
        return 1 + count_carry(a // 10, b // 10, 1)
    else:
        return count_carry(a // 10, b // 10, 0)

def main():
    while True:
        a, b = map(int, sys.stdin.readline().split())
        if a == 0 and b == 0:
            break

        carry = count_carry(a, b)
        if carry == 0:
            print('No carry operation.')
        elif carry == 1:
            print('1 carry operation.')
        else:
            print(f'{carry} carry operations.')

if __name__ == '__main__':
    main()

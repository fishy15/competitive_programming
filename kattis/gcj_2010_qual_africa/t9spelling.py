#!/usr/local/bin/python3.9

import sys

def main():
    n = int(sys.stdin.readline())

    numbers = [
        ['', ' '],
        [],
        ['', 'a', 'b', 'c'],
        ['', 'd', 'e', 'f'],
        ['', 'g', 'h', 'i'],
        ['', 'j', 'k', 'l'],
        ['', 'm', 'n', 'o'],
        ['', 'p', 'q', 'r', 's'],
        ['', 't', 'u', 'v'],
        ['', 'w', 'x', 'y', 'z']
    ]

    for i in range(1, n + 1):
        s = sys.stdin.readline()
        result = ''

        prev = ''
        for c in s:
            for j in range(10):
                if c in numbers[j]:
                    num = str(j)
                    repeat = numbers[j].index(c)

                    if num == prev:
                        result += ' '

                    result += num * repeat
                    prev = num

        print(f'Case #{i}: {result}')

if __name__ == '__main__':
    main()

#!/usr/local/bin/python3.9

import sys

def main():
    line = sys.stdin.readline().split()
    n = int(line[0])
    b = line[1]

    dominant = {'A': 11, 'K': 4, 'Q': 3, 'J': 20, 'T': 10, '9': 14, '8': 0, '7': 0}
    non_dominant = {'A': 11, 'K': 4, 'Q': 3, 'J': 2, 'T': 10, '9': 0, '8': 0, '7': 0}

    points = 0
    for i in range(4 * n):
        line = sys.stdin.readline()
        if line[1] == b:
            points += dominant[line[0]]
        else:
            points += non_dominant[line[0]]

    print(points)

if __name__ == '__main__':
    main()


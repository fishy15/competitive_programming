#!/usr/local/bin/python3.9

import sys

def main():
    cards = sys.stdin.readline().split()
    count = dict()

    for card in cards:
        rank = card[0]
        if rank in count:
            count[rank] += 1
        else:
            count[rank] = 1

    print(max(count.values()))

if __name__ == '__main__':
    main()

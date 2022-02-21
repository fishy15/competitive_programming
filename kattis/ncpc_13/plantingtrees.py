#!/usr/local/bin/python3.9

import sys

def main():
    n = int(sys.stdin.readline())
    nums = [int(x) for x in sys.stdin.readline().split()]
    nums.sort(reverse=True)

    print(max(i + x + 2 for i, x in enumerate(nums)))

if __name__ == '__main__':
    main()

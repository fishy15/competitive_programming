#!/usr/local/bin/python3.9

import sys

def solve(line):
    nums = list(map(int, line.split()))
    print(sum(nums) // 2)

def main():
    for line in sys.stdin.readlines():
        solve(line)

if __name__ == '__main__':
    main()

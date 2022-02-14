#!/usr/local/bin/python3.9

import sys

def solve():
    nums = sys.stdin.readline().split()
    k = int(nums[0])
    nums = nums[1:]
    print(sum(int(x) for x in nums) - k + 1)

def main():
    n = int(sys.stdin.readline())
    for i in range(n):
        solve()

if __name__ == '__main__':
    main()


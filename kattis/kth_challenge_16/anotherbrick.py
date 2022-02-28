#!/usr/local/bin/python3.9

import sys

def main():
    h, w, n = map(int, sys.stdin.readline().split())
    nums = list(map(int, sys.stdin.readline().split()))

    cur_width = 0
    cur_height = 0

    for brick in nums:
        cur_width += brick
        
        if cur_width == w:
            cur_height += 1
            cur_width = 0
            if cur_height == h:
                print('YES')
                return
        elif cur_width > w:
            print('NO')
            return

    print('NO')
    return

if __name__ == '__main__':
    main()

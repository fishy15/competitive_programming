#!/usr/local/bin/python3.9

import sys

# gets the list of numbers that fits the pattern, exactly cnt digits
def get_list(dig, cnt):
    if cnt == 0:
        return [0]

    prev = get_list(dig, cnt - 1)
    nums = [dig * 10 ** (cnt - 1) + x for x in prev]

    if dig == 1:
        nums.extend(get_list(2, cnt))
        nums.extend(get_list(4, cnt))
    elif dig == 2:
        nums.extend(get_list(3, cnt))
        nums.extend(get_list(5, cnt))
    elif dig == 3:
        nums.extend(get_list(6, cnt))
    elif dig == 4:
        nums.extend(get_list(5, cnt))
        nums.extend(get_list(7, cnt))
    elif dig == 5:
        nums.extend(get_list(6, cnt))
        nums.extend(get_list(8, cnt))
    elif dig == 6:
        nums.extend(get_list(9, cnt))
    elif dig == 7:
        nums.extend(get_list(8, cnt))
    elif dig == 8:
        nums.extend(get_list(9, cnt))
        nums.extend(get_list(0, cnt))

    return nums

def main():
    n = int(sys.stdin.readline())

    nums = get_list(1, 3) + get_list(1, 2) + get_list(1, 1)

    for _ in range(n):
        x = int(sys.stdin.readline())
        ans = 0

        for num in nums:
            if abs(x - num) < abs(x - ans):
                ans = num

        print(ans)

if __name__ == '__main__':
    main()

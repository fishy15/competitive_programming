#!/usr/local/bin/python3.9

import sys

def main():
    n, m = map(int, sys.stdin.readline().split())
    cnt = [0] * (n + m + 1)

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            cnt[i + j] += 1

    m = max(cnt)
    print('\n'.join(str(i) for i in range(len(cnt)) if cnt[i] == m))

if __name__ == '__main__':
    main()

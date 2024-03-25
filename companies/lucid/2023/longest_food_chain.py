import sys
from functools import lru_cache

input = sys.stdin.readline

def main():
    n = int(input())

    child = {}
    for _ in range(n):
        line = input().strip()
        pred, prey = line.split(' <- ')
        prey = prey.split(', ')
        child[pred] = prey

    @lru_cache
    def find(x):
        if x not in child:
            return 1
        ans = 0
        for y in child[x]:
            ans = max(ans, find(y))
        return ans + 1

    print(max(find(x) for x in child.keys()))

if __name__ == '__main__':
    main()

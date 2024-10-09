import sys

cache = {1: 1}

def collatz(x):
    if x in cache:
        return cache[x]
    else:
        nxt = x // 2 if x % 2 == 0 else 3 * x + 1
        cache[x] = collatz(nxt) + 1
        return cache[x]


def main():
    for line in sys.stdin.readlines():
        line = line.strip()
        if line:
            a, b = map(int, line.split())
            i, j = min(a, b), max(a, b)
            ans = max(collatz(x) for x in range(i, j+1))
            print(a, b, ans)

if __name__ == '__main__':
    main()

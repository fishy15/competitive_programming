def solve():
    n = int(input())
    cnt = {}
    for x in map(int, input().split()):
        cnt[x] = cnt.get(x, 0) + 1

    N = 1 << n
    pairs = N * (N - 1) // 2
    for _, c in cnt.items():
        pairs -= c * (c - 1) // 2

    print(pairs * (1 << (n - 1)))

for _ in range(int(input())):
    solve()

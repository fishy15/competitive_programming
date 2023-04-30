def calc(d, n):
    best = [0]
    for i in range(1, n + 1):
        ok = 100000000000
        for x in d:
                if i >= x:
                        ok = min(ok, best[i - x])
        best += [ok + 1]

    for x in d:
        print(end=f'{x}: ')
        for i in range(1, n + 1):
                if i >= x:
                        print(best[i - x], end = ' ')
                else:
                        print('x', end=' ')
        print()

n = int(input())
nums = list(map(int, input().split()))
calc(nums, n)


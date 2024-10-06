def solve():
    n, d = map(int, input().split())
    cur = 1
    ans = 0
    while cur < n:
        cur *= d + 1
        ans += 1
    print(ans)

def main():
    t = int(input())
    for _ in range(t):
        solve()

if __name__ == '__main__':
    main()

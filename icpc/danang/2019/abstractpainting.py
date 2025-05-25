MOD = 10**9 + 7
t = int(input())
for _ in range(t):
    r, c = map(int, input().split())
    ans = pow(3, r+c, MOD) * pow(2, r*c, MOD) % MOD
    print(ans)

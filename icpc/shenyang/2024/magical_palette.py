from math import gcd

def solve():
    n, m = map(int, input().split())
    a, b = min(n, m), max(n, m)
    if gcd(n, m) > 1:
        print('No')
    else:
        print('Yes')
        xs = [x % (n*m) for x in range(1, a+1)]
        for i, x in enumerate(xs):
            while gcd(x, b) > 1:
                x = (a + x) % (n * m)
            xs[i] = x
        ys = [y % (n*m) for y in range(1, n*m+1, a)]
        if n > m:
            xs, ys = ys, xs
        print(*[x % (n*m) for x in xs])
        print(*[y % (n*m) for y in ys])

def main():
    for _ in range(int(input())):
        solve()

if __name__ == '__main__':
    main()

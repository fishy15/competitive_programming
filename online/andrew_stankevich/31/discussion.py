from math import ceil, floor, log10

def choose(n: int, k: int):
    num = 1
    den = 1
    for i in range(k):
        num *= n - i
        den *= i + 1
    return num // den

QUIT = 1
CONTINUE = 2
VALID = 3

'''
(n/k)^k <= nCk <= (en/k)^k
k <= n <= k z^(1/k)
'''
def check(z: int, k: int, last_r: int) -> tuple[int, int]:
    lg = log10(z)
    lower: int = 10 ** max(0, int(floor(lg / k)))
    higher: int = k * 10 ** (int(ceil(lg / k)))
    l = max(2*k, lower)
    r = min(last_r, higher)
    if r < l:
        return (QUIT, -1)
    while l <= r:
        m = (l + r) // 2
        res = choose(m, k)
        if res < z:
            l = m + 1
        elif res == z:
            return (VALID, m)
        else:
            r = m - 1
    return (CONTINUE, r)

def solve(z: int) -> int:
    ans = z
    k = 2
    last_r = ans
    while True:
        typ, res = check(z, k, last_r)
        print(z, k, last_r, typ, res)
        if typ == QUIT:
            break
        elif typ == CONTINUE:
            last_r = res
        else:
            ans = res
            last_r = res
        k += 1
    return ans

def main() -> None:
    with open('discuss.in', 'r') as f:
        z = int(f.readline())
    with open('discuss.out', 'w') as f:
        print(solve(z), file=f)

if __name__ == '__main__':
    main()

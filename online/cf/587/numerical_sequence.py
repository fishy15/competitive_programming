from functools import lru_cache

def tri(x: int) -> int:
    return x * (x + 1) // 2

@lru_cache(maxsize=None)
def pow10(e) -> int:
    if e < 0:
        return 0
    elif e == 0:
        return 1
    return 10 * pow10(e - 1)

# block -- 1234...x
@lru_cache(maxsize=None)
def block_size(x: int) -> int:
    e = 1
    pow10 = 10
    ans = 0
    while pow10 <= x:
        ans += e * (pow10 - pow10 // 10)
        e += 1
        pow10 *= 10

    ans += (x - (pow10 // 10) + 1) * e
    return ans

# max size including all digits up to a point
@lru_cache(maxsize=None)
def cum_block_size_digs(digits: int) -> int:
    if digits == 0:
        return 0

    base = 0 if digits == 1 else block_size(pow10(digits - 1) - 1)
    cnt = pow10(digits) - pow10(digits - 1)
    return cum_block_size_digs(digits - 1) + (base * cnt) + digits * tri(cnt)

@lru_cache(maxsize=None)
def cum_block_size(x: int) -> int:
    digits = len(str(x))
    
    base = 0 if digits == 1 else block_size(pow10(digits - 1) - 1)
    cnt = x - pow10(digits - 1) + 1
    return cum_block_size_digs(digits - 1) + (base * cnt) + digits * tri(cnt)

def solve(k: int) -> int:
    lo = 0
    hi = int(1e18)
    ok = -1
    while lo <= hi:
        m = (lo + hi) // 2
        if cum_block_size(m) <= k:
            ok = m
            lo = m + 1
        else:
            hi = m - 1

    assert ok != -1
    k -= cum_block_size(ok)

    # now, k is index within that block
    lo = 0
    hi = int(1e18)
    ok = -1
    while lo <= hi:
        m = (lo + hi) // 2
        if block_size(m) <= k:
            ok = m
            lo = m + 1
        else:
            hi = m - 1

    assert ok != -1
    k -= block_size(ok)

    # now, k is index within ok+1
    return int(str(ok+1)[k])

def main():
    q = int(input())
    for _ in range(q):
        k = int(input()) - 1
        print(solve(k))

if __name__ == '__main__':
    main()

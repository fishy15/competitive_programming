def solve(s, end):
    x = end
    for c in s:
        if c == 'O':
            if x == 1 or (x - 1) % 3 != 0:
                return None
            x = (x - 1) // 3
        else:
            x *= 2
    return x

def check(s, start, end):
    x = start
    for c in s:
        if c == 'E' and x % 2 == 0:
            # if we are a power of two
            if x & (x - 1) == 0:
                return False
            x //= 2
        elif c == 'O' and x % 2 == 1:
            if x == 1:
                return False
            x = 3 * x + 1
        else:
            return False
    return x == end

def main():
    s = input()

    for c in s:
        if c not in 'OE':
            print('INVALID')
            return

    if s[-1] != 'O' or 'OO' in s:
        print('INVALID')
        return

    rev = s[::-1]

    ans = None
    end = 1
    while end <= 2**90:
        res = solve(rev, end)
        if res is not None and check(s, res, end):
            if ans is None:
                ans = res
            else:
                ans = min(ans, res)
        end *= 2

    if ans is None:
        print('INVALID')
    else:
        print(ans)

if __name__ == '__main__':
    main()

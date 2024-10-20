def fact(n):
    ans = 1
    for x in range(1, n+1):
        ans *= x
    return ans

def steps(n, m):
    num = fact(n + m)    
    denom = fact(n) * fact(m)
    return num // denom

def verts(n, m):
    ans = 0
    for i in range(0, m):
        for j in range(i, m):
            for k in range(0, m):
                for l in range(k, m):
                    if not (i == 0 or k == 0):
                        continue
                    if not (j == m-1 or l == m-1):
                        continue

                    x = max(i, k)
                    y = min(j, l)
                    len = y - x + 1
                    if len >= 0:
                        v = (n - 1) ** len
                        if len == 0:
                            ans += v
                        else:
                            ans += 2 * v
    return ans

def solve(n, m):
    step = 4 * (steps(n, m) - 2)
    horz = verts(n, m)
    vert = verts(m, n)
    flats = 2 * ((n - 1) + (m - 1))
    ans = horz + vert - step + flats
    return ans // 2

def main():
    with open('separable.in', 'r') as fin:
        m, n = map(int, fin.readlines()[0].split())
    ans = solve(m, n)
    with open('separable.out', 'w') as fout:
        print(ans, file=fout)

if __name__ == '__main__':
    main()


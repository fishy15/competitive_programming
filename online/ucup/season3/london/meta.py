def solve():
    n = int(input())
    opts: list[int] = []
    for _ in range(n):
        _, a_str, b_str, c_str = input().split()
        times = list(filter(lambda x: x != -1, map(int, (a_str, b_str, c_str))))
        if times:
            opts.append(min(times))

    used = 0
    time = 0
    for t in sorted(opts):
        if time + t <= 300:
            time += t
            used += 1

    print(used)

if __name__ == '__main__':
    solve()

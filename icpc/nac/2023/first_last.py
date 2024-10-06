from functools import lru_cache
from itertools import product, combinations, permutations

def to_list(tup):
    return list(list(row) for row in tup)

def to_tup(lst):
    return tuple(tuple(row) for row in lst)

def rem(state, x, y):
    as_list = to_list(state)
    as_list[x][y] -= 1
    return to_tup(as_list)

@lru_cache(maxsize=None)
def brute(state, cur):
    for i in range(3):
        if state[cur][i] > 0:
            nxt_state = rem(state, cur, i)
            if not brute(nxt_state, i):
                return True
    return False

def format(xs):
    return (xs[0:3], xs[3:6], xs[6:9])

def reduce(state):
    as_list = to_list(state)

    for a in range(3):
        as_list[a][a] %= 2

    for a, b in combinations(range(3), 2):
        mm = min(as_list[a][b], as_list[b][a])
        as_list[a][b] -= mm
        as_list[b][a] -= mm

    return to_tup(as_list)

def solve(state, start):
    state = reduce(state)

    all_zeros = (
        (0, 0, 0),
        (0, 0, 0),
        (0, 0, 0),
    )

    if state == all_zeros:
        return False

    for a in range(3):
        if a == start:
            # if the only thing we can do is loop here
            if state[a][a] == 1 and sum(state[a]) == 1:
                return True

            for b in range(3):
                if a != b:
                    if state[a][b] > 0 and sum(state[b]) == 0:
                        return True

    cyc_count = sum(state[i][i] for i in range(3))
    for p in permutations(range(3)):
        a, b, c = p
        if state[a][b] > 0 and state[b][c] > 0 and state[c][a] > 0:
            if state[a][b] == state[b][c] == state[c][a]:
                cnt = state[a][b]
                if cnt == 1:
                    return True
                return (cnt + cyc_count) % 2 == 1
            return True
    return False

def main():
    n = int(input())
    words = [input() for _ in range(n)]

    as_list = [[0]*3 for _ in range(3)]
    starts_and_ends = list(set(w[0] for w in words).union(set(w[-1] for w in words)))

    for w in words:
        a = starts_and_ends.index(w[0])
        b = starts_and_ends.index(w[-1])
        as_list[a][b] += 1

    ans = 0
    state = to_tup(as_list)
    for a in range(3):
        for b in range(3):
            if state[a][b] > 0:
                if not brute(reduce(rem(state, a, b)), b):
                    ans += state[a][b]
    print(ans)

if __name__ == '__main__':
    main()
    

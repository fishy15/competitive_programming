def solve(state, pos):
    res = []
    for i in range(len(state)):
            if i == pos:
                    continue
            st = state.copy()
            st[i] -= 1
            if st[i] == 0:
                    del st[i]
                    res.append(solve(st, len(st)))
            else:
                    res.append(solve(st, i))
    if len(res) == 0 or min(res) == 1:
            return 0
    return 1

from itertools import permutations

def prob_win(teams, goal):
    groups = [[[1.0, i]] for i in range(8)]
    def merge(groups1, groups2):
        res = [[0.0, -1] for _ in range(2 * len(groups1))]
        cur = 0 
        for p1, pos1 in groups1:
            res[cur][1] = pos1
            for p2, pos2 in groups2:
                if pos1 < pos2:
                    me = teams[pos1][0]
                    other = teams[pos2][1]
                else:
                    me = teams[pos1][1]
                    other = teams[pos2][0]
                res[cur][0] += p1 * p2 * me / (me + other)
            cur += 1
        for p1, pos1 in groups2:
            res[cur][1] = pos1
            for p2, pos2 in groups1:
                if pos1 < pos2:
                    me = teams[pos1][0]
                    other = teams[pos2][1]
                else:
                    me = teams[pos1][1]
                    other = teams[pos2][0]
                res[cur][0] += p1 * p2 * me / (me + other)
            cur += 1
        return res

    while len(groups) > 1:
        nxt_groups = []
        for i in range(0, len(groups), 2):
            nxt_groups.append(merge(groups[i], groups[i+1]))
        groups = nxt_groups

    ans = 0
    for p, idx in groups[0]:
        if teams[idx] == goal:
            ans = max(ans, p)
    return ans

if __name__ == '__main__':
    teams = [list(int(x) for x in input().split()) for _ in range(8)]

    ans = 0
    goal = teams[0]
    for t in permutations(teams):
        ans = max(ans, prob_win(t, goal))

    print(ans)

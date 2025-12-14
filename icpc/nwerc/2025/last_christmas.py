from collections import Counter

def main():
    n = int(input())
    groups_t = [input().split() for _ in range(n)]
    groups: list[list[str]] = [[] for _ in range(10)]
    for g in groups_t:
        for i, x in enumerate(g):
            groups[i].append(x)

    all_count = Counter([x for xs in groups for x in xs])
    indiv = [Counter(xs) for xs in groups]
    indiv = [all_count] + indiv

    def construct(s: str) -> list[int]:
        return [m.get(s, 0) for m in indiv]

    levels = [construct(s) for s in all_count.keys()]
    ans = max(all_count.keys(), key=lambda s: construct(s))
    if levels.count(construct(ans)) > 1:
        print('tie')
    else:
        print(ans)

if __name__ == '__main__':
    main()

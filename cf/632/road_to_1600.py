from itertools import permutations

def find_index(nums, n):
    return [(x, i // n, i % n) for i, x in enumerate(nums)]

def find_cost(nums, diag):
    nums = nums.copy()

    def reachable(cur_x, cur_y, new_x, new_y):
        same_row = cur_x == new_x
        same_col = cur_y == new_y
        same_diag = (cur_x + cur_y == new_x + new_y) or (cur_x - cur_y == new_x - new_y)

        return same_row or same_col or (diag and same_diag)

    count = 0
    while nums:
        count += 1
        cur = min(nums)
        nums.remove(cur)

        while True:
            reachable_nodes = [loc for loc in nums if reachable(cur[1], cur[2], loc[1], loc[2])]
            if reachable_nodes:
                cur = min(reachable_nodes)
                nums.remove(cur)
            else:
                break

    return count - 1

def pretty_print(lst, n):
    for i, x in enumerate(lst):
        print(x + 1, end=' ')
        if i % n == n - 1:
            print()

def main():
    n = 3
    for lst in permutations(range(0, n ** 2)):
        idxs = find_index(lst, n)
        if find_cost(idxs, False) < find_cost(idxs, True):
            pretty_print(lst, n)
            break

if __name__ == '__main__':
    main()

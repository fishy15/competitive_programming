from itertools import combinations
from functools import lru_cache

def all_rems(lst, sz):
	n = len(lst)
	for idxs in combinations(range(n), sz):
		res = []
		for i, x in enumerate(lst):
			if i not in idxs:
				res += [x]
		yield res

def split(lst, idxs, cur_lst, idx):
	if idx == len(lst):
		yield cur_lst
	else:
		if idx in idxs:
			for i in range(1, lst[idx] // 2 + 1):
				yield from split(lst, idxs, cur_lst + [i, lst[idx] - i], idx+1)
		else:
			yield from split(lst, idxs, cur_lst + [lst[idx]], idx+1)
		

def all_splits(lst, sz):
	n = len(lst)
	for idxs in combinations(range(n), sz):
		yield from split(lst, idxs, [], 0)

@lru_cache(maxsize=None)
def wins(lst):
	n = len(lst)
	for sz in range(1, n//2 + 1):
		for after_rems in all_rems(lst, sz):
			for after_splits in all_splits(after_rems, sz):
				after_splits.sort()
				if not wins(tuple(after_splits)):
					return True
	return False

def solve(lst):
	if len(lst) % 2 == 1:
		while all(x % 2 == 0 for x in lst):
			for i in range(len(lst)):
				lst[i] /= 2

	if any(x % 2 == 0 for x in lst):
		print("1")
	else:
		print("0")
	
for i in range(1, 30):
	for j in range(i, 30):
		for k in range(j, 30):
			if not wins((i, j, k)):
				print(i, j, k)

'''
t = int(input())
for _ in range(t):
	n = int(input())
	nums = list(map(int, input().split()))
	solve(nums)
'''

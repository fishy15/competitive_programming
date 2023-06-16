#!/usr/local/bin/python3.9

import sys

def visit(x, y, grid, vis):
    if x < 0 or y < 0 or x >= len(grid) or y >= len(grid[x]) or vis[x][y] or grid[x][y] == '.':
        return

    vis[x][y] = True

    dx = [-1, -1, -1, 0, 1, 1, 1, 0]
    dy = [-1, 0, 1, 1, 1, 0, -1, -1]

    for a, b in zip(dx, dy):
        visit(x + a, y + b, grid, vis)


def main():
    n, m = map(int, sys.stdin.readline().split())
    grid = [sys.stdin.readline().strip() for _ in range(n)]
    vis = [[False] * m for _ in range(n)]

    cnt = 0
    for i in range(n):
        for j in range(m):
            if not vis[i][j] and grid[i][j] == '#':
                visit(i, j, grid, vis)
                cnt += 1

    print(cnt)

if __name__ == '__main__':
    main()




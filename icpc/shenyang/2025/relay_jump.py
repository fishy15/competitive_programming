def main():
    n, s = map(int, input().split())
    s -= 1
    pts = [[int(x) for x in input().split()] for _ in range(n)]

    x_diff = sum(p[2] - p[0] for p in pts) // 2
    y_diff = sum(p[3] - p[1] for p in pts) // 2

    goal_x = pts[s][0] + x_diff
    goal_y = pts[s][1] + y_diff
    for i in range(n):
        if [goal_x, goal_y] == pts[i][2:]:
            print(i + 1)
            return

if __name__ == '__main__':
    main()

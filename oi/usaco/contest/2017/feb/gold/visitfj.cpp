#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define ll long long

using namespace std;

typedef struct loc loc;
struct loc {
    int x;
    int y;
    ll time;
    int eaten;

    loc (int x, int y, ll time, int eaten) {
        this->x = x;
        this->y = y;
        this->time = time;
        this->eaten = eaten;
    }
};

bool comp(const loc &l1, const loc &l2) {
    return l1.time > l2.time;
}

int n, t;
int grid[100][100];
ll dist[100][100][3];

int main() {
    ifstream fin("visitfj.in");
    ofstream fout("visitfj.out");

    fin >> n >> t;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> grid[i][j];
        }
    }

    loc start(0, 0, 1, 0);

    priority_queue<loc, vector<loc>, decltype(&comp)> pq(comp);
    pq.push(start);

    while (dist[n - 1][n - 1][0] == 0 && dist[n - 1][n - 1][1] == 0 && dist[n - 1][n - 1][2] == 0) {
        loc cur = pq.top();
        pq.pop();

        if (dist[cur.x][cur.y][cur.eaten] != 0) continue;
        dist[cur.x][cur.y][cur.eaten] = cur.time;

        cout << cur.x << ' ' << cur.y << ' ' << cur.eaten << '\n';

        if (cur.eaten != 2) {
            if (cur.x > 0) pq.push(loc(cur.x - 1, cur.y, cur.time + t, cur.eaten + 1));
            if (cur.y > 0) pq.push(loc(cur.x, cur.y - 1, cur.time + t, cur.eaten + 1));
            if (cur.x < n - 1) pq.push(loc(cur.x + 1, cur.y, cur.time + t, cur.eaten + 1));
            if (cur.y < n - 1) pq.push(loc(cur.x, cur.y + 1, cur.time + t, cur.eaten + 1));
        } else {
            if (cur.x > 0) pq.push(loc(cur.x - 1, cur.y, cur.time + grid[cur.x][cur.y] + t, 0));
            if (cur.y > 0) pq.push(loc(cur.x, cur.y - 1, cur.time + grid[cur.x][cur.y] + t, 0));
            if (cur.x < n - 1) pq.push(loc(cur.x + 1, cur.y, cur.time + grid[cur.x][cur.y] + t, 0));
            if (cur.y < n - 1) pq.push(loc(cur.x, cur.y + 1, cur.time + grid[cur.x][cur.y] + t, 0));
        }
    }

    if (dist[n - 1][n - 1][0] != 0) {
        cout << dist[n - 1][n - 1][0] - 1 << '\n';
    } else if (dist[n - 1][n - 1][1] != 0) {
        cout << dist[n - 1][n - 1][1] - 1 << '\n';
    } else {
        cout << dist[n - 1][n - 1][2] - 1 << '\n';
    }

    return 0;
}
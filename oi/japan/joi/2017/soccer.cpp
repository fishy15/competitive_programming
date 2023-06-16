/* 
 * The only reason a player would lose possession of the ball is if they kicked it. We can compute the 
 * min amount of energy needed to reach to each square on the grid in both the cases where the ball is and
 * is not in possession of someone. There are three transitions: either a player moves with the ball to an
 * adjacent square, a player kicks the ball in one of the directions (losing possession of the ball), or 
 * the nearest player to the ball comes and picks it up (gaining posession of the ball). There are a lot of
 * possible kick transitions though, so to speed it up, we split the unpossessed ball case into 4 subcases 
 * representing the 4 directions the ball could be traveling in, and we add the transition of one ball
 * continuing to move in the direction it was kicked in. Overall there are at max 8 transitions possible
 * from a given state, so the time complexity is O(8 * 5 * n^2 log n).
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100010
#define MAXW 510

using namespace std;

int h, w;
ll a, b, c;
int n;
array<int, 2> players[MAXN];
priority_queue<array<ll, 4>, vector<array<ll, 4>>, greater<array<ll, 4>>> pq; // {dist, x, y, dir}
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

bool walk_set[MAXW][MAXW];
ll walk_dist[MAXW][MAXW];

// 0-3 refer to dir kicked from, corresponds to directions above
// 5 is min cost while keeping the ball
ll dist[MAXW][MAXW][5];

bool ok(int x, int y, int dir, ll d) {
    return x >= 0 && y >= 0 && x < h && y < w && d < dist[x][y][dir];
}

bool ok_walk(int x, int y) {
    return x >= 0 && y >= 0 && x < h && y < w && !walk_set[x][y];
}

void set_dist(ll d, int x, int y, int dir) {
    if (dist[x][y][dir] < d) return;
    if (dir < 4) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        // continue the kick
        if (ok(nx, ny, dir, d + a)) {
            dist[nx][ny][dir] = d + a;
            pq.push({d + a, nx, ny, dir});
        }

        // get picked up by person
        if (ok(x, y, 4, d + walk_dist[x][y])) {
            dist[x][y][4] = d + walk_dist[x][y];
            pq.push({d + walk_dist[x][y], x, y, 4});
        }
    } else {
        // walk to adjacent square
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (ok(nx, ny, 4, d + c)) {
                dist[nx][ny][4] = d + c;
                pq.push({d + c, nx, ny, 4});
            }
        }

        // kick in some direction
        for (int i = 0; i < 4; i++) {
            if (ok(x, y, i, d + b)) {
                dist[x][y][i] = d + b;
                pq.push({d + b, x, y, i});
            }
        }
    }
}

void calc_walk() {
    queue<array<int, 2>> q;
    for (int i = 0; i < n; i++) {
        auto [x, y] = players[i];
        walk_set[x][y] = true;
        q.push({x, y});
    }

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (ok_walk(nx, ny)) {
                walk_dist[nx][ny] = walk_dist[x][y] + c;
                walk_set[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
}

void calc_dist() {
    pq.push({0, players[0][0], players[0][1], 4});
    memset(dist, 0x3f, sizeof dist);
    dist[players[0][0]][players[0][1]][4] = 0;
    while (!pq.empty()) {
        auto [d, x, y, dir] = pq.top();
        pq.pop();
        set_dist(d, x, y, dir);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> h >> w;
    cin >> a >> b >> c;
    cin >> n;

    h++; w++;
    for (int i = 0; i < n; i++) {
        int s, t; cin >> s >> t;
        players[i] = {s, t};
    }

    calc_walk();

    calc_dist();

    cout << dist[players[n - 1][0]][players[n - 1][1]][4] << '\n';

    return 0;
}

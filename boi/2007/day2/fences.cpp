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
#define MAXN 500

using namespace std;

int n;
array<int, 4> rect[MAXN];
map<int, int> mx;
map<int, int> my;

int psum[MAXN][MAXN];

int m;
pair<int, int> pts[MAXN];
vector<array<int, 3>> adj[MAXN];

int ckmin(int &a, int b) {
    return a = min(a, b);
}

int dist(int start) {
    vector<array<bool, 2>> vis(m);
    vector<array<int, 2>> dist(m, {INF, INF});
    dist[start][0] = 0;

    for (int i = 0; i < 2 * m; i++) {
        int min_dist = INF;
        pair<int, int> pos = {-1, -1};
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 2; k++) {
                if (!vis[j][k] && dist[j][k] < min_dist) {
                    min_dist = dist[j][k];
                    pos = {j, k};
                }
            }
        }
        if (pos.first == -1) break;
        vis[pos.first][pos.second] = true;
        for (auto e : adj[pos.first]) {
            if (!vis[e[0]][pos.second ^ e[2]]) {
                ckmin(dist[e[0]][pos.second ^ e[2]], dist[pos.first][pos.second] + e[1]);
            }
        }
    }

    return dist[start][1];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> rect[i][0] >> rect[i][1] >> rect[i][2] >> rect[i][3];
        mx[rect[i][0]] = 0;
        mx[rect[i][2]] = 0;
        my[rect[i][1]] = 0;
        my[rect[i][3]] = 0;
    }

    int cur = 1;
    for (auto &p : mx) {
        mx[p.first] = cur;
        cur += 2;
    }
    cur = 1;
    for (auto &p : my) {
        my[p.first] = cur;
        cur += 2;
    }

    for (int i = 0; i < n; i++) {
        auto &cur = rect[i];
        for (int j = mx[cur[0]] + 1; j < mx[cur[2]]; j++) {
            for (int k = my[cur[1]] + 1; k < my[cur[3]]; k++) {
                psum[j][k]++;
            }
        }
    }

    for (int i = 1; i < MAXN; i++) {
        for (int j = 1; j < MAXN; j++) {
            psum[i][j] += psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1];
        }
    }

    // figure out what points are not inside another rectangle
    for (int i = 0; i < n; i++) {
        auto &cur = rect[i];
        vector<pair<int, int>> pt = {{cur[0], cur[1]}, {cur[0], cur[3]}, {cur[2], cur[1]}, {cur[2], cur[3]}};
        for (auto p : pt) {
            bool inside = false;
            for (int j = 0; j < n; j++) {
                if (rect[j][0] < p.first && p.first < rect[j][2] && rect[j][1] < p.second && p.second < rect[j][3]) {

                    inside = true;
                    break;
                }
            }

            if (!inside) {
                pts[m++] = p;
            }
        }
    }

    // build edges
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            int min_x = mx[min(pts[i].first, pts[j].first)] - 1;
            int max_x = mx[max(pts[i].first, pts[j].first)];
            int min_y = my[min(pts[i].second, pts[j].second)] - 1;
            int max_y = my[max(pts[i].second, pts[j].second)];
            int area = psum[max_x][max_y] - psum[min_x][max_y] - psum[max_x][min_y] + psum[min_x][min_y];

            if (area == 0) {
                int d = 0;
                if (min_x + 1 <= mx[rect[0][0]] && max_x > mx[rect[0][0]] && max_y <= my[rect[0][1]]) d = 1;
                adj[i].push_back({j, abs(pts[i].first - pts[j].first) + abs(pts[i].second - pts[j].second), d});
                adj[j].push_back({i, abs(pts[i].first - pts[j].first) + abs(pts[i].second - pts[j].second), d});
            }
        }
    }

    int ans = INF;
    for (int i = 0; i < m; i++) {
        ckmin(ans, dist(i));
    }

    cout << ans << '\n';

    return 0;
}

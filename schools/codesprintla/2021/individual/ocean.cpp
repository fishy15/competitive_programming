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
#define MAXN 1000000

using namespace std;

void solve() {
    int a, b; cin >> a >> b;

    vector<vector<ll>> cnt(60, vector<ll>(60));
    vector<vector<ll>> dist(60, vector<ll>(60, -1));
    vector<vector<bool>> vis(60, vector<bool>(60));
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> pq;
    pq.push({0, a, b});

    cnt[a][b] = 1;
    dist[a][b] = 0;

    while (!pq.empty()) {
        auto [d, x, y] = pq.top();
        pq.pop();

        if (dist[x][y] == d && !vis[x][y]) {
            if (x > 1) {
                auto &nd = dist[x - 1][y];
                auto &nc = cnt[x - 1][y];
                if (nd == -1 || nd > d + 1) {
                    nd = d + 1;
                    nc = cnt[x][y];
                } else if (nd == d + 1) {
                    nc += cnt[x][y];
                }
                pq.push({d + 1, x - 1, y});
            }

            if (y > 0) {
                auto &nd = dist[x + 1][y - 1];
                auto &nc = cnt[x + 1][y - 1];
                if (nd == -1 || nd > d + 1) {
                    nd = d + 1;
                    nc = cnt[x][y];
                } else if (nd == d + 1) {
                    nc += cnt[x][y];
                }
                pq.push({d + 1, x + 1, y - 1});
            }

            if (x == 2 && y == 0) {
                auto &nd = dist[0][0];
                auto &nc = cnt[0][0];
                if (nd == -1 || nd > d + 1) {
                    nd = d + 1;
                    nc = cnt[x][y];
                } else if (nd == d + 1) {
                    nc += cnt[x][y];
                }
                pq.push({d + 1, 0, 0});
            }

            if (x == 0 && y == 1) {
                auto &nd = dist[0][0];
                auto &nc = cnt[0][0];
                if (nd == -1 || nd > d + 1) {
                    nd = d + 1;
                    nc = cnt[x][y];
                } else if (nd == d + 1) {
                    nc += cnt[x][y];
                }
                pq.push({d + 1, 0, 0});
            }

            vis[x][y] = true;
        }
    }

    cout << cnt[0][0] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

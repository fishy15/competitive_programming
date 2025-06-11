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
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

constexpr array dx = {1, 0, -1, 0};
constexpr array dy = {0, 1, 0, -1};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int, int>>> by_row(n), by_col(m);

    vector<pair<int, int>> locs(k);
    for (auto &[x, y] : locs) {
        cin >> x >> y;
        x--;
        y--;
        by_row[x].push_back({x, y});
        by_col[y].push_back({x, y});
    }

    auto ord = locs;
    rep(i, 0, n) {
        ord.push_back({i, -1});
    }
    rep(i, 0, m) {
        ord.push_back({-1, i});
    }

    sort(all(ord));

    vector<int> dist(sz(ord), INF);
    deque<array<int, 3>> q;
    auto get = [&](int x, int y) { 
        auto it = lower_bound(all(ord), pair{x, y});
        if (it == end(ord) || *it != pair{x, y}) {
            return -1;
        }
        return (int) (it - begin(ord));
    };

    int start = get(0, 0);
    dist[start] = 0;
    q.push_back({0, 0, 0});

    while (!q.empty()) {
        auto [x, y, d] = q.front();
        q.pop_front();

        if (d != dist[get(x, y)]) {
            continue;
        }

        if (y == -1) {
            // we can go to anything in the adj row for free
            rep(adj_x, x-1, x+2) {
                if (adj_x >= 0 && adj_x < n) {
                    for (auto [nx, ny] : by_row[adj_x]) {
                        auto pos = get(nx, ny);
                        if (d < dist[pos]) {
                            dist[pos] = d;
                            q.push_front({nx, ny, d});
                        }
                    }
                }
            }
        } else if (x == -1) {
            // we can go to anything in the same col for free
            rep(adj_y, y-1, y+2) {
                if (adj_y >= 0 && adj_y < m) {
                    for (auto [nx, ny] : by_col[adj_y]) {
                        auto pos = get(nx, ny);
                        if (d < dist[pos]) {
                            dist[pos] = d;
                            q.push_front({nx, ny, d});
                        }
                    }
                }
            }
        } else {
            // we can go to anything adjacent for free
            rep(i, 0, 4) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 0 && ny >= 0 && nx < n && ny < m) {
                    int npos = get(nx, ny);
                    if (npos != -1 && d < dist[npos]) {
                        dist[npos] = d;
                        q.push_front({nx, ny, d});
                    }
                }
            }

            // we can also go to adj row/column for 1 cost
            rep(nx, x-1, x+2) {
                int row_pos = get(nx, -1);
                if (row_pos != -1 && d+1 < dist[row_pos]) {
                    dist[row_pos] = d+1;
                    q.push_back({nx, -1, d+1});
                }
            }
            rep(ny, y-1, y+2) {
                int col_pos = get(-1, ny);
                if (col_pos != -1 && d+1 < dist[col_pos]) {
                    dist[col_pos] = d+1;
                    q.push_back({-1, ny, d+1});
                }
            }
        }
    }

    int end_pos = get(n-1, m-1);
    if (end_pos == -1) {
        auto ans = min(dist[get(n-1, -1)], dist[get(-1, m-1)]);
        if (ans == INF) {
            cout << "-1\n";
        } else {
            cout << ans << '\n';
        }
    } else {
        cout << dist[end_pos] << '\n';
    }

    return 0;
}

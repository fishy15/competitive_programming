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

constexpr int B = 200;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> dogs(n);
    int start = -1;
    int goal = -1;
    rep(i, 0, m) {
        int b, p;
        cin >> b >> p;
        dogs[b].push_back(p);
        if (i == 0) {
            start = b;
        } else if (i == 1) {
            goal = b;
        }
    }

    // 0 = min time to reach, 1-B = min time where we have a dog of that weight
    vector dist(n, vector<int>(B + 1, INF));
    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> pq;

    auto move_small = [&](int x, int p) {
        int d = dist[x][p];
        if (d < dist[x][0]) {
            dist[x][0] = d;
            pq.push({d, x, 0});
        }

        if (x - p >= 0 && d + 1 < dist[x - p][p]) {
            dist[x - p][p] = d + 1;
            pq.push({d + 1, x - p, p});
        }

        if (x + p < n && d + 1 < dist[x + p][p]) {
            dist[x + p][p] = d + 1;
            pq.push({d + 1, x + p, p});
        }
    };

    auto move_large = [&](int x, int p) {
        int d = dist[x][0];
        for (int i = x - p; i >= 0; i -= p) {
            d++;
            if (d < dist[i][0]) {
                dist[i][0] = d;
                pq.push({d, i, 0});
            }
        }

        d = dist[x][0];
        for (int i = x + p; i < n; i += p) {
            d++;
            if (d < dist[i][0]) {
                dist[i][0] = d;
                pq.push({d, i, 0});
            }
        }
    };

    auto move_base = [&](int x) {
        for (auto p : dogs[x]) {
            if (p <= B) {
                if (dist[x][0] < dist[x][p]) {
                    dist[x][p] =  dist[x][0];
                    pq.push({dist[x][p], x, p});
                }
            } else {
                move_large(x, p);
            }
        }
    };

    dist[start][0] = 0;
    pq.push({0, start, 0});
    while (!pq.empty()) {
        auto [d, x, p] = pq.top();
        pq.pop();

        if (d != dist[x][p]) continue;
        if (p == 0) {
            move_base(x);
        } else {
            move_small(x, p);
        }
    }

    if (dist[goal][0] == INF) {
        cout << "-1\n";
    } else {
        cout << dist[goal][0] << '\n';
    }

    return 0;
}

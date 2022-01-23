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

// change if necessary
#define MAXN 100010

using namespace std;

int n, m;
vector<int> adj[MAXN];
vector<int> dadj[MAXN];
set<array<int, 2>> edge;
int deg[MAXN];
ll tot;
ll tri;

ll c2(ll x) {
    return x * (x - 1) / 2;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;;
        adj[a].push_back(b);
        adj[b].push_back(a);
        edge.insert({min(a, b), max(a, b)});
        deg[a]++;
        deg[b]++;
    }

    // count total number
    for (int i = 0; i < n; i++) {
        if (deg[i] < 4) continue;
        ll d = deg[i];

        ll tot_deg = 0;
        for (int e : adj[i]) {
            tot_deg += deg[e] - 1;
        }

        ll c = (d - 1) * (d - 2) * (d - 3) / 6;
        tot += tot_deg * c;
    }

    // count triangle count
    for (auto [a, b] : edge) {
        if (deg[a] < deg[b]) {
            dadj[a].push_back(b);
        } else if (deg[a] == deg[b]) {
            auto [x, y] = minmax(a, b);
            dadj[x].push_back(y);
        } else {
            dadj[b].push_back(a);
        }
    }

    vector<pair<int, int>> ord;
    for (int i = 0; i < n; i++) {
        ord.push_back({deg[i], i});
    }

    sort(ord.begin(), ord.end());

    for (auto [_, v] : ord) {
        auto &cur = dadj[v];
        int sz = cur.size();
        for (int i = 0; i < sz; i++) {
            for (int j = i + 1; j < sz; j++) {
                auto [x, y] = minmax(cur[i], cur[j]);
                if (edge.count({x, y})) {
                    tri += c2(deg[v] - 2);
                    tri += c2(deg[x] - 2);
                    tri += c2(deg[y] - 2);
                }
            }
        }
    }

    cout << tot - 2 * tri << '\n';

    return 0;
}

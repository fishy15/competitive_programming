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
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : v(_v % MOD) {}

    mi operator+(const mi other) const { return mi(v + other.v); }
    mi operator-(const mi other) const { return mi(v - other.v); }
    mi operator*(const mi other) const { return mi((ll) v * other.v); }

#define OP(op) \
    mi &operator op##= (const mi other) { return *this = *this op other; }
    OP(+); OP(-); OP(*);
#undef OP
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);

    vector<int> val_assigned(n, -1);
    vector<int> idx_assigned(n, -1);

    // {max possible, how many things assert this}
    vector<int> max_possible(n, n-1);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        c--;

        max_possible[a] = min(max_possible[a], c);
        max_possible[b] = min(max_possible[b], c);

        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    auto assign = [&](int v, int w) {
        if (idx_assigned[v] != -1 && idx_assigned[v] != w) {
            cout << "0\n";
            exit(0);
        }

        if (val_assigned[w] != -1 && val_assigned[w] != v) {
            cout << "0\n";
            exit(0);
        }

        idx_assigned[v] = w;
        val_assigned[w] = v;
    };

    for (int u = 0; u < n; u++) {
        sort(adj[u].begin(), adj[u].end(), [](auto p1, auto p2) {
            return p1.second < p2.second;
        });

        if (!adj[u].empty()) {
            auto min_weight = adj[u][0].second;
            int min_cnt = 0;
            for (auto [v, w] : adj[u]) {
                if (w == min_weight) {
                    min_cnt++;
                } else {
                    assign(v, w);
                }
            }

            if (min_cnt > 1) {
                assign(u, min_weight);
            }
        }
    }

    // if any unassigned pairs, just assign and double answer
    mi ans = 1;
    
    for (int u = 0; u < n; u++) {
        for (auto [v, w] : adj[u]) {
            if (idx_assigned[u] == -1 && idx_assigned[v] == -1) {
                assign(u, w);
                ans *= 2;
            }
        }
    }

    // remainder of values can be anything
    
    vector<int> remainder;
    vector<int> unassigned_leq(n);
    for (int i = 0; i < n; i++) {
        if (i > 0) unassigned_leq[i] += unassigned_leq[i-1];
        if (val_assigned[i] == -1) unassigned_leq[i]++;
        if (idx_assigned[i] == -1) remainder.push_back(i);
    }

    sort(remainder.begin(), remainder.end(), [&](auto a, auto b) {
        return max_possible[a] < max_possible[b];
    });

    for (int i = 0; i < (int) remainder.size(); i++) {
        int choices = unassigned_leq[max_possible[remainder[i]]] - i;
        if (choices <= 0) {
            cout << "0\n";
            return 0;
        } else {
            ans *= choices;
        }
    }

    cout << ans.v << '\n';

    return 0;
}

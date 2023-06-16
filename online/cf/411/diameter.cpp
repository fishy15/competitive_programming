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
#include <unordered_map>

#define ll long long
#define ld double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100010

using namespace std;

struct tree {
    int d;
    vector<int> dist;
    vector<ld> exp_psum;
    vector<ld> prob_psum;
    int cnt = 0;
    ld exp;

    void add(int x) {
        if ((int) dist.size() <= x) {
            dist.resize(x + 1);
        }
        dist[x]++;
        cnt++;
    }

    void calc_exp() {
        exp_psum.push_back(0);
        prob_psum.push_back(0);

        ld sum = 0;
        for (int i = 0; i < (int) dist.size(); i++) {
            exp += (ld) i * dist[i] / cnt;
            sum += (ld) dist[i] / cnt;
            exp_psum.push_back(exp);
            prob_psum.push_back(sum);
        }
    }

    // expected value of sum where i + j + 1 < d2
    ld get_change(int i) {
        int min_j = d / 2;
        int max_j = d - i - 1;
        // want dist[j] / cnt * (i + j + 1)
        // = dist[j] / cnt * (i + 1) + dist[j] / cnt * j
        // first part sum is cons

        ld prob = prob_psum[max_j] - prob_psum[min_j];
        ld E = exp_psum[max_j] - exp_psum[min_j];

        return prob * d - prob * (i + 1) - E;
    }
};

int n, m, q;
vector<tree> t;
vector<int> adj[MAXN];
int dist[MAXN];

ll conv(int a, int b) {
    return (ll) a + n * b;
}

map<int, int> to_t;
unordered_map<ll, double> cache;

array<int, 2> dfs_m(int v, int p) {
    array<int, 2> ans{0, v};

    for (int e : adj[v]) {
        if (e != p) {
            auto res = dfs_m(e, v);
            res[0]++;
            ans = max(ans, res);
        }
    }

    return ans;
}

void calc_d(int v, int p, int x) {
    dist[v] = max(dist[v], x);
    for (int e : adj[v]) {
        if (e != p) {
            calc_d(e, v, x + 1);
        }
    }
}

void add(int v, int p) {
    to_t[v] = ((int) t.size()) - 1;
    t.back().add(dist[v]);

    for (int e : adj[v]) {
        if (e != p) {
            add(e, v);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 0; i < n; i++) {
        if (!to_t.count(i)) {
            t.emplace_back();
            auto [_, loc] = dfs_m(i, i);

            auto [d, other] = dfs_m(loc, loc);
            t.back().d = d;

            calc_d(loc, loc, 0);
            calc_d(other, other, 0);

            add(i, i);
            t.back().calc_exp();
        }
    }

    cout << fixed << setprecision(10);

    while (q--) {
        int u, v; cin >> u >> v;
        u--; v--;

        auto [a, b] = minmax(to_t[u], to_t[v]);
        if (a == b) {
            cout << "-1\n";
        } else {
            ll x = conv(a, b);
            if (cache.count(x)) {
                cout << cache[x] << '\n';
            } else {
                auto smaller = t[a];
                auto larger = t[b];

                if (smaller.d > larger.d) {
                    swap(smaller, larger);
                }

                int d1 = smaller.d;
                int d2 = larger.d;

                ld E = smaller.exp + larger.exp + 1;

                for (int i = d1 / 2; i <= min(d1, d2 / 2); i++) {
                    ld prob = (ld) smaller.dist[i] / smaller.cnt;
                    /* E -= prob * (i + j + 1); */
                    /* E += prob * larger.d; */
                    E += prob * larger.get_change(i);
                }

                cout << E << '\n';
                cache[x] = E;
            }
        }
    }

    return 0;
}

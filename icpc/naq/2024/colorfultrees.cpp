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
#include <cassert>

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

using vi = vector<int>;
using pii = pair<int, int>;

template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j,0,sz(jmp[k]))
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b); // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

struct LCA {
    int T = 0;
    vi time, path, ret;
    RMQ<int> rmq;

    LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C,0,-1), ret)) {}
    void dfs(vector<vi>& C, int v, int par) {
        time[v] = T++;
        for (int y : C[v]) if (y != par) {
            path.push_back(v), ret.push_back(time[v]);
            dfs(C, y, v);
        }
    }

    int lca(int a, int b) {
        if (a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
    //dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};


typedef vector<pair<int, int>> vpi;
vpi compressTree(LCA& lca, const vi& subset) {
    static vi rev; rev.resize(sz(lca.time));
    vi li = subset, &T = lca.time;
    auto cmp = [&](int a, int b) { return T[a] < T[b]; };
    sort(all(li), cmp);
    int m = sz(li)-1;
    rep(i,0,m) {
        int a = li[i], b = li[i+1];
        li.push_back(lca.lca(a, b));
    }
    sort(all(li), cmp);
    li.erase(unique(all(li)), li.end());
    rep(i,0,sz(li)) rev[li[i]] = i;
    vpi ret = {pii(0, li[0])};
    rep(i,0,sz(li)-1) {
        int a = li[i], b = li[i+1];
        ret.emplace_back(rev[lca.lca(a, b)], b);
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> color(n);
    vector<vector<int>> at_color(n);
    vector<vector<int>> adj(n);
    rep(i, 0, n) {
        cin >> color[i];
        color[i]--;
        at_color[color[i]].push_back(i);
    }

    vector<pair<int, int>> edges;
    rep(i, 0, n - 1) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
        edges.push_back({a, b});
    }

    LCA lca(adj);

    vector<ll> overall_diff(n);
    rep(c, 0, n) {
        const auto &s = at_color[c];
        if (sz(s) > 1) {
            auto pp = compressTree(lca, s);
            vector<ll> child_count(sz(pp));
            // how much you change answer from all children
            vector<ll> diff(sz(pp));
            for (int i = sz(pp) - 1; i >= 0; i--) {
                auto [par, orig] = pp[i];
                if (color[orig] == c) {
                    // add all paths going up
                    // remove all paths going down
                    diff[i] += sz(s) - child_count[i] - 1;
                    diff[i] -= child_count[i];
                    child_count[i]++;
                }

                // add to parent and remove from lca if necessary
                if (par != i) {
                    diff[par] -= 2LL * child_count[par] * child_count[i];
                    child_count[par] += child_count[i];
                }
            }

            // now update state
            rep(i, 0, sz(pp)) {
                auto [_, orig] = pp[i];
                overall_diff[orig] += diff[i];
            }
        }
    }

    vector<ll> ans_low(n);
    vector<ll> depth(n);
    auto dfs = [&](auto &&self, int v, int p, int d) -> void {
        ans_low[v] += overall_diff[v];
        depth[v] = d;
        for (auto e : adj[v]) {
            if (e != p) {
                self(self, e, v, d+1);
                ans_low[v] += ans_low[e];
            }
        }
    };

    dfs(dfs, 0, 0, 0);

    for (auto [a, b] : edges) {
        auto v = depth[a] > depth[b] ? a : b;
        cout << ans_low[v] << '\n';
    }

    return 0;
}

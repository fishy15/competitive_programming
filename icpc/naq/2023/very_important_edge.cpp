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
#include <climits>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct DSU {
    vector<int> dsu;
    vector<int> sz;
    DSU(int n) : dsu(n), sz(n, 1) {
        iota(dsu.begin(), dsu.end(), 0);
    }

    int find(int x) {
        if (x == dsu[x]) return x;
        return dsu[x] = find(dsu[x]);
    }

    bool join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            dsu[y] = x;
            sz[x] += sz[y];
            return true;
        }
        return false;
    }
};

template<typename T>
void merge(T &a, T &&b) {
    if (a.size() < b.size()) swap(a, b);
    for (auto x : b) {
        a.insert(x);
    }
}

struct segtree {
    typedef int T;
    static constexpr T unit = INT_MAX;
    T f(T a, T b) { return min(a, b); }
    vector<T> s; int n;
    segtree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(int b, int e) {
        T ra = unit, rb = unit;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};

struct tree {
    int n;
    vector<vector<pair<int, int>>> tadj;
    vector<multiset<int>> add;
    vector<vector<array<int, 3>>> rem;
    ll cost = 0;
    ll ans = 0;

    int t = 0;
    vector<int> in;
    vector<int> out;
    vector<array<int, 20>> up;

    segtree st;

    tree(int n) : n(n), tadj(n), add(n), rem(n), in(n), out(n), up(n), st(n) {}

    void add_edge(int a, int b, int w) {
        tadj[a].push_back({b, w});
        tadj[b].push_back({a, w});
        cost += w;
    }

    void add_extra(int a, int b, int w) {
        add[a].insert(w);
        add[b].insert(w);
        rem[lca(a, b)].push_back({a, b, w});
    }

    void predfs(int v, int p) {
        in[v] = t++;
        up[v][0] = p;
        for (int i = 1; i < 20; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }

        for (auto [e, w] : tadj[v]) {
            if (e != p) {
                predfs(e, v);
            }
        }

        out[v] = t;
    }

    bool anc(int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    }

    int lca(int u, int v) {
        if (anc(u, v)) return u;
        if (anc(v, u)) return v;
        for (int i = 19; i >= 0; i--) {
            if (!anc(up[v][i], u)) v = up[v][i];
        }
        return up[v][0];
    }

    void init() {
        for (int i = 0; i < n; i++) {
            if (!add[i].empty()) {
                st.update(in[i], *add[i].begin());
            }
        }
    }

    void prem(int a, int w) {
        add[a].erase(add[a].find(w));
        if (add[a].empty()) {
            st.update(in[a], segtree::unit);
        } else {
            st.update(in[a], *add[a].begin());
        }
    }

    void dfs(int v, int p) {
        int up = -1;
        for (auto [e, w] : tadj[v]) {
            if (e != p) {
                dfs(e, v);
            } else {
                up = w;
            }
        }

        for (auto [a, b, w] : rem[v]) {
            prem(a, w);
            prem(b, w);
        }

        if (up != -1) {
            auto g = st.query(in[v], out[v]);
            ans = max(ans, cost - up + g);
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<array<int, 3>> edges;
    edges.reserve(m);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        edges.push_back({w, a, b});
    }

    sort(edges.begin(), edges.end(), [](auto a, auto b) { return a[0] < b[0]; });

    DSU dsu(n);
    tree t(n);
    vector<array<int, 3>> extra;
    for (auto [w, a, b] : edges) {
        if (dsu.join(a, b)) {
            t.add_edge(a, b, w);
        } else {
            extra.push_back({w, a, b});
        }
    }

    t.predfs(0, 0);
    for (auto [w, a, b] : extra) {
        t.add_extra(a, b, w);
    }

    t.init();
    t.dfs(0, 0);
    cout << t.ans << '\n';

    return 0;
}

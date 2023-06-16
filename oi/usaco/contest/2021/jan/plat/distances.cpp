#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <array>
#include <algorithm>
#include <map>
#include <set>

#define MOD 1000000007
#define MAXN 50010
#define ll long long

using namespace std;

int k;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int v) : v(v) {}
    mi &operator+=(const mi &m2) {
        v += m2.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    mi operator+(const mi &m2) {
        mi m(v);
        return m += m2;
    }
    mi &operator*=(const mi &m2) {
        v = (ll)v * m2.v % MOD;
        return *this;
    }
    mi operator*(const mi &m2) {
        mi m(v);
        return m *= m2;
    }
};

struct segtree {
    vector<mi> st;
    segtree() {
        st.assign(4 * k, mi(0));
    }
    void upd(int x, int y, int v = 1, int l = 0, int r = k - 1) {
        if (l == r) {
            st[v] += y;
        } else {
            int m = (l + r) / 2;
            if (x <= m) {
                upd(x, y, 2 * v, l, m);
            } else {
                upd(x, y, 2 * v + 1, m + 1, r);
            }
            st[v] = st[2 * v] * st[2 * v + 1];
        }
    }
    mi qry(int x, int y, int v = 1, int l = 0, int r = k - 1) {
        if (x <= l && r <= y) {
            return st[v];
        } else if (y < l || x > r) {
            return mi(1);
        } else {
            int m = (l + r) / 2;
            return qry(x, y, 2 * v, l, m) * qry(x, y, 2 * v + 1, m + 1, r);
        }
    }
    mi qry_wo(int x) {
        mi ans(1);
        if (x) ans *= qry(0, x - 1);
        if (x != k - 1) ans *= qry(x + 1, k - 1);
        return ans;
    }
};

vector<pair<int, int>> odd_tot;
vector<pair<int, int>> odd_pref;
vector<pair<int, int>> even_tot;
vector<pair<int, int>> even_pref;
vector<pair<int, pair<int, int>>> both_pref;

struct graph {
    int n, m;
    vector<vector<int>> adj;
    vector<array<int, 2>> dist; // even / odd distance
    vector<array<int, 2>> vis;

    graph(int n, int m) : n(n), m(m) {
        adj.resize(n);
        dist.assign(n, {-1, -1});
        vis.resize(n);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void bfs() {
        queue<array<int, 2>> q;
        q.push({0, 0});
        dist[0][0] = 0;
        vis[0][0] = true;

        while (!q.empty()) {
            auto t = q.front();
            q.pop();
            int pos = t[0];
            int d = t[1];

            for (int e : adj[pos]) {
                if (!vis[e][(d + 1) & 1]) {
                    vis[e][(d + 1) & 1] = true;
                    dist[e][(d + 1) & 1] = d + 1;
                    q.push({e, d + 1});
                }
            }
        }
    }

    void calc_categories(int idx) {
        for (int i = 0; i < n; i++) {
            if (dist[i][0] == -1 && dist[i][1] == -1) continue;
            if (dist[i][0] == -1) {
                odd_tot.push_back({dist[i][1], idx});
            } else if (dist[i][1] == -1) {
                even_tot.push_back({dist[i][0], idx});
            } else {
                odd_tot.push_back({dist[i][1], idx});
                odd_pref.push_back({dist[i][1], idx});
                even_tot.push_back({dist[i][0], idx});
                even_pref.push_back({dist[i][0], idx});
                both_pref.push_back({dist[i][0], {idx, i}});
                both_pref.push_back({dist[i][1], {idx, i}});
            }
        }
    }
};

vector<graph> graphs;
mi ans;

mi calc(vector<pair<int, int>> &cur) {
    mi res;
    segtree st;
    sort(cur.begin(), cur.end());
    for (auto p : cur) {
        st.upd(p.second, 1);
        res += mi(p.first) * st.qry_wo(p.second);
    }
    return res;
}

mi calc_2(vector<pair<int, pair<int, int>>> &cur) {
    mi res;
    segtree odd, even, both;
    sort(cur.begin(), cur.end());
    set<pair<int, int>> used;

    for (auto p : cur) {
        if (p.first % 2 == 0) {
            mi q = even.qry_wo(p.second.first);
            even.upd(p.second.first, 1);
            if (used.count(p.second)) {
                q += mi(MOD - 1) * both.qry_wo(p.second.first);
                both.upd(p.second.first, 1);
            } else {
                used.insert(p.second);
            }
            res += mi(p.first) * q;
        } else {
            mi q = odd.qry_wo(p.second.first);
            odd.upd(p.second.first, 1);
            if (used.count(p.second)) {
                q += mi(MOD - 1) * both.qry_wo(p.second.first);
                both.upd(p.second.first, 1);
            } else {
                used.insert(p.second);
            }
            res += mi(p.first) * q;
        }
    }

    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> k;

    for (int i = 0; i < k; i++) {
        int n, m; cin >> n >> m;
        graphs.emplace_back(n, m);
        graph &cur = graphs.back();

        for (int j = 0; j < m; j++) {
            int a, b; cin >> a >> b;
            a--; b--;
            cur.add_edge(a, b);
        }

        cur.bfs();
        cur.calc_categories(i);
    }

    ans += calc(odd_tot);
    ans += mi(MOD - 1) * calc(odd_pref);
    ans += calc(even_tot);
    ans += mi(MOD - 1) * calc(even_pref);
    ans += calc_2(both_pref);

    cout << ans.v << '\n';

    return 0;
}

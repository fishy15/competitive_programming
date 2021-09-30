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

struct tree {
    int n;
    vector<vector<int>> adj;
    vector<vector<int>> add;
    vector<vector<int>> rem;
    int ans = 0;
    tree(int n) : n(n), adj(n), add(n), rem(n), in(n), out(n), up(n, array<int, 20>{}) {}

    vector<int> in, out;
    vector<array<int, 20>> up;

    void add_edge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    void dfs() {
        int t = 1;
        dfs(0, 0, t);
    }

    void dfs(int v, int p, int &t) {
        in[v] = t++;
        up[v][0] = p;
        for (int i = 1; i < 20; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }

        for (int e : adj[v]) {
            if (e != p) {
                dfs(e, v, t);
            }
        }

        out[v] = t++;
    }

    bool anc(int a, int b) {
        return in[a] <= in[b] && out[b] <= out[a];
    }

    int lca(int a, int b) {
        if (anc(a, b)) return a;
        if (anc(b, a)) return b;
        for (int i = 19; i >= 0; i--) {
            if (!anc(up[b][i], a)) {
                b = up[b][i];
            }
        }
        return up[b][0];
    }

    int dfs2() {
        dfs2(0, 0);
        return ans;
    }

    set<int> dfs2(int v, int p) {
        set<int> cur;
        for (int e : adj[v]) {
            if (e != p) {
                auto res = dfs2(e, v);
                if (res.empty()) ans++;
                if (res.size() > cur.size()) swap(res, cur);
                for (int i : res) cur.insert(i);
            }
        }

        for (int i : add[v]) {
            cur.insert(i);
        }

        for (int i : rem[v]) {
            cur.erase(i);
        }

        return cur;
    }
};

void solve() {
    int n; cin >> n;
    tree t(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        t.add_edge(a, b);
    }

    t.dfs();
    vector<int> freq(n, -1);
    for (int i = 0; i < n; i++) {
        int f; cin >> f;
        f--;
        if (freq[f] == -1) {
            freq[f] = i;
        } else {
            freq[f] = t.lca(i, freq[f]);
        }
        t.add[i].push_back(f);
    }

    for (int i = 0; i < n; i++) {
        if (freq[i] != -1) {
            t.rem[freq[i]].push_back(i);
        }
    }

    cout << t.dfs2() << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

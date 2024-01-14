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
#define MAXN 1000000

using namespace std;

#define sz(x) (int) (x).size()
#define rep(i, a, b) for (int i = (a); i < (b); i++)

using vi = vector<int>;
vi val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
    int low = val[j] = ++Time, x; z.push_back(j);
    for (auto e : g[j]) if (comp[e] < 0)
        low = min(low, val[e] ?: dfs(e,g,f));

    if (low == val[j]) {
        do {
            x = z.back(); z.pop_back();
            comp[x] = ncomps;
            cont.push_back(x);
        } while (x != j);
        f(cont); cont.clear();
        ncomps++;
    }
    return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
    int n = sz(g);
    val.assign(n, 0); comp.assign(n, -1);
    Time = ncomps = 0;
    rep(i,0,n) if (comp[i] < 0) dfs(i, g, f);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector adj_nopass(n, vector<int>());
    vector radj_all(n, vector<int>());

    for (int i = 0; i < m; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        u--;
        v--;

        if (t == 2) {
            adj_nopass[u].push_back(v);
        }

        radj_all[v].push_back(u);
    }

    vector<bool> valid(n);
    queue<int> q;
    auto check = [&](const vector<int> &cc) {
        set in_cc(cc.begin(), cc.end());
        bool is_valid = false;
        for (auto v : cc) {
            for (auto x : adj_nopass[v]) {
                if (!in_cc.count(x)) {
                    is_valid = true;
                    goto marking;
                }
            }
        }

marking:
        if (is_valid) {
            for (auto v : cc) {
                valid[v] = true;
                q.push(v);
            }
        }
    };

    scc(adj_nopass, check); 

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (auto e : radj_all[v]) {
            if (!valid[e]) {
                valid[e] = true;
                q.push(e);
            }
        }
    }

    if (valid[0]) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}

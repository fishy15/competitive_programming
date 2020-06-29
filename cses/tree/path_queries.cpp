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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

int n, q;
int vals[MAXN];
vector<int> adj[MAXN];
ll bit[2 * MAXN];
int in[MAXN];
int out[MAXN];
int t = 1;

void upd(int x, int v) {
    while (x < 2 * MAXN) {
        bit[x] += v;
        x += x & -x;
    }
}

ll qry(int x) {
    ll res = 0;
    while (x) {
        res += bit[x];
        x -= x & -x;
    }
    return res;
}

void dfs(int v, int p) {
    in[v] = t++;
    upd(in[v], vals[v]);
    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v);
        }
    }
    out[v] = t++;
    upd(out[v], -vals[v]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> vals[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, 0);
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int s, x; cin >> s >> x;
            s--;
            upd(in[s], -vals[s]);
            upd(out[s], vals[s]);
            vals[s] = x;
            upd(in[s], vals[s]);
            upd(out[s], -vals[s]);
        } else {
            int s; cin >> s;
            s--;
            cout << qry(in[s]) << '\n';
        }
    }

    return 0;
}

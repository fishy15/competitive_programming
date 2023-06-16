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
#define MAXN 200010

using namespace std;

int n, q;
vector<int> adj[MAXN];
pair<int, int> edge[MAXN];
int par[MAXN];
ll pref[2 * MAXN];
int in[MAXN];
int out[MAXN];
int t = 1;

void dfs(int v, int p) {
    in[v] = t++;
    par[v] = p;
    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v);
        }
    }
    out[v] = t++;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
        edge[i] = {a, b};
    }

    dfs(0, -1);

    cin >> q;
    for (int i = 0; i < q; i++) {
        int t, e, x; cin >> t >> e >> x;
        e--;
        int a = edge[e].first;
        int b = edge[e].second;
        if (t == 2) swap(a, b);
        if (par[a] == b) {
            pref[in[a]] += x;
            pref[out[a] + 1] -= x;
        } else {
            pref[1] += x;
            pref[in[b]] -= x;
            pref[out[b] + 1] += x;
        }
    }

    for (int i = 1; i <= 2 * n; i++) {
        pref[i] += pref[i - 1];
    }

    for (int i = 0; i < n; i++) {
        cout << pref[in[i]] << '\n';
    }

    return 0;
}

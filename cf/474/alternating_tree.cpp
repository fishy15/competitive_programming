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

int n;
int val[MAXN];
vector<int> adj[MAXN];
int below[MAXN][2];
int sz[MAXN];
ll ans;

void dfs(int v, int p) {
    below[v][0] = 1;
    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v);
            below[v][1] += below[e][0];
            below[v][0] += below[e][1];
        }
    }
}

void dfs2(int v, int p, int even, int odd) {
    vector<array<int, 2>> combo = {{even, odd}};
    for (int e : adj[v]) {
        if (e != p) {
            combo.push_back({below[e][1], below[e][0]});
        }
    }

    for (auto [e, o] : combo) {
        ans -= (ll) val[v] * o % MOD * (n - e - o) % MOD; 
        if (ans >= MOD) ans -= MOD;
        if (ans < 0) ans += MOD;
        ans += (ll) val[v] * e % MOD * (n - e - o) % MOD;
        if (ans >= MOD) ans -= MOD;
        if (ans < 0) ans += MOD;
    }

    ans += (ll) val[v] * n % MOD;
    if (ans >= MOD) ans -= MOD;
    if (ans < 0) ans += MOD;

    // recurse into children
    combo.clear();
    for (int e : adj[v]) {
        if (e != p) {
            int tot_even = odd + below[v][1] - below[e][0];
            int tot_odd = even + below[v][0] - below[e][1];
            dfs2(e, v, tot_even, tot_odd);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, 0);
    dfs2(0, 0, 0, 0);

    cout << ans << '\n';

    return 0;
}

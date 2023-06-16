// :pray: :steph:
// :pray: :bakekaga:

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
#define MAXN 300000
#define MAXBIT (2 * MAXN + 1)

using namespace std;

int n, m;
vector<int> adj[MAXN + 1];
vector<pair<int, int>> q[MAXN + 1];

ll bit[MAXBIT];
ll ans[MAXN + 1];
int d = 1;

void update(int x, int v) {
    while (x <= MAXBIT) {
        bit[x] += v;
        x += (x & -x);
    }
}

ll query(int x) {
    ll ans = 0;
    while (x > 0) {
        ans += bit[x];
        x -= (x & -x);
    }

    return ans;
}

void dfs(int v, int p) {
    for (auto qq : q[v]) {
        update(d, qq.second);
        update(d + qq.first + 1, -qq.second);
    }

    ans[v] = query(d);
    d++;

    for (int i : adj[v]) {
        if (i != p) {
            dfs(i, v);
        }
    }

    d--;

    for (auto qq : q[v]) {
        update(d, -qq.second);
        update(d + qq.first + 1, qq.second);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    cin >> m;

    for (int i = 0; i < m; i++) {
        int v, d, x; cin >> v >> d >> x;
        q[v].push_back({d, x});
    }

    dfs(1, 0);

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }

    cout << '\n';

    return 0;
}

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
#define MAXN 200000
#define MAXBIT (2 * MAXN + 1)

using namespace std;

int n;
int val[MAXN + 1];
vector<int> adj[MAXN + 1];

int in[MAXN + 1];
int out[MAXN + 1];
int t = 1;
ll d;

ll pre[MAXBIT];

ll cur;
ll ans;

void dfs(int v, int p) {
    in[v] = t++;

    cur += val[v] * d;
    d++;

    for (int i : adj[v]) {
        if (i != p) {
            dfs(i, v);
        }
    }

    d--;
    out[v] = t++;
}

void dfs2(int v, int p) {
    ans = max(ans, cur);

    for (int i : adj[v]) {
        if (i != p) {
            ll sum1 = pre[out[i]] - pre[in[i] - 1];
            ll sum2 = pre[out[1]] - sum1;
            cur -= sum1;
            cur += sum2;
            dfs2(i, v);
            cur -= sum2;
            cur += sum1;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);

    for (int i = 1; i <= n; i++) {
        pre[in[i]] = val[i];
    }

    for (int i = 1; i < MAXBIT; i++) {
        pre[i] += pre[i - 1];
    }

    dfs2(1, 0);

    cout << ans << '\n';

    return 0;
}

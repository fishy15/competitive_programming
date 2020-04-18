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
#define MAXN 1000000

using namespace std;

int n;
vector<int> adj[MAXN + 1];
bool leaf[MAXN + 1];
int d[MAXN + 1];
int par[2];
int mm;

void dfs(int v, int p) {
    if (adj[v].size() == 1) leaf[v] = true;
    d[v] = d[p] + 1;
    if (leaf[v]) par[d[v] % 2]++;

    int cnt = 0;
    for (int e : adj[v]) {
        if (e != p) dfs(e, v);
        if (leaf[e]) cnt++;
    }

    mm += max(cnt - 1, 0);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);

    if (par[0] && par[1]) {
        cout << "3 ";
    } else {
        cout << "1 ";
    }
    cout << n - mm - 1 << '\n';

    return 0;
}

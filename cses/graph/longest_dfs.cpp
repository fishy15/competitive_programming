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
#define MAXN 100000

using namespace std;

int n, m;
vector<int> adj[MAXN + 1];
int p[MAXN + 1];
int ans = -1;
int dist;

void dfs(int pos) {
    if (pos == n) {
        ans = max(ans, dist);
    } else {
        dist++;
        for (int i : adj[pos]) {
            dfs(i);
        }
        dist--;
    }
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
    }

    dfs(0);
    if (ans != -1) {
        cout << ans << '
    }
    cout << ans << '\n';

    return 0;
}

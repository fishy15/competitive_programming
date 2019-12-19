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
vector<int> radj[MAXN + 1];
int deg[MAXN + 1];
int dp[MAXN + 1];
int p[MAXN + 1];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        radj[b].push_back(a);
        deg[a]++;
    }

    queue<int> no_out;

    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) {
            no_out.push(i);
        }
    }

    vector<int> order;
    while (!no_out.empty()) {
        int pos = no_out.front();
        no_out.pop();
        order.push_back(pos);

        for (int i : radj[pos]) {
            deg[i]--;
            if (deg[i] == 0) {
                no_out.push(i);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (i == n) {
            dp[i] = 1;
        } else {
            dp[i] = 0;
        }
    }

    for (int i : order) {
        for (int j : adj[i]) {
            dp[i] += dp[j];
            if (dp[i] > MOD) dp[i] -= MOD;
        }
    }

    cout << dp[1] << '\n';

    return 0;
}

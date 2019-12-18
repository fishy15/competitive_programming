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

    int qqqq = 0;
    while (order[qqqq] != n) qqqq++;
    dp[qqqq] = 1;
    for (int i : radj[5]) cout << i << ' '; cout << '\n';
    for (int k = qqqq + 1; k < n; k++)  {
        int i = order[k];
        for (int j : adj[i]) {
            if (dp[j] + 1 > dp[i] && dp[j]) {
                p[i] = j;
                dp[i] = dp[j] + 1;
            }
        }

        cout << i << ' ' << dp[i] << ' ' << p[i] << '\n';
    }

    if (dp[1] == 0) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> ans_pos;
    int pos = 1;
    while (pos != 0) {
        ans_pos.push_back(pos);
        pos = p[pos];
    }

    cout << dp[1] << '\n';
    for (int i = dp[1] - 1; i >= 0; i--) {
        cout << ans_pos[i] << ' ';
    } cout << '\n';

    return 0;
}

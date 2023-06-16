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
vector<int> adj[MAXN];
map<int, int> used[MAXN][4];
vector<int> no_2_conn[MAXN];
int dp[MAXN][4];
int pp[MAXN];

void dfs(int v, int p, int dd) {
    pair<int, int> max_diff = {0, -1};
    if (dd >= 2) dp[v][1] = 1;
    pp[v] = p;
    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v, dd + 1);
            int b = 0;
            if (dp[e][0] < dp[e][3]) b = 3;
            if (dp[e][b] < dp[e][2]) b = 2;

            dp[v][0] += dp[e][b];
            dp[v][1] += dp[e][b];
            used[v][0][e] = b;
            used[v][1][e] = b;

            dp[v][3] += dp[e][b];
            used[v][3][e] = b;
            if (b != 2) no_2_conn[v].push_back(e);

            dp[v][2] += dp[e][b];
            used[v][2][e] = b;
            if (max_diff.first < dp[e][1] - dp[e][b]) {
                max_diff.first = dp[e][1] - dp[e][b];
                max_diff.second = e;
            }
        }
    }

    dp[v][0] += no_2_conn[v].size() / 2;
    dp[v][1] += no_2_conn[v].size() / 2;
    dp[v][3] += no_2_conn[v].size() / 2;

    if (max_diff.second != -1) {
        if (find(no_2_conn[v].begin(), no_2_conn[v].end(), max_diff.second) == no_2_conn[v].end()) {
            dp[v][2] += no_2_conn[v].size() / 2;
        } else {
            dp[v][2] += (no_2_conn[v].size() - 1) / 2;
        }
        dp[v][2] += max_diff.first;
        used[v][2][max_diff.second] = 1;
    }
}

void dfs2(int v, int p, int cur) {
    int nxt_1 = -1;
    if (cur == 1) {
        cout << v + 1 << ' ' << pp[pp[v]] + 1 << '\n';
    }
    for (int e : adj[v]) {
        if (e != p) {
            if (used[v][cur][e] == 1) nxt_1 = e;
            dfs2(e, v, used[v][cur][e]);
        }
    }

    vector<int> &cc = no_2_conn[v];
    if (cur == 2 && find(cc.begin(), cc.end(), nxt_1) != cc.end()) {
        cc.erase(find(cc.begin(), cc.end(), nxt_1));    
    }
    for (int i = 0; i + 1 < (int)cc.size(); i += 2) {
        cout << cc[i] + 1 << ' ' << cc[i + 1] + 1 << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, -1, 0);
    int best = max_element(dp[0], dp[0] + 4) - dp[0];
    cout << dp[0][best] << '\n';
    dfs2(0, -1, best);

    return 0;
}

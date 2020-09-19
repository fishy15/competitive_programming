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
vector<int> req[MAXN + 1];
int dp[2 * MAXN + 10];
int deg[MAXN + 1];

int t = 0;
int in[MAXN + 1];
int out[MAXN + 1];
int ord[2 * MAXN + 10];
int ans[MAXN + 1];
int up[MAXN + 1][18];

void dfs(int v, int p) {
    in[v] = t++;

    up[v][0] = p;
    for (int i = 1; i < 18; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }

    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v); 
        }
    }

    out[v] = t++;
}

bool anc(int p, int c) {
    return in[p] <= in[c] && out[c] <= out[p];
}

int main() {
    ifstream fin("gathering.in");
    ofstream fout("gathering.out");

    fin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int a, b; fin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        deg[a]++;
        deg[b]++;
    }

    dfs(1, 1);

    for (int i = 1; i <= n; i++) {
        ord[in[i]] = i;
        ord[out[i]] = -i;
        int a, b; fin >> a >> b;
        deg[b]++;
        req[a].push_back(b);
        if (anc(a, b)) {
            dp[in[1]]++;
            dp[out[1] + 1]--;

            for (int i = 17; i >= 0; i--) {
                if (!anc(up[b][i], a)) {
                    b = up[b][i];
                }
            }

            dp[in[b]]--;
            dp[out[b] + 1]++;
        } else {
            dp[in[a]]++;
            dp[out[a] + 1]--;
        } 
    }

    for (int i = 0; i <= out[1]; i++) {
        if (i > 0) {
            dp[i] += dp[i - 1];
        }

        if (ord[i] > 0) {
            ans[ord[i]] = dp[i] == 0 ? 1 : 0;
        }
    }

    int cc = 0;
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        cc++;

        for (int e : adj[x]) {
            deg[e]--;
            if (deg[e] == 1) {
                q.push(e);
            }
        }

        for (int e : req[x]) {
            deg[e]--;
            if (deg[e] == 1) {
                q.push(e);
            }
        }
    }

    if (cc < n) {
        for (int i = 1; i <= n; i++) {
            fout << "0\n";
        }
    } else {
        for (int i = 1; i <= n; i++) {
            fout << ans[i] << '\n';
        }
    }

    return 0;
}

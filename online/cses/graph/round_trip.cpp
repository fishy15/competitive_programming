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

using namespace std;

int n, m;
vector<int> adj[MAXN + 1];
int in[MAXN + 1];
int out[MAXN + 1];
int par[MAXN + 1];
int t = 1;

vector<int> ans;

void dfs(int v, int p) {
   par[v] = p;
   in[v] = t++;

   for (int e : adj[v]) {
       if (!in[e]) {
            dfs(e, v);
       } else if (e != p && !out[e] && ans.empty()) {
            int cur = v;
            ans = {e};
            while (cur != e) {
                ans.push_back(cur);
                cur = par[cur];
            }
            ans.push_back(e);
       }
   }

   out[v] = t++;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        if (!in[i]) {
            dfs(i, 0);
            if (!ans.empty()) {
                cout << ans.size() << '\n';
                for (int j : ans) {
                    cout << j << ' ';
                } cout << '\n';
                return 0;
            }
        }
    }

    cout << "IMPOSSIBLE\n";

    return 0;
}

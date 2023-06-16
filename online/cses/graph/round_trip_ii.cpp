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
vector<int> adj[MAXN];
int pp[MAXN];
int in[MAXN];
int out[MAXN];
int t = 1;

bool dfs(int v, int p) {
    in[v] = t++;
    pp[v] = p;

    for (int e : adj[v]) {
        if (!in[e]) {
            if (dfs(e, v)) return true;
        } else if (!out[e]) {
            vector<int> ans = {e, v};
            int cur = v;
            while (cur != e) {
                cur = pp[cur];
                ans.push_back(cur);
            }
            reverse(ans.begin(), ans.end());
            cout << ans.size() << '\n';
            for (int i : ans) {
                cout << i + 1 << ' ';
            } 
            cout << '\n';
            return true;
        }
    }

    out[v] = t++;
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
    }

    for (int i = 0; i < n; i++) {
        if (!in[i]) {
            if (dfs(i, -1)) return 0;
        }
    }

    cout << "IMPOSSIBLE\n";

    return 0;
}

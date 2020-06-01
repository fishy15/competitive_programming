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
#include <deque>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n, m;
set<int> adj[MAXN];
int deg[MAXN];
deque<int> ans;

void dfs(int v, int p) {
    while (!adj[v].empty()) {
        int i = *adj[v].begin();
        adj[v].erase(i);
        adj[i].erase(v);
        dfs(i, v);
    }
    ans.push_front(v); 
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].insert(b);
        adj[b].insert(a);
        deg[a]++;
        deg[b]++;
    }

    for (int i = 0; i < n; i++) {
        if (deg[i] % 2 != 0) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    dfs(0, -1);

    if (ans.size() != m + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i : ans) {
        cout << i + 1 << ' ';
    } cout << '\n';

    return 0;
}

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
#define MAXN 400000

using namespace std;

int n, m;
vector<int> adj[MAXN];
deque<int> ans;
int pos[MAXN];

void dfs(int v) {
    while (pos[v]) {
        dfs(adj[v][--pos[v]]);
    }
    ans.push_front(v);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    if (n == 1) {
        cout << "01\n";
        return 0;
    }

    m = 1 << (n - 1);

    for (int i = 0; i < m; i++) {
        int x = (i << 1) & (m - 2);
        adj[i].push_back(x);
        adj[i].push_back(x + 1);
        pos[i] = adj[i].size();
    }

    dfs(0);

    for (int i = 0; i < n - 2; i++) {
        cout << '0';
    }

    for (int i : ans) {
        cout << (i & 1);
    }
    
    cout << '\n';

    return 0;
}

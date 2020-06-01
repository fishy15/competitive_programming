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

int n, m;
vector<int> adj[MAXN];
int in[MAXN];
int out[MAXN];
deque<int> ans;

void dfs(int v) {
    while (out[v]) {
        dfs(adj[v][--out[v]]);
    }
    ans.push_front(v);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        out[a]++;
        in[b]++;
    }

    if (in[0] + 1 != out[0]) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    if (out[n - 1] + 1 != in[n - 1]) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 1; i < n - 1; i++) {
        if (in[i] != out[i]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    dfs(0);

    if (ans.size() != m + 1) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int i : ans) {
            cout << i + 1 << ' ';
        }
        cout << '\n';
    }

    return 0;
}

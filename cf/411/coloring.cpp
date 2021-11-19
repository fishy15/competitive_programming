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
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 300010

using namespace std;

int n, m;
vector<int> adj[MAXN];
vector<int> color[MAXN];
int col[MAXN];

void dfs(int v, int p) {
    set<int> cur;
    for (int x : color[v]) {
        if (col[x] != 0) {
            cur.insert(col[x]);
        }
    }

    int ptr = 1;
    for (int x : color[v]) {
        if (col[x] == 0) {
            while (cur.find(ptr) != cur.end()) {
                ptr++;
            }

            col[x] = ptr;
            ptr++;
        }
    }

    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    
    for (int i = 0; i < n; i++) {
        int s; cin >> s;
        for (int j = 0; j < s; j++) {
            int c; cin >> c;
            c--;
            color[i].push_back(c);
        }
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, 0);

    int mc = 1;
    for (int i = 0; i < m; i++) {
        if (col[i] == 0) col[i] = 1;
        mc = max(mc, col[i]);
    }
    
    cout << mc << '\n';
    for (int i = 0; i < m; i++) {
        cout << col[i] << ' ';
    }
    cout << '\n';

    return 0;
}

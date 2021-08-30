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
#define MAXN 1000000

using namespace std;

int n, k;
vector<int> adj[MAXN];
int ans;

int dfs_root(int v, int p) {
    if ((int) adj[v].size() >= 2) {
        return v; 
    } else {
        for (int e : adj[v]) {
            if (e != p) {
                int res = dfs_root(e, v);
                if (res != -1) {
                    return res;
                }
            }
        }
        return -1;
    }
}

int dfs(int v, int p, int d) {
    if ((int) adj[v].size() == 1) {
        return d;
    } else {
        vector<int> depths;
        for (int e : adj[v]) {
            if (e != p) {
                depths.push_back(dfs(e, v, d + 1));
            }
        }

        sort(depths.rbegin(), depths.rend());

        int sz = depths.size();
        while (sz >= 2 && (depths[sz - 1] + depths[sz - 2] - 2 * d) <= k) {
            depths.pop_back();
            sz--;
        }

        ans += depths.size() - 1;
        return depths.back();
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int root = dfs_root(0, 0);
    dfs(root, root, 0);

    cout << ans + 1 << '\n';

    return 0;
}

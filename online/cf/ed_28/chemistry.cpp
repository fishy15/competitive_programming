/*
 * Due to the constraint that x_i < i, this forms a tree, so we can recursively solve by starting at the 
 * leaves and working our way up. The only reason why this problem is rated 2300 is because knowing how to get
 * around long long overflow (saying NO if any value is less than -2e17) is needed.
 */
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
#define MAXN 100010

using namespace std;

int n;
pair<int, ll> par[MAXN];
vector<int> adj[MAXN];
ll need[MAXN];
ll cur[MAXN];

ll bad(ll a, ll b) {
    double x = (double)a * b;
    if (x < -2e17) {
        cout << "NO\n";
        exit(0);
    }
    return a * b;
}

ll dfs(int v) {
    for (int e : adj[v]) {
        cur[v] += dfs(e);
        bad(cur[v], 1);
    }

    ll diff = cur[v] - need[v];
    if (diff >= 0) {
        return bad(diff, 1);
    } else {
        return bad(diff, par[v].second);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> cur[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> need[i];
    }
    
    for (int i = 1; i < n; i++) {
        cin >> par[i].first >> par[i].second;
        par[i].first--;
        adj[par[i].first].push_back(i);
    }

    par[0].second = 1;
    dfs(0);

    if (need[0] > cur[0]) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }

    return 0;
}

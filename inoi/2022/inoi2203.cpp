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
#define MAXN 2010
#define LIMIT 15000

using namespace std;

int n, m, p;
vector<int> adj[MAXN];
bool vis[MAXN];

void solve_complete() {
    cout << n << '\n';
    string res(n, '0');
    for (int i = 1; i < n; i++) {
        res[i] = '1';
        cout << res << '\n';
        res[i] = '0';
    }
    res[1] = '1';
    res[n - 1] = '1';
    cout << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    if (n == 2) {
        cout << "1\n";
        cout << "01\n";
        return 0;
    }

    if (m == n * (n - 1) / 2) {
        solve_complete();
        return 0;
    }

    cout << "0\n";

    return 0;
}

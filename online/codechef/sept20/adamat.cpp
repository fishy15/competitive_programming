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

void solve() {
    int n; cin >> n;
    vector<vector<ll>> m(n);

    for (int i = 0; i < n; i++) {
        m[i].resize(n);
        for (int j = 0; j < n; j++) {
            cin >> m[i][j];
        }
    }
    
    bool flip = false;
    int ans = 0;
    for (int i = n - 1; i > 0; i--) {
        bool res = flip ? m[0][i] < m[i][0] : m[0][i] > m[i][0];
        if (res) {
            flip = !flip;
            ans++;
        }
    }
    
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

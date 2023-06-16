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
    int n, m; cin >> n >> m;

    vector<int> k(n);
    vector<int> c(m);

    for (int i = 0; i < n; i++) {
        cin >> k[i];
        k[i]--;
    }

    sort(k.begin(), k.end());

    for (int i = 0; i < m; i++) {
        cin >> c[i];
    }

    int cur_idx = 0;
    ll ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (cur_idx < k[i]) {
            ans += c[cur_idx++];
        } else {
            ans += c[k[i]];
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

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
#include <numeric>

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
    int n, c; cin >> n >> c;
    if (c < n - 1 || n * (n + 1) / 2 - 1 < c) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    vector<int> ans(n);
    iota(ans.begin(), ans.end(), 1);
    
    c -= n - 1;
    for (int i = n - 2; i >= 0; i--) {
        int sw = min(c, n - i - 1);
        reverse(ans.begin() + i, ans.begin() + i + sw + 1);
        c -= sw;
    }

    for (int x : ans) {
        cout << x << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

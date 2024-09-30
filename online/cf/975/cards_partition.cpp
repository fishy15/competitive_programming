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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

void solve() {
    int n;
    ll k;
    cin >> n >> k;

    vector<ll> a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }

    auto biggest = *max_element(all(a));
    auto total = accumulate(all(a), 0LL);
    for (int size = n; size >= 1; size--) {
        auto new_total = (total + k) / size * size;
        if (new_total >= total && biggest * size <= new_total) {
            cout << size << '\n';
            return;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

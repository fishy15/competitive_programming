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
#define MAXN 1000000

using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    vector<int> sub(n);
    for (auto &x : a) {
        cin >> x;
    }

    for (int i = 0; i < n; i++) {
        sub[i] = a[i] - i;
    }

    ll cur = 1;
    for (int i = k - 1; i >= 0; i--) {
        auto it = upper_bound(sub.begin(), sub.end(), cur);
        if (it != sub.begin()) {
            cur += it - sub.begin();
        }
    }

    cout << cur << '\n';
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

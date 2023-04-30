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
    ll n, m, k; cin >> n >> m >> k;

    vector<ll> a(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }

    ll row = 0;
    ll col = 0;

    bool row_cnt = false;
    bool col_cnt = false;

    for (int i = 0; i < k; i++) {
        if (a[i] / n >= 2) {
            row += a[i] / n;
            if (a[i] / n >= 3) {
                row_cnt = true;
            }
        }

        if (a[i] / m >= 2) {
            col += a[i] / m;
            if (a[i] / m >= 3) {
                col_cnt = true;
            }
        }
    }

    if ((row >= m && (row_cnt ? m > 1 : m % 2 == 0)) || (col >= n && (col_cnt ? n > 1 : n % 2 == 0))) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

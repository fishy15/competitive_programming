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
    int n;
    cin >> n;

    vector<int> a(n);
    vector<int> b(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    vector<ll> type1, type2;

    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            type1.push_back(b[i]);
        } else {
            type2.push_back(b[i]);
        }
    }

    sort(type1.rbegin(), type1.rend());
    sort(type2.rbegin(), type2.rend());

    ll ans = 0;

    if (type1.empty() || type2.empty()) {
        ans = accumulate(type1.begin(), type1.end(), 0LL) 
            + accumulate(type2.begin(), type2.end(), 0LL);
    } else {
        for (int i = 0; i < 2; i++) {
            ll cur = 0;

            if (type1.size() > 1) {
                rotate(type1.begin(), type1.end() - 1, type1.end());
            }

            cur += type1[0];
            cur += 2 * type2[0];

            int sz = min(type1.size(), type2.size());
            for (int i = 1; i < sz; i++) {
                cur += 2 * type1[i];
                cur += 2 * type2[i];
            }

            if (type1.size() > type2.size()) {
                cur += accumulate(type1.begin() + sz, type1.end(), 0LL);
                cur += type1[sz];
            } else {
                cur += accumulate(type2.begin() + sz, type2.end(), 0LL);
            }

            ans = max(ans, cur);

            if (type1.size() > 1) {
                rotate(type1.begin(), type1.begin() + 1, type1.end());
            }

            swap(type1, type2);
        }
    }

    cout << ans << '\n';
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

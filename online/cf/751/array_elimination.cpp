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
    for (auto &x : a) {
        cin >> x;
    }

    array<int, 30> cnt{};
    for (auto x : a) {
        for (int i = 0; i < 30; i++) {
            if (((x >> i) & 1) == 1) {
                cnt[i]++;
            }
        }
    }

    int ans = 0;
    for (auto x : cnt) {
        ans = gcd(ans, x);
    }

    for (int i = 1; i <= n; i++) {
        if (ans % i == 0) {
            cout << i << ' ';
        }
    }
    cout << '\n';
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

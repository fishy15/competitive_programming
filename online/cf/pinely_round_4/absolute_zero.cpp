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
    cin >> n;

    vector<int> a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }

    bool same_parity = true;
    rep(i, 1, n) {
        if (a[0] % 2 != a[i] % 2) {
            same_parity = false;
            break;
        }
    }

    vector<int> xs;
    auto apply_x = [&](int x) {
        xs.push_back(x);
        rep(i, 0, n) {
            a[i] = abs(a[i] - x);
        }
    };

    if (same_parity) {
        while (true) {
            auto mx = *max_element(all(a));
            if (mx == 0) {
                break;
            }

            if (mx == 1) {
                apply_x(1);
            } else {
                apply_x(mx / 2);
            }
        }

        cout << sz(xs) << '\n';
        for (auto x : xs) {
            cout << x << ' ';
        }
        cout << '\n';
    } else {
        cout << "-1\n";
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

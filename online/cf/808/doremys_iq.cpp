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
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }

    int l = 0;
    int r = n;
    int ans = n;

    auto check = [&](int skip) {
        int cur_q = q;
        for (auto x : a) {
            if (cur_q == 0) {
                return false;
            }
            if (x > cur_q) {
                if (skip > 0) {
                    skip--;
                } else {
                    cur_q--;
                }
            }
        }

        return true;
    };

    auto pr = [&](int skip) {
        int cur_q = q;
        for (auto x : a) {
            if (x > cur_q) {
                if (skip > 0) {
                    skip--;
                    cout << 0;
                } else {
                    cout << 1;
                }
            } else {
                cout << 1;
            }
        }
    };

    while (l <= r) {
        int m = (l + r) / 2;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    pr(ans);
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

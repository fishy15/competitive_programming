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

template<typename T>
struct BIT {
    int n;
    vector<T> bit;

    BIT(int n) : n(n), bit(n + 1) {}

    void upd(int x, int v) {
        x++;
        while (x <= n) {
            bit[x] += v;
            x += x & -x;
        }
    }

    T qry(int r) {
        T res{};
        while (r > 0) {
            res += bit[r];
            r -= r & -r;
        }
        return res;
    }

    T qry(int l, int r) {
        return qry(r) - qry(l);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    ll k;
    cin >> n >> k;

    vector<pair<int, int>> pts(n);
    for (auto &p : pts) {
        cin >> p.first >> p.second;
    }

    sort(pts.begin(), pts.end());

    auto check = [&](ll m) {
        int l = 0;
        int r = 0;

        BIT<int> bit(100'010);
        ll ans = 0;
        for (auto p : pts) {
            while (l < n && pts[l].first < p.first - m) {
                bit.upd(pts[l].second, -1);
                l++;
            }

            while (r < n && pts[r].first <= p.first + m) {
                bit.upd(pts[r].second, 1);
                r++;
            }

            int lower = max(0LL, p.second - m);
            int upper = min(100'000LL, p.second + m);
            ans += bit.qry(lower, upper + 1);
    }

        return ((ans - n) / 2) >= k;
    };

    ll l = 0;
    ll r = 1e5;
    ll ans = -1;

    while (l <= r) {
        auto m = l + (r - l) / 2;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    cout << ans << '\n';

    return 0;
}

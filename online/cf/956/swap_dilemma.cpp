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

ll inversions(const vector<int> &nums) {
    vector<int> cc = nums;
    sort(cc.begin(), cc.end());
    cc.erase(unique(cc.begin(), cc.end()), cc.end());

    auto g = [&](int x) { return lower_bound(cc.begin(), cc.end(), x) - cc.begin(); };
    int sz = (int) cc.size();

    BIT<int> bit(sz);
    ll ans = 0;

    for (auto x : nums) {
        auto idx = g(x);
        ans += bit.qry(idx+1, sz);
        bit.upd(idx, 1);
    }

    return ans;
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;

    if (inversions(a) % 2 == inversions(b) % 2) {
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        if (a == b) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    } else {
        cout << "NO\n";
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

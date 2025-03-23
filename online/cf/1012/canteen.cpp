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

struct segtree {
    int n;
    vector<ll> st;

    segtree(int n) : n(n), st(2 * n) {}
    segtree(int n, vector<ll> &nums) : segtree(n) { 
        copy(nums.begin(), nums.end(), st.begin() + n);
        for (int i = n - 1; i > 0; i--) {
            st[i] = max(st[i << 1], st[i << 1 | 1]);
        }
    }

    ll qry(int l, int r) const {
        ll ans = -INFLL;
        l += n;
        r += n;
        while (l < r) {
            if (l & 1) {
                ans = max(ans, st[l]);
                l++;
            }

            if (r & 1) {
                r--;
                ans = max(ans, st[r]);
            }

            l >>= 1;
            r >>= 1;
        }
        return ans;
    }
};

void solve() {
    int n;
    ll k;
    cin >> n >> k;

    vector<ll> a(n), b(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    rep(i, 0, n) {
        cin >> b[i];
    }

    if (accumulate(all(a), 0LL) <= k) {
        cout << "0\n";
        return;
    }

    vector<ll> psum = {0};
    rep(i, 0, 2*n) {
        psum.push_back(psum.back() + b[i % n] - a[i % n]);
    }

    segtree st(sz(psum), psum);

    auto check = [&](int gap) {
        ll needed = 0;
        rep(i, 0, n) {
            auto best = st.qry(i+1, i+gap+1);
            needed += max(0LL, psum[i] - best);
        }
        return needed <= k;
    };

    int lo = 1;
    int hi = n;
    int ans = n;
    while (lo <= hi) {
        int m = (lo + hi) / 2;
        if (check(m)) {
            ans = m;
            hi = m - 1;
        } else {
            lo = m + 1;
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

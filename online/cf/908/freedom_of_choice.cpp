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

struct block {
    int n;
    ll l, r;
    ll tot;
    map<ll, ll> cnts;
};

void solve() {
    int m;
    cin >> m;

    vector<block> blocks;
    map<ll, vector<ll>> at;
    ll sum_l = 0, sum_r = 0;
    for (int i = 0; i < m; i++) {
        block b;
        cin >> b.n >> b.l >> b.r;

        vector<ll> a(b.n), c(b.n);
        for (auto &x : a) cin >> x;
        for (auto &x : c) cin >> x;

        b.tot = 0;
        for (int j = 0; j < b.n; j++) {
            b.cnts[a[j]] = c[j];
            at[a[j]].push_back(i);
            b.tot += c[j];
        }

        blocks.push_back(b);

        sum_l += b.l;
        sum_r += b.r;
    }

    // also the smallest that is nowhere
    ll cur = sum_l;
    while (at.find(cur) != at.end()) cur++;
    at[cur] = {};

    ll ans = INFLL;
    for (const auto &[len, locs] : at) {
        if (len < sum_l || len > sum_r) continue;

        auto extra_free = sum_r - sum_l;
        ll required = 0;

        for (auto i : locs) {
            auto &b = blocks[i];

            auto c = b.cnts[len];
            auto remain = b.tot - c;

            extra_free -= b.r - b.l;

            if (remain < b.l) {
                required += b.l - remain;
            } else if (remain <= b.r) {
                extra_free += remain - b.l;
            } else {
                extra_free += b.r - b.l;
            }
        }

        auto base = sum_l;
        if (base + extra_free < len) {
            required += len - (base + extra_free);
        }

        ans = min(ans, required); 
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

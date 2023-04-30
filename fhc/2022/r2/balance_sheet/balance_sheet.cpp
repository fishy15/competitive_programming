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

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : mi((int)(_v % MOD)) {}
    mi operator+(const mi &m2) const { return mi(v + m2.v); }
    mi operator-(const mi &m2) const { return mi(v - m2.v); }
    mi operator*(const mi &m2) const { return mi((ll) v * m2.v); }
    mi operator/(const mi &m2) const { return mi((ll) v * m2.inv().v); }
    mi &operator+=(const mi &m2) { return *this = *this + m2; }
    mi &operator-=(const mi &m2) { return *this = *this - m2; }
    mi &operator*=(const mi &m2) { return *this = *this * m2; }
    mi &operator/=(const mi &m2) { return *this = *this / m2; }
    mi pow(ll e) const {
        mi res = 1;
        mi n = *this;
        while (e > 0) {
            if (e & 1) res *= n;
            n *= n;
            e >>= 1;
        }
        return res;
    }
    mi inv() const {
        return pow(MOD - 2);
    }
};

void solve() {
    int n, k;
    cin >> n >> k;

    map<int, vector<array<ll, 3>>> nums;
    vector<vector<ll>> best(n);

    for (int i = 0; i < n; i++) {
        int a, b, x, y;
        cin >> a >> b >> x >> y;
        nums[a].push_back({x, 1, i}); // 1 means put this later after sorting
        nums[b].push_back({y, 0, i});
    }

    for (auto &[_, v] : nums) {
        sort(v.begin(), v.end());

        multiset<ll> cur_best, to_add;
        int pc = -1;
        for (auto [c, t, idx] : v) {
            if (pc != c) {
                if (cur_best.size() < to_add.size()) swap(cur_best, to_add);

                for (ll x : to_add) {
                    cur_best.insert(x);
                }
                
                to_add.clear();
            }

            // if this is endpoint
            if (t == 0) {
                cur_best.insert(-c);
                for (ll b : best[idx]) {
                    to_add.insert(b - c);
                }
            } else {
                auto it = cur_best.rbegin();
                for (int i = 0; i < k && it != cur_best.rend(); i++, it++) {
                    best[idx].push_back(*it + c);
                }
            }

            pc = c;
        }
    }

    vector<ll> total_best;

    for (int i = 0; i < n; i++) {
        for (ll b : best[i]) {
            total_best.push_back(b);
        }
    }

    sort(total_best.rbegin(), total_best.rend());

    mi ans;
    for (int i = 0; i < min(k, (int) total_best.size()); i++) {
        ans += total_best[i];
    }

    cout << ans.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

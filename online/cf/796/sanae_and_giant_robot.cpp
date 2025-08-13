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
    int n, m;
    cin >> n >> m;

    vector<ll> a(n), b(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    rep(i, 0, n) {
        cin >> b[i];
    }

    vector<pair<int, int>> ints(m);
    vector<vector<int>> at_idx(n+1);
    rep(i, 0, m) {
        auto &[l, r] = ints[i];
        cin >> l >> r;
        l--;
        at_idx[l].push_back(i);
        at_idx[r].push_back(i);
    }

    vector<ll> psum = {0};
    psum.reserve(n + 1);
    rep(i, 0, n) {
        psum.push_back(psum.back() + (b[i] - a[i]));
    }

    set<int> not_zero;
    rep(i, 0, n+1) {
        not_zero.insert(i); 
    }

    vector<int> cnt(m);
    queue<int> q;
    auto set_zero = [&](int x) {
        for (auto int_idx : at_idx[x]) {
            cnt[int_idx]++;
            if (cnt[int_idx] == 2) {
                q.push(int_idx);
            }
        }
    };

    auto set_interval = [&](int l, int r) {
        auto start_it = not_zero.lower_bound(l);
        auto end_it = not_zero.lower_bound(r);
        for (auto it = start_it; it != end_it; it++) {
            set_zero(*it);
        }
        not_zero.erase(start_it, end_it);
    };

    rep(i, 0, n+1) {
        if (psum[i] == 0) {
            set_zero(i);
            not_zero.erase(i);
        }
    }

    while (!q.empty()) {
        auto idx = q.front();
        q.pop();

        auto [l, r] = ints[idx];
        set_interval(l, r);
    }

    if (not_zero.empty()) {
        cout << "YES\n";
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

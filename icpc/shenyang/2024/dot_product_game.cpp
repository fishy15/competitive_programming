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

struct BIT {
    int n;
    vector<int> bit;
    BIT(int _n) : n(_n), bit(_n + 1) {}

    void upd(int x, int q) {
        x++;
        while (x <= n) {
            bit[x] += q;
            x += x & -x;
        }
    }

    int qry(int r) {
        int res = 0;
        while (r > 0) {
            res += bit[r];
            r -= r & -r;
        }
        return res;
    }

    int qry(int l, int r) {
        return qry(r) - qry(l);
    }
};

ll count_inversions(vector<pair<int, int>> perms) {
    int n = sz(perms);
    sort(all(perms));

    BIT bit(n);
    ll ans = 0;
    for (auto [_, x] : perms) {
        ans += bit.qry(x, n);
        bit.upd(x, 1);
    }

    return ans;
}

void solve() {
    int n;
    cin >> n;

    vector<pair<int, int>> nums(n);
    rep(i, 0, n) {
        cin >> nums[i].first;
        nums[i].first--;
    }
    rep(i, 0, n) {
        cin >> nums[i].second;
        nums[i].second--;
    }

    auto num_inversions = count_inversions(nums);
    cout << (num_inversions % 2 == 0 ? 'B' : 'A');
    rep(i, 0, n-1) {
        char t;
        int l, r, d;
        cin >> t >> l >> r >> d;
        l--;
        r--;

        num_inversions += d * (r - l);
        cout << (num_inversions % 2 == 0 ? 'B' : 'A');
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

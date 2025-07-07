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

    vector<ll> a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }

    auto tot = accumulate(all(a), 0LL);
    if (tot % 2 == 1 || count_if(all(a), [tot](auto x) { return x > tot / 2; })) {
        cout << "-1\n";
        return;
    }

    ll cur_sum = 0;
    int mid = 0;
    while (cur_sum < tot / 2) {
        cur_sum += a[mid];
        mid++;
    }
    mid--;

    if (cur_sum == tot / 2) {
        cout << 1 << '\n';
        for (auto x : a) {
            cout << x << ' ';
        }
        cout << '\n';
        return;
    }

    auto left_sum = cur_sum - a[mid];
    auto right_sum = tot - cur_sum;
    auto middle = a[mid];

    ll left_give = 0;
    vector<ll> op1(n);
    vector<ll> op2(n);

    if (left_sum < right_sum) {
        // give diff more on the right side than the left side
        auto diff = right_sum - left_sum;
        auto right_give = (middle - diff) / 2 + diff;
        left_give = middle - right_give;
    } else {
        // give diff more on the right side than the left side
        auto diff = left_sum - right_sum;
        left_give = (middle - diff) / 2 + diff;
    }

    // give to left side on the first iteration
    rep(i, 0, mid) {
        auto to_give = min(a[i], left_give);
        op1[i] += to_give;
        op1[mid] += to_give;
        a[i] -= to_give;
        a[mid] -= to_give;
        left_give -= to_give;
    }

    // everything else on second iteration
    op2 = a;

    cout << "2\n";
    for (auto x : op1) {
        cout << x << ' ';
    }
    cout << '\n';
    for (auto x : op2) {
        cout << x << ' ';
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

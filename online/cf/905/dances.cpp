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
    int n, m;
    cin >> n >> m;

    vector<int> a(n - 1), b(n);
    for (auto &x : a) {
        cin >> x;
    }
    for (auto &x : b) {
        cin >> x;
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    // how much we have to delete for this to be okay
    // whether it be by removing it or shifting to the right
    // init assumes we start at index i+1
    // later assumes we start at index i
    vector<int> need_init(n - 1), need_later(n - 1);
    for (int i = 0; i < n - 1; i++) {
        int first_better = upper_bound(b.begin(), b.end(), a[i]) - b.begin();
        need_init[i] = max(0, first_better - (i + 1));
        need_later[i] = max(0, first_better - i);
    }

    // need_init_mx[i] = max of the last i elements
    // need_later_mx[i] = max of the first i elements
    vector<int> need_init_mx(n), need_later_mx(n);
    for (int i = 0; i < n - 1; i++) {
        need_init_mx[i + 1] = max(need_init_mx[i], need_init[n - i - 2]);
        need_later_mx[i + 1] = max(need_later_mx[i], need_later[i]);
    }

    vector<int> total;
    total.reserve(2 * n - 1);
    total.insert(total.end(), a.begin(), a.end());
    total.insert(total.end(), b.begin(), b.end());

    sort(total.begin(), total.end());
    total.erase(unique(total.begin(), total.end()), total.end());

    // assumes it goes to the same location once sorted and beats the same things
    auto process_range = [&](int l, int r) {
        r = min(r, m);
        if (l > r || l > m) return 0LL;
        
        // where we would insert
        int idx = upper_bound(a.begin(), a.end(), l) - a.begin();
        int init_needed = need_init_mx[(n - 1) - idx];
        int later_needed = need_later_mx[idx];

        // for me
        int first_better = upper_bound(b.begin(), b.end(), l) - b.begin();
        int cur_needed = max(0, first_better - idx);
        return (ll) (r - l + 1) * max({init_needed, later_needed, cur_needed});
    };

    ll ans = 0;

    // process first range
    ans += process_range(1, total[0] - 1);

    for (auto it = total.begin(); it != total.end(); it++) {
        auto x = *it;
        int nxt = next(it) == total.end() ? INF : *next(it);

        ans += process_range(x, x);
        ans += process_range(x + 1, nxt - 1);
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

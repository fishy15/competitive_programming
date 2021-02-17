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
    int n, m; cin >> n >> m;
    vector<int> a(n), x(m);
    vector<ll> ans(m);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> x[i];
    }

    ll sum = 0;
    ll max_p = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        max_p = max(max_p, sum);
    }

    set<pair<int, int>> to_ans;
    for (int i = 0; i < m; i++) {
        if (x[i] > max_p && sum <= 0) {
            ans[i] = -1;
        } else {
            if (sum > 0) ans[i] += max(0LL, (x[i] - max_p + sum - 1) / sum);
            to_ans.insert({x[i] - sum * ans[i], i});
            ans[i] *= n;
        }
    }

    ll cur_p = 0;
    for (int i = 0; i < n; i++) {
        cur_p += a[i];
        while (!to_ans.empty() && to_ans.begin()->first <= cur_p) {
            ans[to_ans.begin()->second] += i;
            to_ans.erase(to_ans.begin());
        }
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

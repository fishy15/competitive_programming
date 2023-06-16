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

ll need(ll amt, ll x, ll res) {
    if (amt > res) {
        if (amt % x < res) {
            return 0;
        } else {
            return x - (amt % x - res);
        }
    }
    return 0;
}

void solve() {
    int n; cin >> n;
    vector<ll> nums(n + 1);
    vector<pair<ll, int>> pos;
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        sum += nums[i];
        if (i != 1) pos.push_back({nums[i], i});
    }
    
    if (sum % n != 0) {
        cout << "-1\n";
        return;
    }
    ll tot = sum / n;
    
    sort(pos.begin(), pos.end(), [tot](const pair<ll, int> &p1, const pair<ll, int> &p2) {
        ll n1 = need(p1.first, p1.second, tot);
        ll n2 = need(p2.first, p2.second, tot);
        if (n1 == n2) return p1.first > p2.first;
        return n1 < n2;
    });

    vector<array<ll, 3>> ans;
    for (auto p : pos) {
        if (nums[p.second] > tot) {
            ll rem = nums[p.second] / p.second;
            if (rem) ans.push_back({p.second, 1, rem});
            nums[1] += p.second * rem;
            nums[p.second] -= p.second * rem;
        }
    }

    sort(pos.begin(), pos.end(), [&](const pair<ll, int> &p1, const pair<ll, int> &p2) {
        ll n1 = need(nums[p1.second], p1.second, tot);
        ll n2 = need(nums[p2.second], p2.second, tot);
        if (n1 == n2) return p1.first > p2.first;
        return n1 > n2;
    });

    for (auto p : pos) {
        if (nums[p.second] > tot) {
            ll n1 = need(nums[p.second], p.second, tot);
            ans.push_back({1, p.second, n1});
            ans.push_back({p.second, 1, 1});
        } else if (nums[p.second] < tot) {
            ans.push_back({1, p.second, tot - nums[p.second]});
        }
    }

    cout << ans.size() << '\n';
    for (auto [a, b, c] : ans) {
        cout << a << ' ' << b << ' ' << c << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

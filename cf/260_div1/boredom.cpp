#include <iostream>
#include <vector>
#include <map>
#include <utility>

#define ll long long
using namespace std;

ll max(ll a, ll b) {
    return a > b ? a : b;
}

int main() {
    ll n; cin >> n;
    map<ll, ll> m;

    for (ll i = 0; i < n; i++) {
        ll x; cin >> x;
        if (m.count(x) == 0) {
            m[x] = 1;
        } else {
            m[x]++;
        }
    }

    vector<pair<ll, ll>> nums;
    for (auto p : m) {
        nums.push_back(p);
    }

    ll sz = (ll)(nums.size());
    vector<vector<ll>> ans(sz, vector<ll>(2, 0));
    ans[0][0] = 0;
    ans[0][1] = nums[0].first * nums[0].second;

    for (ll i = 1; i < sz; i++) {
        if (nums[i].first - nums[i - 1].first == 1) {
            ans[i][0] = max(ans[i - 1][0], ans[i - 1][1]);
            ans[i][1] = ans[i - 1][0] + nums[i].first * nums[i].second;
        } else {
            ans[i][0] = max(ans[i - 1][0], ans[i - 1][1]);
            ans[i][1] = ans[i][0] + nums[i].first * nums[i].second;
        }
    }

    cout << max(ans[sz - 1][0], ans[sz - 1][1]) << '\n';
    return 0;
}
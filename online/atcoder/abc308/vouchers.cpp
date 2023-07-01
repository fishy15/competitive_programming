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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<ll> price(n);
    for (auto &p : price) {
        cin >> p;
    }

    ll total_cost = accumulate(price.begin(), price.end(), 0LL);

    sort(price.begin(), price.end());
    // remove the last few if extra
    if (m < n) {
        price.erase(price.begin(), price.begin() + (n - m));
    }

    vector<pair<ll, ll>> coupon(m);
    for (auto &c : coupon) {
        cin >> c.first;
    }

    for (auto &c : coupon) {
        cin >> c.second;
    }

    // {L, 0, D}
    // {p, 1, _}
    vector<array<ll, 3>> events;
    for (auto p : price) {
        events.push_back({p, 1, 0});
    }

    for (auto [l, d] : coupon) {
        events.push_back({l, 0, d});
    }

    sort(events.begin(), events.end());
    
    multiset<ll> ds;
    ll save = 0;
    for (auto &qq : events) {
        if (qq[1] == 0) {
            ds.insert(qq[2]);
        } else {
            if (!ds.empty()) {
                auto it = prev(ds.end());
                save += *it;
                ds.erase(it);
            }
        }
    }

    cout << total_cost - save << '\n';

    return 0;
}

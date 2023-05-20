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

constexpr int ps[] = {
    2, 3, 5, 7, 11,
    13, 17, 19, 23,
    29, 31, 37, 41,
    43, 47, 53, 59,
    61, 67, 71, 73,
    79, 83, 89, 97
};

constexpr int num_ps = end(ps) - begin(ps);

void add_p(vector<ll> &list, int p, ll limit) {
    int cur_sz = list.size();

    for (int i = 0; i < cur_sz; i++) {
        ll cur_pow = p;
        ll x = list[i];
        while (cur_pow <= limit / x) {
            list.push_back(cur_pow * x);
            cur_pow *= p;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    int p;
    cin >> n >> p;

    vector<ll> all1 = {1}, all2 = {1};
    for (int i = 0; i < num_ps && ps[i] <= p; i++) {
        if (all1.size() <= all2.size()) {
            add_p(all1, ps[i], n);
        } else {
            add_p(all2, ps[i], n);
        }
    }

    if (all1.size() < all2.size()) swap(all1, all2);
    sort(all2.begin(), all2.end());

    ll ans = 0;
    for (auto x : all1) {
        auto last_mul = n / x;
        ans += upper_bound(all2.begin(), all2.end(), last_mul) - all2.begin();
    }

    cout << ans << '\n';

    return 0;
}

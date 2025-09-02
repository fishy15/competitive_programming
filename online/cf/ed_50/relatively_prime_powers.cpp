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

ll isqrt(ll x) {
    ll res = sqrt(x);
    while (res * res < x) {
        res++;
    }
    while (res * res > x) {
        res--;
    }
    return res;
}

constexpr __int128_t LIMIT = 1'000'000'000'000'000'000;
vector<__int128_t> big_powers;

void precomp() {
    // precomputed
    big_powers.reserve(1003479);

    __int128_t cur_sqrt = 1;
    rep(i, 2, 1'000'000 + 1) {
        if ((cur_sqrt + 1) * (cur_sqrt + 1) == i) {
            cur_sqrt++;
        } else {
            int exp = 1;
            __int128_t cur = i;
            while (cur <= LIMIT) {
                if (exp != 1 && exp % 2 == 1) {
                    big_powers.push_back(cur);
                }
                exp++;
                cur *= i;
            }
        }
    }

    sort(all(big_powers));
    big_powers.erase(unique(all(big_powers)), end(big_powers));
}

void solve() {
    ll x;
    cin >> x;

    auto sqs = isqrt(x) - 1;
    auto bound = upper_bound(all(big_powers), x);
    auto to_remove = sqs + (int) (bound - begin(big_powers));
    auto ans = (x - 1) - to_remove;
    cout << (ll) ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

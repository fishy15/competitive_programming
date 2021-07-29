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
#include <chrono>
#include <random>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

int n;
ll nums[MAXN];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll randval() {
    return uniform_int_distribution(0, n - 1)(rng);
}

ll calc(ll i) {
    ll cur = 0;
    for (int j = 0; j < n; j++) {
        if (nums[j] < i) {
            cur += i - nums[j] % i;
        } else {
            cur += min(nums[j] % i, i - nums[j] % i);
        }
    }
    return cur;
}

ll check(ll x) {
    ll res = INFLL;
    for (ll i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) {
            while (x % i == 0) x /= i;
            res = min(res, calc(i));
        }
    }
    if (x != 1) res = min(res, calc(x));
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    ll ans = INFLL;
    for (int i = 0; i <= 30; i++) {
        ll x = randval();
        x = nums[x];
        if (x - 1 > 1) ans = min(ans, check(x - 1));
        if (x > 1) ans = min(ans, check(x));
        if (x + 1 > 1) ans = min(ans, check(x + 1));
    }

    cout << ans << '\n';

    return 0;
}

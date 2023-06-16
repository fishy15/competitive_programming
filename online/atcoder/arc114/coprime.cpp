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

int n;
ll nums[MAXN];

int p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

ll gcd(ll x, ll y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    ll ans = INFLL;
    ll sz = sizeof(p) / sizeof(p[0]);

    for (int i = 0; i < (1 << sz); i++) {
        ll cur = 1;
        for (int j = 0; j < sz; j++) {
            if ((i >> j) & 1) cur *= p[j];
        }

        bool ok = true;
        for (int j = 0; j < n && ok; j++) {
            if (gcd(nums[j], cur) == 1) ok = false;
        }

        if (ok) {
            ans = min(ans, cur);
        }
    }

    cout << ans << '\n';

    return 0;
}

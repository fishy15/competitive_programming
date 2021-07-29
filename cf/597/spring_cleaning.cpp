/*
 * Same solution as editorial https://codeforces.com/blog/entry/71080.
 */
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

ll prefix(ll x, ll r) {
    ll ans = 0;

    while (r) {
        ll lsb = r & -r;
        r -= lsb;

        if ((x & r) == 0) {
            ll cur = 1;
            ll pow = 1;
            while (pow < lsb) {
                if ((pow & x) == 0) {
                    cur *= 2; 
                }
                pow <<= 1;
            } 
            ans += cur;
        }
    }
    
    return ans;
}

ll solve(ll l, ll r) {
    if (l == r) {
        return 0;
    } else if (l == 0) {
        return 2 * r - 1 + solve(1, r);
    } else if (l % 2 == 1) {
        return solve(l + 1, r) + 2 * (prefix(l, r) - prefix(l, l));
    } else if (r % 2 == 1) {
        return solve(l, r - 1) + 2 * (prefix(r - 1, r) - prefix(r - 1, l));
    } else {
        return 3 * solve(l / 2, r / 2);
    }
}

void solve() {
    ll l, r; cin >> l >> r;
    cout << solve(l, r + 1) << '\n';
}

ll solve2(ll l, ll r) {
    int ans = 0;
    for (int i = l; i < r; i++) {
        for (int j = l; j < r; j++) {
            if ((i & j) == 0) {
                ans++;
            }
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

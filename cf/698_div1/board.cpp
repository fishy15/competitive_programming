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

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void solve() {
    int n; ll k; cin >> n >> k;
    vector<ll> nums(n);
    ll g = -1;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        if (nums[0] != nums[i]) {
            if (g == -1) {
                g = abs(nums[i] - nums[0]);
            } else {
                g = gcd(g, abs(nums[i] - nums[0]));
            }
        }
    }

    if (g == -1) {
        cout << (nums[0] == k ? "YES\n" : "NO\n");
    } else {
        cout << (abs(k - nums[0]) % g == 0 ? "YES\n" : "NO\n");
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

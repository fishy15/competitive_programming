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
    ll n, k; cin >> n >> k;
    vector<ll> nums;

    ll mm = -INFLL;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        nums.push_back(x);
        mm = max(mm, x);
    }

    ll mm2 = -INFLL;
    for (int i = 0; i < n; i++) {
        nums[i] = mm - nums[i];
        mm2 = max(nums[i], mm2);
    }

    for (int i = 0; i < n; i++) {
        if (k & 1) {
            cout << nums[i] << ' ';
        } else {
            cout << mm2 - nums[i] << ' ';
        }
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

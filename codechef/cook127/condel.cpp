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
    int n, k; cin >> n >> k;
    vector<int> nums(n);
    vector<int> psum(n + 1);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        psum[i + 1] = nums[i];
        psum[i + 1] += psum[i];
    }

    ll mm = INF;
    for (int i = 0; i < n - k + 1; i++) {
        mm = min<ll>(mm, psum[i + k] - psum[i]);
    }

    ll ans = psum[n];
    ans -= mm;
    ans += mm * (mm + 1) / 2;
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

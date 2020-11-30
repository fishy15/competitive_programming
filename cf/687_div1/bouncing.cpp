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
    int n, p, k; cin >> n >> p >> k;
    string pattern; cin >> pattern;
    ll x, y; cin >> x >> y;

    vector<int> cnt(k);
    vector<int> to_add(n);

    for (int i = n - 1; i >= 0; i--) {
        if (pattern[i] == '1') cnt[i % k]++;
        to_add[i] = (n - 1 - i) / k + 1 - cnt[i % k];
    }


    int rem = 0;
    ll ans = INFLL;
    for (int i = 0; i < n; i++) {
        if (i + p > n) break;
        ans = min(ans, y * rem + x * to_add[i + p - 1]);
        rem++;
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

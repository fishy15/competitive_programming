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

bool pali(ll x) {
    ll copy_x = x;
    ll flip = 0;

    while (x > 0) {
        flip = 10 * flip + x % 10;
        x /= 10;
    }

    return copy_x == flip;
}

void solve() {
    ll n; cin >> n;
    ll sq = sqrt(n) + 1;

    vector<int> f;
    for (ll i = 1; i <= sq; i++) {
        if (n % i == 0) {
            f.push_back(i);
            f.push_back(n / i);
        }
    }

    sort(f.begin(), f.end());
    f.erase(unique(f.begin(), f.end()), f.end());

    int cnt = 0;
    for (auto x : f) {
        if (pali(x)) {
            cnt++;
        }
    }

    cout << cnt << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

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
#define MAXN 100010

using namespace std;

int n, k;
int t[MAXN];

bool check(ll d) {
    int done = 0;
    for (int i = 0; i < n; i++) {
        if (t[i] <= d) {
            done++;
            d--;
            i++;

            if (done == k) return true;
        }
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    ll l = 0;
    ll r = 2000000000;
    ll ans = -1;

    while (l <= r) {
        ll m = (l + r) / 2;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    cout << ans << '\n';

    return 0;
}

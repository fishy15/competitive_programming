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

int n;
ll w, l;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> l >> w;

    ll r = 0;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll a; cin >> a;

        if (r < a) {
            ans += (a - r + w - 1) / w;
        }

        r = a + w;
    }

    ans += (l - r + w - 1) / w;
    cout << ans << '\n';

    return 0;
}

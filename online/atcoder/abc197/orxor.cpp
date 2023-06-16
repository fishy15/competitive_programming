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
#define MAXN 30

using namespace std;

int n;
ll nums[MAXN];

ll ckmin(ll &a, ll b) {
    return a = min(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    ll res = INFLL;
    for (int i = 0; i < (1 << (n - 1)); i++) {
        int mask = (i << 1) | 1;
        ll ans = 0;
        ll cur = 0;
        for (int j = n - 1; j >= 0; j--) {
            cur |= nums[j];
            if ((mask >> j) & 1) {
                ans ^= cur;
                cur = 0;
            }
        }
        res = min(res, ans);
    }

    cout << res << '\n';

    return 0;
}

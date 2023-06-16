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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    ll n;
    int k;
    cin >> n >> k;

    vector<ll> p(k);
    for (int i = 0; i < k; i++) {
        cin >> p[i];
    }

    ll ans = 0;
    for (int i = 1; i < (1 << k); i++) {
        int sgn = -1;
        ll mul = 1;
        ll cnt = 0;

        for (int j = 0; j < k; j++) {
            if ((i >> j) & 1) {
                sgn *= -1;
                if (n / mul < p[j]) goto done;
                mul *= p[j];
            }
        }

        cnt = n / mul;

done:
        ans += sgn * cnt;
    }

    cout << ans << '\n';

    return 0;
}

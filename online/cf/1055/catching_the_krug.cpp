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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

void solve() {
    ll n, rk, ck, rd, cd;
    cin >> n >> rk >> ck >> rd >> cd;

    auto steps1 = (rk < rd) ? rk : n - rk;
    auto steps2 = (ck < cd) ? ck : n - ck;
    ll gap1 = abs(rk - rd);
    ll gap2 = abs(ck - cd);

    if (gap1 == 0) {
        steps1 = 0;
    }
    if (gap2 == 0) {
        steps2 = 0;
    }

    cout << max(steps1 + gap1, steps2 + gap2) << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

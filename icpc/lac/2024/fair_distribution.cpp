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
#include <bitset>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> g(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> g[i] >> r[i];
    }

    if (n == 1) {
        cout << "N\n";
        return 0;
    }

    ll r_gcd = 0;
    for (auto x : r) {
        r_gcd = gcd(r_gcd, x);
    }


    auto tot = accumulate(g.begin(), g.end(), 0LL);
    bool has_zero = count(g.begin(), g.end(), 0) > 0;

    vector<int> cnt(MAXN);
    for (auto x : g) {
        cnt[x]++;
    }

    vector<int> ng;
    for (int i = 1; i < MAXN; i++) {
        if (cnt[i] > 0) {
            auto extra = (cnt[i] - 1) / 2;
            cnt[2 * i] += extra;
            cnt[i] -= 2 * extra;
        }

        for (int j = 0; j < cnt[i]; j++) {
            ng.push_back(i);
        }
    }

    bitset<MAXN> dp;
    dp[0] = 1;
    for (auto x : ng) {
        dp |= dp << x;
    }

    int low = has_zero ? 0 : 1;
    int high = has_zero ? tot : tot - 1;
    for (int i = low; i <= high; i++) {
        auto rest = tot - i;
        if (dp[i] && (i % r_gcd == rest % r_gcd)) {
            cout << "Y\n";
            return 0;
        }
    }

    cout << "N\n";

    return 0;
}

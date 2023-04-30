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
#define MAXN 10000000

using namespace std;

int pp[MAXN + 1];

void precalc() {
    for (ll i = 2; i <= MAXN; i++) {
        if (pp[i] == 0) {
            pp[i] = i;
            for (ll j = i * i; j <= MAXN; j += i) {
                pp[j] = i;
            }
        }
    }
}

void add_primes(int x, map<int, int> &cnt) {
    while (x > 1) {
        cnt[pp[x]]++;
        x /= pp[x];
    }
}

void solve() {
    int n;
    cin >> n;

    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        add_primes(x, cnt);
    }

    int leftover = 0;
    int ans = 0;
    for (auto [_, c] : cnt) {
        ans += c / 2;
        leftover += (c % 2 == 0) ? 0 : 1;
    }

    ans += leftover / 3;
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}

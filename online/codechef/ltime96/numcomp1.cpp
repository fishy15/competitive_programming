/*
 * Only primes can create a new category. In addition, a prime only forms a new cateogry iff 2p > n. We can
 * use prefix sums on the number of primes to calculate the answers.
 */

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
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 10000010

using namespace std;

int p[MAXN];

void preprocess() {
    for (ll i = 2; i < MAXN; i++) {
        if (!p[i]) {
            for (ll j = i * i; j < MAXN; j += i) {
                p[j] = 1;
            }
        }
        p[i] = 1 - p[i];
    }

    partial_sum(p, p + MAXN, p);
}

void solve() {
    int n; cin >> n;
    if (n == 2 || n == 3) {
        cout << n - 1 << '\n';
    } else {
        cout << p[n] - p[n / 2] + 1 << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    preprocess();

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

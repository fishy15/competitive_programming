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

int pp[MAXN + 1];

void precalc() {
    for (ll i = 2; i <= MAXN; i++) {
        if (pp[i] == 0) {
            pp[i] = i;
            for (ll j = i * i; j <= MAXN; j += i) {
                if (pp[j] == 0) {
                    pp[j] = i;
                }
            }
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    if (n == 1 || m == 1) {
        cout << "YES\n";
    } else if (n % m == 0) {
        cout << "NO\n";
    } else {
        if (m >= pp[n]) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
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

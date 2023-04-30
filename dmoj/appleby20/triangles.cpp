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
#define MAXN 1000000

using namespace std;

ll sq(ll x) {
    return x * x;
}

void solve() {
    ll a[3]; cin >> a[0] >> a[1] >> a[2];
    sort(a, a + 3);
    ll v = sq(a[0]) + sq(a[1]) - sq(a[2]);
    if (v < 0) {
        cout << "O\n";
    } else if (v == 0) {
        cout << "R\n";
    } else {
        cout << "A\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

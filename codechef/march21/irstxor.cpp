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

void solve() {
    int c; cin >> c;
    int p = 0;
    while ((1 << p) <= c) p++;
    ll x = 0;
    ll y = 0;
    for (int i = p - 1; i >= 0; i--) {
        if ((1 << i) & c) {
            x += 1 << i;
            if (x > y) swap(x, y);
        } else {
            x += 1 << i;
            y += 1 << i;
        }
    }
    cout << x * y << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

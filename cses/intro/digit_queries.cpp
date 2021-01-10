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
    ll k; cin >> k;

    int dig = 1;
    ll tot = 9;
    ll cnt = 9;
    ll prev = 0;
    while (tot < k) {
        dig++;
        cnt *= 10;
        prev = tot;
        tot += dig * cnt;
    }
    if (dig > 1) k -= prev + 1;
    ll num = k / dig + (dig == 1 ? 0 : cnt / 9);
    cout << to_string(num)[k % dig] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int q; cin >> q;
    while (q--) solve();

    return 0;
}

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

const int Q = 20;

void solve() {
    int n; cin >> n;
    ll vals[Q];
    ll tot = 0;
    ll pp = (1 << Q) - 1;
    memset(vals, 0, sizeof vals);
    for (int i = 0; i < Q; i++) {
        cout << "1 " << pp - (1 << i) << '\n'; 
        cin >> vals[i];
        tot += vals[i];
    }

    ll invsum = (tot - pp * n) / (Q - 2);
    ll sum = pp * n - invsum; 
    ll ans = 0;
    for (int i = 0; i < Q; i++) {
        ll v = pp * n - vals[i];
        ll res = sum - v;
        res += n * (1 << i);
        res >>= i + 1;
        ans += (1 << i) * (res & 1);
    }
    cout << "2 " << ans << '\n';
    cin >> vals[0];
}

int main() {
    int t; cin >> t;
    while (t--) solve();

    return 0;
}

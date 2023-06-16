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

ll get(ll a, ll b) {
    if (b == 1) return INF;
    int cnt = 0;
    while (a != 0) {
        a /= b;
        cnt++;
    }
    return cnt;
}

void solve() {
    ll a, b; cin >> a >> b;
    ll ans = get(a, b);
    int cnt = 0;
    while (true) {
        ll cur = get(a, b + 1);
        if (cur < ans) {
            ans = cur;
            cnt++;
            b++;
        } else {
            break;
        }
    }
    cout << cnt + get(a, b) << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

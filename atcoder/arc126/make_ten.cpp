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
    ll a, b, c; cin >> a >> b >> c;

    ll ans = 0;
    // 3 3 4
    {
        ll d = min(b / 2, c);
        b -= 2 * d;
        c -= d;
        ans += d;
    }

    // 4 4 2
    {
        ll d = min(c / 2, a);
        c -= 2 * d;
        a -= d;
        ans += d;
    }

    // 3 3 2 2 
    {
        ll d = min(b / 2, a / 2);
        b -= 2 * d;
        a -= 2 * d;
        ans += d;
    }

    // 4 2 2 2
    {
        ll d = min(c, a / 3);
        c -= d;
        a -= 3 * d;
        ans += d;
    }

    // 2 2 2 2 2
    {
        ans += a / 5;
    }
    
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

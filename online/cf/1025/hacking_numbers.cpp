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
#include <cassert>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

#ifdef LOCAL
ll x, n, moves;
#endif

bool add(ll y) {
    assert(-1e18 <= y && y <= 1e18);
    cout << "add " << y << endl;
#ifdef LOCAL
    moves++;
    if (x + y < 1 || x + y > 1e18) {
        return false;
    }
    x += y;
    return true;
#else
    int res;
    cin >> res;
    return res == 1;
#endif
}

bool mul(ll y) {
    assert(1 <= y && y <= 1e18);
    cout << "mul " << y << endl;
#ifdef LOCAL
    moves++;
    if (y > 1e18 / x || x * y > 1e18) {
        return false;
    }
    x *= y;
    return true;
#else
    int res;
    cin >> res;
    return res == 1;
#endif
}

bool div(ll y) {
    assert(1 <= y && y <= 1e18);
    cout << "div " << y << endl;
#ifdef LOCAL
    moves++;
    if (x % y != 0) {
        return false;
    }
    x /= y;
    return true;
#else
    int res;
    cin >> res;
    return res == 1;
#endif
}

void digit() {
    cout << "digit" << endl;
#ifdef LOCAL
    moves++;
    ll sum = 0;
    while (x > 0) {
        sum += x % 10;
        x /= 10;
    }
    x = sum;
#else
    int res;
    cin >> res;
#endif
}

void answer() {
    cout << "!" << endl;
#ifdef LOCAL
    cout << x << ' ' << n << ' ' << moves << '\n';
    if (x == n && moves <= 4) {
        cout << "passed\n";
    } else {
        cout << "failed\n";
    }
#else
    int res;
    cin >> res;
    if (res == -1) {
        exit(0);
    }
#endif
}

void solve(ll n) {
    mul(9);
    digit(); 
    digit();
    add(n - 9);
    answer();
}


int main() {
    cin.tie(0)->sync_with_stdio(0);

#ifdef LOCAL
    cin >> x >> n;
    solve(n);
#else
    int t;
    cin >> t;

    while (t--) {
        ll n;
        cin >> n;
        solve(n);
    }
#endif

    return 0;
}

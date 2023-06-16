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

int get_pow(int p, int x) {
    int cur = 0;
    while (x % p == 0) {
        x /= p;
        cur++;
    }

    return cur;
}

int div_out(int x) {
    while (x % 2 == 0) x /= 2;
    while (x % 3 == 0) x /= 3;
    return x;
}

void solve() {
    int n, m;
    cin >> n >> m;

    int n2 = get_pow(2, n);
    int n3 = get_pow(3, n);
    int m2 = get_pow(2, m);
    int m3 = get_pow(3, m);

    int d2 = m2 - n2;
    int d3 = n3 - m3;

    if (d3 >= 0 && d2 >= 0 && d2 <= d3 && div_out(n) == div_out(m)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

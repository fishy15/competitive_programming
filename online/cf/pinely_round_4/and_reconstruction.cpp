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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> b(n - 1);
    rep(i, 0, n-1) {
        cin >> b[i];
    }

    vector<int> a(n);
    rep(i, 0, n-1) {
        a[i] |= b[i];
        a[i + 1] |= b[i];
    }

    // check that it works
    bool works = true;
    rep(i, 0, n-1) {
        if (b[i] != (a[i] & a[i + 1])) {
            works = false;
            break;
        }
    }

    if (!works) {
        cout << "-1\n";
    } else {
        for (auto x : a) {
            cout << x << ' ';
        }
        cout << '\n';
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

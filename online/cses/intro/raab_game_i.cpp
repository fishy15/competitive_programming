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
    int n, a, b;
    cin >> n >> a >> b;

    vector<int> p1(n), p2(n);
    iota(all(p1), 1);
    iota(all(p2), 1);
    if (a != 0 || b != 0) {
        int left = n - a - b;
        if (left < 0 || a == 0 || b == 0) {
            cout << "NO\n";
            return;
        }

        rotate(begin(p1), begin(p1) + b, begin(p1) + a + b);
    }

    cout << "YES\n";
    for (auto x : p1) {
        cout << x << ' ';
    }
    cout << '\n';
    for (auto x : p2) {
        cout << x << ' ';
    }
    cout << '\n';
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

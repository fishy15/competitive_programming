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
    int n; cin >> n;
    vector<pair<int, int>> pts;
    vector<int> x, y;

    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        pts.push_back({a, b});
        x.push_back(a);
        y.push_back(b);
    }

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    if (n % 2 == 1) {
        cout << "1\n";
    } else {
        ll l_x = x[n / 2 - 1];
        ll r_x = x[n / 2];
        ll l_y = y[n / 2 - 1];
        ll r_y = y[n / 2];
        cout << (r_x - l_x + 1) * (r_y - l_y + 1) << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

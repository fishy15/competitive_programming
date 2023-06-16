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

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    auto loc = [](const vector<int> &v, int x) { return find(v.begin(), v.end(), x) - v.begin(); };

    int diff = (loc(b, 1) + n - loc(a, 1)) % n;
    for (int i = 0; i < n; i++) {
        if (b[(i + diff) % n] != a[i]) {
            cout << "NO\n";
            return;
        }
    }

    if (k == 0) {
        cout << (diff == 0 ? "YES\n" : "NO\n");
    } else if (k == 1) {
        cout << (diff != 0 ? "YES\n" : "NO\n");
    } else if (n == 2) {
        cout << (k % 2 == diff % 2 ? "YES\n" : "NO\n");
    } else {
        cout << "YES\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

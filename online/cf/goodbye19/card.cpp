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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n, k1, k2; cin >> n >> k1 >> k2;
    int m = 0, m1 = 0, m2 = 0;
    for (int i = 0; i < k1; i++) {
        int x; cin >> x;
        m = max(m, x);
        m1 = max(m1, x);
    }

    for (int i = 0; i < k2; i++) {
        int x; cin >> x;
        m = max(m, x);
        m2 = max(m2, x);
    }

    if (m1 == m) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

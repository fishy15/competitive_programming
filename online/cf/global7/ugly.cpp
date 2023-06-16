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
    int n; cin >> n;
    ll s1 = 2 * (n - 1) + 3;
    ll s2 = 2 * (n - 2) + 3;
    ll s3 = 2 * (n - 3) + 3;

    if (n == 1) {
        cout << -1 << '\n'; 
    } else if (s1 % 3 != 0) {
        for (int i = 0; i < n - 1; i++) {
            cout << 2;
        }
        cout << 3 << '\n';
    } else if (s2 % 3 != 0) {
        for (int i = 0; i < n - 2; i++) {
            cout << 2;
        }
        cout << 33 << '\n';
    } else if (s3 % 3 != 0) {
        for (int i = 0; i < n - 3; i++) {
            cout << 2;
        }
        cout << 333 << '\n';
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

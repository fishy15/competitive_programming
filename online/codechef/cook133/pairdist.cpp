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
    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (n == 1) {
        cout << "YES\n";
        cout << "0 0\n";
    } else if (n == 2) {
        cout << "YES\n";
        cout << "0 0\n";
        cout << "0 " << a[0] + a[1] << '\n';
    } else if (n == 3) {
        cout << "YES\n";
        cout << "0 " << a[0] << '\n';
        cout << "0 " << -a[1] << '\n';
        cout << a[2] << " 0\n";
    } else if (n == 4) {
        cout << "YES\n";
        cout << "0 " << a[0] << '\n';
        cout << "0 " << -a[1] << '\n';
        cout << a[2] << " 0\n";
        cout << -a[3] << " 0\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

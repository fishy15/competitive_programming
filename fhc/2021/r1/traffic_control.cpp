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
    int n, m, a, b;
    cin >> n >> m >> a >> b;

    if (min(a, b) < n + m - 1) {
        cout << "Impossible\n";
    } else {
        cout << "Possible\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0) {
                    cout << 1 << ' ';
                } else if (j == 0) {
                    if (i == n - 1) {
                        cout << b - (n + m - 2) << ' ';
                    } else {
                        cout << 1 << ' ';
                    }
                } else if (j == m - 1) {
                    if (i == n - 1) {
                        cout << a - (n + m - 2) << ' ';
                    } else {
                        cout << 1 << ' ';
                    }
                } else {
                    cout << 1000 << ' ';
                }
            }
            cout << '\n';
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

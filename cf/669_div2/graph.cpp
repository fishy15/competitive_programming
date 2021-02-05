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
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    vector<array<int, 2>> in(n, {-1, -1});

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                in[i][grid[i][j] - 'a'] = j;
            }
        }
    }

    if (m % 2 == 1) {
        cout << "YES\n";
        for (int i = 0; i <= m; i++) {
            if (i % 2 == 0) {
                cout << 1 << ' ';
            } else {
                cout << 2 << ' ';
            }
        }
        cout << '\n';
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && grid[i][j] == 'a' && grid[j][i] == 'a') {
                cout << "YES\n";
                for (int k = 0; k <= m; k++) {
                    if (k % 2 == 0) {
                        cout << i + 1 << ' ';
                    } else {
                        cout << j + 1 << ' ';
                    }
                }
                cout << '\n';
                return;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (in[i][0] != -1 && in[i][1] != -1) {
            int mid = i + 1;
            int a = in[i][1] + 1;
            int b = in[i][0] + 1;

            cout << "YES\n";
            if (m % 4 == 0) {
                cout << mid << ' ';
                for (int i = 0; i < m / 2; i++) {
                    if (i % 2 == 0) {
                        cout << a << ' ';
                    } else {
                        cout << mid << ' ';
                    }
                }
                for (int i = 0; i < m / 2; i++) {
                    if (i % 2 == 0) {
                        cout << b << ' ';
                    } else {
                        cout << mid << ' ';
                    }
                }
                cout << '\n';
            } else {
                for (int i = 0; i < m / 2; i++) {
                    if (i % 2 == 0) {
                        cout << b << ' ';
                    } else {
                        cout << mid << ' ';
                    }
                }
                cout << mid << ' ';
                for (int i = 0; i < m / 2; i++) {
                    if (i % 2 == 0) {
                        cout << a << ' ';
                    } else {
                        cout << mid << ' ';
                    }
                }
                cout << '\n';
            }
            return;
        }
    }

    cout << "NO\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

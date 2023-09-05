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
    int n, m;
    cin >> n >> m;

    if (n > m) {
        cout << "No\n";
        return;
    }

    if (n % 2 == 0) {
        if (m % 2 == 0) {
            cout << "Yes\n";
            for (int i = 0; i < n - 2; i++) {
                cout << "1 ";
            }
            int left = m - (n - 2);
            cout << left / 2 << ' ' << left / 2 << '\n';
        } else {
            cout << "No\n";
        }
    } else {
        cout << "Yes\n";
        for (int i = 0; i < n - 1; i++) {
            cout << "1 ";
        }
        cout << m - (n - 1) << '\n';
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

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

    vector<string> a(n);
    vector<string> b(n);
    
    for (auto &row : a) {
        cin >> row;
    }

    for (auto &row : b) {
        cin >> row;
    }

    vector diff(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            diff[i][j] = ((a[i][j] - '0') - (b[i][j] - '0') + 3) % 3;
        }
    }

    for (int i = 0; i < n; i++) {
        if (accumulate(diff[i].begin(), diff[i].end(), 0) % 3 != 0) {
            cout << "NO\n";
            return;
        }
    }

    for (int j = 0; j < m; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += diff[i][j];
        }

        if (sum % 3 != 0) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
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

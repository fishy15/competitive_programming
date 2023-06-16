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

    vector grid(n, vector(m, 0));
    vector zero_col(m, vector<int>());
    vector one_col(m, vector<int>());
    vector cur(n, 0);

    int tot = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == 0) {
                zero_col[j].push_back(i);
            } else {
                tot++;
                cur[i]++;
                one_col[j].push_back(i);
            }
        }
    }

    if (tot % n != 0) {
        cout << "-1\n";
        return;
    }

    int want = tot / n;
    vector<array<int, 3>> ops;

    for (int j = 0; j < m; j++) {
        auto &zero = zero_col[j];
        auto &one = one_col[j];

        while (true) {
            while (!zero.empty() && cur[zero.back()] >= want) zero.pop_back();
            while (!one.empty() && cur[one.back()] <= want) one.pop_back();

            if (!zero.empty() && !one.empty()) {
                int low = zero.back();
                int high = one.back();
                zero.pop_back();
                one.pop_back();

                ops.push_back({low, high, j});
                cur[low]++;
                cur[high]--;
            } else {
                break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (cur[i] != want) {
            cout << "-1\n";
            return;
        }
    }

    cout << ops.size() << '\n';
    for (auto [x, y, z] : ops) {
        cout << x + 1 << ' ' << y + 1 << ' ' << z + 1 << '\n';
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

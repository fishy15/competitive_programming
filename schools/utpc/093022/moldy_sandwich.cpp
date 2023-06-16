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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<string> grid(n);
    vector<vector<int>> psum(n + 1, vector<int>(n + 1));
    vector<pair<int, int>> mold;

    for (int i = 0; i < n; i++) {
        cin >> grid[i];

        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '#') {
                mold.push_back({i, j});
                psum[i + 1][j + 1]++;
            }

            psum[i + 1][j + 1] += psum[i][j + 1];
            psum[i + 1][j + 1] += psum[i + 1][j];
            psum[i + 1][j + 1] -= psum[i][j];
        }
    }

    auto get = [&](int x, int y, int d) {
        if (x + d > n || y + d > n) return -1;
        return psum[x + d][y + d] - psum[x][y + d] - psum[x + d][y] + psum[x][y];
    };

    auto check = [&](int d, int need) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (get(i, j, d) >= need) return true;
            }
        }

        return false;
    };

    int prev = 1;
    for (int i = 1; i <= (int) mold.size(); i++) {
        int l = prev;
        int r = n;
        int ans = 1;

        while (l <= r) {
            int m = (l + r) / 2;
            if (check(m, i)) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }

        cout << ans << ' ';
    }
    cout << '\n';

    return 0;
}

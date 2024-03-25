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

    int n, q;
    cin >> n >> q;

    vector grid(n, vector<int>(n));
    for (auto &row : grid) {
        for (auto &x : row) {
            cin >> x;
        }
    }

    vector psum(n + 1, vector<int>(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            psum[i + 1][j + 1] = grid[i][j];
            psum[i + 1][j + 1] += psum[i + 1][j];
            psum[i + 1][j + 1] += psum[i][j + 1];
            psum[i + 1][j + 1] -= psum[i][j];
        }
    }

    while (q--) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        x1--;
        y1--;
        cout << psum[y2][x2] - psum[y1][x2] - psum[y2][x1] + psum[y1][x1] << '\n';
    }

    return 0;
}

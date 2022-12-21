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

/* 
 * 1 2 4
 * 5 3 8
 * 9 6 7
 *
 * 9 5 1
 * 6 3 2
 * 7 8 4
 */

constexpr array<array<int, 3>, 3> THREE_ANS = {array{9, 5, 1}, {6, 3, 2}, {7, 8, 4}};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    if (n <= 2) {
        cout << "-1\n";
        return 0;
    }

    vector grid(n, vector(n, 0));

    bool start_down = n % 2 == 1;

    int cur = 1;
    for (int i = 0; i < n - 3; i++) {
        if (start_down) {
            for (int y = n - 1; y > i; y--) {
                grid[i][y] = cur;
                cur++;
            }

            for (int x = i; x < n; x++) {
                grid[x][i] = cur;
                cur++;
            }
        } else {
            for (int x = n - 1; x > i; x--) {
                grid[x][i] = cur;
                cur++;
            }

            for (int y = i; y < n; y++) {
                grid[i][y] = cur;
                cur++;
            }
        }

        start_down = !start_down;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            grid[n - 3 + i][n - 3 + j] = THREE_ANS[i][j] + cur - 1;
        }
    }

    for (auto &v : grid) {
        for (auto &x : v) {
            cout << x << ' ';
        }
        cout << '\n';
    }

    return 0;
}

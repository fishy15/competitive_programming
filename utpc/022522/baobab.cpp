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

int h, w;
int t;
int v[30];

char grid[15][15];

bool can_place(int x, int y, int s) {
    if (x + s > h || y + s > w) return false;
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            if (grid[x + i][y + j]) return false;
        }
    }

    return true;
}

void place(int x, int y, int s, char c) {
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            grid[x + i][y + j] = c;
        }
    }
}

void solve(int x) {
    if (x == t) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cout << (grid[i][j] ? grid[i][j] : '.') << ' ';
            }
            cout << '\n';
        }
        exit(0);
    } else {
        for (int i = 0; i < h; i++) {
            int col = 0;
            while (col < w) {
                if (can_place(i, col, v[x])) {
                    place(i, col, v[x], 'A' + x);
                    solve(x + 1);
                    place(i, col, v[x], 0);
                }
                col++;
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> h >> w;
    cin >> t;

    int sum = 0;
    for (int i = 0; i < t; i++) {
        cin >> v[i];
        sum += v[i] * v[i];
    }

    if (sum > h * w) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    sort(v, v + t);

    solve(0);

    cout << "IMPOSSIBLE\n";

    return 0;
}

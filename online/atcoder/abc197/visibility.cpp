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
#define MAXN 110

using namespace std;

int h, w;
string grid[MAXN];
int x, y;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> h >> w >> x >> y;
    x--; y--;

    for (int i = 0; i < h; i++) {
        cin >> grid[i];
    }

    int cnt = 0;

    for (int i = x; i < h; i++) {
        if (grid[i][y] == '.') {
            cnt++;
        } else {
            break;
        }
    }

    for (int i = x; i >= 0; i--) {
        if (grid[i][y] == '.') {
            cnt++;
        } else {
            break;
        }
    }

    for (int j = y; j < w; j++) {
        if (grid[x][j] == '.') {
            cnt++;
        } else {
            break;
        }
    }

    for (int j = y; j >= 0; j--) {
        if (grid[x][j] == '.') {
            cnt++;
        } else {
            break;
        }
    }

    cnt -= 3;
    cout << cnt << '\n';

    return 0;
}

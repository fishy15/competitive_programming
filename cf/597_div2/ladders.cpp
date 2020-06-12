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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int l[10][10];
long double ans[10][10];

pair<int, int> nxt(const pair<int, int> &cur) {
    auto [i, j] = cur;
    if (i % 2 == 0) {
        if (j == 0) {
            return {i - 1, j};
        }
        return {i, j - 1};
    }
    if (j == 9) {
        return {i - 1, j};
    }
    return {i, j + 1};
}

pair<int, int> prv(const pair<int, int> &cur) {
    auto [i, j] = cur;
    if (i % 2 == 0) {
        if (j == 9) {
            return {i + 1, j};
        }
        return {i, j + 1};
    }
    if (j == 0) {
        return {i + 1, j};
    }
    return {i, j - 1};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> l[i][j];
        }
    }

    ans[0][0] = 0;
    for (int i = 1; i <= 5; i++) {
        ans[0][i] = 6;
    }

    pair<int, int> cur = {0, 5};
    while (cur != make_pair(9, 0)) {
        cur = prv(cur);
        auto loc = nxt(cur);
        for (int i = 0; i < 6; i++, loc = nxt(loc)) {
            auto [x, y] = loc;
            long double mm = min(ans[x][y], ans[x - l[x][y]][y]);
            ans[cur.first][cur.second] += mm / 6;
        }
        ans[cur.first][cur.second]++;
    }

    cout << fixed << setprecision(12) << ans[9][0] << '\n';

    return 0;
}

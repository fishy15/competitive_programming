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
#define MAXN 200010

using namespace std;

int n;
array<int, 3> range[MAXN];
bool ans[MAXN][2];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> range[i][0] >> range[i][1];
        range[i][2] = i;
    }

    sort(range, range + n, [](const auto &a, const auto &b) {
        if (a[0] == b[0]) {
            return a[1] > b[1];
        }
        return a[0] < b[0];
    });

    int cur_min = INF;
    for (int i = n - 1; i >= 0; i--) {
        auto &cur = range[i];
        ans[cur[2]][0] |= cur_min <= cur[1];
        cur_min = min(cur_min, cur[1]);
    }

    int cur_max = 0;

    for (int i = 0; i < n; i++) {
        auto &cur = range[i];
        ans[cur[2]][1] += cur_max >= cur[1];
        cur_max = max(cur_max, cur[1]);
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i][0] << ' ';
    }
    cout << '\n';

    for (int i = 0; i < n; i++) {
        cout << ans[i][1] << ' ';
    }
    cout << '\n';

    return 0;
}

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
#define MAXN 1010

using namespace std;

int n, p;
array<int, 3> loc[MAXN];
int save[MAXN][5];

template<typename T>
T &ckmax(T &a, T b) {
    return a = max(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> p;
    cin >> loc[0][0] >> loc[0][1];

    for (int i = 1; i <= p; i++) {
        cin >> loc[i][2] >> loc[i][0] >> loc[i][1];
    }

    sort(loc, loc + p + 1, [](auto a, auto b) {
        if (a[2] == b[2]) return a < b;
        return a[2] < b[2];
    });

    memset(save, -1, sizeof save);
    save[0][0] = 0;

    for (int i = 1; i <= p; i++) {
        for (int j = 0; j < i; j++) {
            for (int a = 0; a < 5; a++) {
                int reach = (loc[j][2] + a) + abs(loc[i][0] - loc[j][0]) + abs(loc[i][1] - loc[j][1]);
                int t = loc[i][2];
                int idx = max(reach - t, 0);
                if (idx < 5 && save[j][a] != -1) {
                    ckmax(save[i][idx], save[j][a] + 1);
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= p; i++) {
        for (int j = 0; j < 5; j++) {
            ckmax(ans, save[i][j]);
        }
    }

    cout << ans << '\n';

    return 0;
}

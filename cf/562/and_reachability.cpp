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
#define MAXN 300010

using namespace std;

constexpr int lg = 19;

int n, q;
int nums[MAXN];
int nxt[MAXN][lg];
int has[lg];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        fill(nxt[i], nxt[i] + lg, n);
    }

    fill(nxt[n], nxt[n] + lg, n);
    fill(has, has + lg, n);

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < lg; j++) {
            if ((nums[i] >> j) & 1) {
                for (int k = 0; k < lg; k++) {
                    nxt[i][k] = min(nxt[i][k], nxt[has[j]][k]);
                }
            }
        }

        for (int j = 0; j < lg; j++) {
            if ((nums[i] >> j) & 1) {
                nxt[i][j] = i;
                has[j] = i;
            }
        }
    }

    while (q--) {
        int a, b; cin >> a >> b;
        a--; b--;

        bool ok = false;
        for (int j = 0; j < lg && !ok; j++) {
            if (((nums[b] >> j) & 1) && nxt[a][j] <= b) {
                ok = true;
            }
        }

        cout << (ok ? "Shi" : "Fou") << '\n';
    }

    return 0;
}

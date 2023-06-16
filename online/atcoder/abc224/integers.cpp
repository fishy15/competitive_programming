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

int n, h, w;
map<int, vector<array<int, 3>>> pts;
map<int, int> row;
map<int, int> col;
map<int, int> rcnt;
map<int, int> ccnt;
int ans[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> h >> w >> n;
    for (int i = 0; i < n; i++) {
        int r, c, a; cin >> r >> c >> a;
        pts[a].push_back({r, c, i});
        rcnt[r]++;
        ccnt[c]++;
    }

    for (auto it = pts.rbegin(); it != pts.rend(); it++) {
        auto &[a, v] = *it;
        vector<array<int, 4>> upd;

        for (auto [r, c, idx] : v) {
            int pre = max(row[r], col[c]);
            upd.push_back({r, c, pre + 1, idx});
        }

        for (auto [r, c, x, idx] : upd) {
            row[r] = max(row[r], x);
            col[c] = max(col[c], x);
            ans[idx] = x - 1;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}

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

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void solve() {
    int n, k; cin >> n >> k;
    int mid = (n + 1) / 2;

    vector<vector<int>> val(n, vector<int>(n, 0));
    int x = 0;
    int y = 0;
    int dir = 0;

    auto ok = [&](int a, int b) {
        return a >= 0 && b >= 0 && a < n && b < n && val[a][b] == 0;
    };

    int num = 1;
    vector<array<int, 2>> loc;
    while (x != mid - 1 || y != mid - 1) {
        val[x][y] = num;
        loc.push_back({x + 1, y + 1});

        if (!ok(x + dx[dir], y + dy[dir])) {
            dir++;
            dir %= 4;
        }

        x += dx[dir];
        y += dy[dir];
        num++;
    }

    val[mid - 1][mid - 1] = n * n;

    vector<int> path;
    for (int i = 0; i < n * n - 1; i++) {
        auto [a, b] = loc[i];
        int d = i + abs(a - mid) + abs(b - mid);
        path.push_back({val[a - 1][b - 1]});
        
        if (d == k) {
            while (a != mid || b != mid) {
                int nxt_a = a < mid ? a + 1 : a - 1;
                int nxt_b = b < mid ? b + 1 : b - 1;

                if (a != mid && path.back() < val[nxt_a - 1][b - 1]) {
                    a = nxt_a;
                } else {
                    b = nxt_b;
                }

                path.push_back({val[a - 1][b - 1]});
            }

            int skip = 0;

            int p = 0;
            vector<array<int, 2>> ans;
            for (int x : path) {
                if (x != p + 1) {
                    skip++;
                    ans.push_back({p, x});
                }

                p = x;
            }

            cout << skip << '\n';
            for (auto [a, b] : ans) {
                cout << a << ' ' << b << '\n';
            }
            return;
        }
    }

    cout << "IMPOSSIBLE\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

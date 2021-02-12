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
#define MAXN 1000000

using namespace std;

int x, y;
string grid[101];
int d[101][101][50];
bool vis[101][101][50];
string num;

int dx[2] = {0, 1};
int dy[2] = {1, 0};

bool ok(int a, int b, int c) {
    return a >= 0 && b >= 0 && a < x && b < y && !vis[a][b][c];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> y >> x;
    cin >> num;
    for (int i = x - 1; i >= 0; i--) {
        cin >> grid[i];
    }

    memset(d, 0x3f, sizeof d);
    d[0][0][0] = grid[0][0] - '0';
    priority_queue<array<int, 4>, vector<array<int, 4>>, greater<array<int, 4>>> pq;
    pq.push({d[0][0][0], 0, 0, 0});

    while (!pq.empty()) {
        auto [dd, a, b, c] = pq.top();
        pq.pop();

        if (vis[a][b][c]) continue;
        vis[a][b][c] = true;

        // no diff
        for (int i = 0; i < 2; i++) {
            int na = a + dx[i];
            int nb = b + dy[i];
            if (!ok(na, nb, c)) continue;
            int ndd = dd + grid[na][nb] - '0';
            if (d[na][nb][c] > ndd) {
                d[na][nb][c] = ndd;
                pq.push({ndd, na, nb, c});
            }
        }

        // skip
        if (c < (int)(num.size())) {
            for (int i = 0; i < 2; i++) {
                int v = num[c] - '0' + 1;
                int na = a + dx[i] * v;
                int nb = b + dy[i] * v;
                if (!ok(na, nb, c + 1)) continue;
                int ndd = dd + grid[na][nb] - '0';
                if (d[na][nb][c + 1] > ndd) {
                    d[na][nb][c + 1] = ndd;
                    pq.push({ndd, na, nb, c + 1});
                }
            }
        }
    }

    for (int i = x - 1; i >= 0; i--) {
        for (int j = 0; j < y; j++) {
            cout << d[i][j][0] << ' ';
        }
        cout << '\n';
    }
    cout << "---\n";
    for (int i = x - 1; i >= 0; i--) {
        for (int j = 0; j < y; j++) {
            cout << d[i][j][1] << ' ';
        }
        cout << '\n';
    }
    cout << "---\n";
    for (int i = x - 1; i >= 0; i--) {
        for (int j = 0; j < y; j++) {
            cout << d[i][j][2] << ' ';
        }
        cout << '\n';
    }
    cout << "---\n";
    for (int i = x - 1; i >= 0; i--) {
        for (int j = 0; j < y; j++) {
            cout << d[i][j][3] << ' ';
        }
        cout << '\n';
    }
    cout << "---\n";

    int ans = INF;
    for (int i = 0; i <= (int)(num.size()); i++) {
        /* cout << d[x - 1][y - 1][i] << '\n'; */
        ans = min(ans, d[x - 1][y - 1][i]);
    }

    cout << ans << '\n';

    return 0;
}

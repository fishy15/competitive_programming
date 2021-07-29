/*
 * Let dp[i][j] be the max sum you can get if you have used the rows i, i + 1, ... n - 1 and the current 
 * interval starts at j (current interval meaning the 2 x k rectangle, upper-left corner is (i, j)).
 * To calculate the value of dp[i][j], we want to subtract any values that could be repeated from the 
 * previous row and then find the maximum. There are a range of dp values that contain repeated values, 
 * so we can answer these queries with lazy segment trees (range addition update, range max query). The
 * answer is the max value in the 0th row.
 */

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
#define MAXN 60
#define MAXM 20010

using namespace std;

int n, m, k;
int grid[MAXN][MAXM];
int dp[MAXN][MAXM];

struct lazy_segtree {
    int st[4 * MAXM];
    int lazy[4 * MAXM];
    void push(int v, int l, int r) {
        if (l != r) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        st[v] += lazy[v];
        lazy[v] = 0;
    }
    void upd(int x, int y, int q, int v = 1, int l = 0, int r = m - 1) {
        push(v, l, r);
        if (r < x || l > y) return;
        if (x <= l && r <= y) {
            lazy[v] += q;
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(x, y, q, 2 * v, l, m);
            upd(x, y, q, 2 * v + 1, m + 1, r);
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }
    int qry(int x, int y, int v = 1, int l = 0, int r = m - 1) {
        push(v, l, r);
        if (r < x || l > y) return 0;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return max(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m + 1, r));
    }
} st[MAXN];


int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    for (int i = 0; i < k; i++) {
        dp[n - 1][0] += grid[n - 1][i];
    }

    for (int i = 1; i <= m - k; i++) {
        dp[n - 1][i] = dp[n - 1][i - 1] - grid[n - 1][i - 1] + grid[n - 1][i + k - 1];
    }

    for (int i = n - 2; i >= 0; i--) {
        vector<array<int, 3>> cur;
        for (int j = 0; j < m; j++) {
            cur.push_back({grid[i + 1][j], max(0, j - k + 1), j});
            /* auto &elem = cur.back(); */
            /* st[i].upd(elem[1], elem[2], elem[0]); */
        }

        for (int j = 0; j <= m - k; j++) {
            st[i].upd(j, j, dp[i + 1][j]);
        }

        int window = 0;
        for (int j = 0; j < k; j++) {
            st[i].upd(cur[j][1], cur[j][2], -cur[j][0]);
            window += grid[i][j];
            window += grid[i + 1][j];
        }

        dp[i][0] = window + st[i].qry(0, m - 1);

        for (int j = 1; j <= m - k; j++) {
            st[i].upd(cur[j - 1][1], cur[j - 1][2], cur[j - 1][0]);
            st[i].upd(cur[j + k - 1][1], cur[j + k - 1][2], -cur[j + k - 1][0]);
            window += -grid[i][j - 1] - grid[i + 1][j - 1] 
                + grid[i][j + k - 1] + grid[i + 1][j + k - 1];
            dp[i][j] = window + st[i].qry(0, m - 1);
        }
    }

    cout << *max_element(dp[0], dp[0] + m) << '\n';

    return 0;
}

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
#define MAXN 100010

using namespace std;

int n;
int nums[MAXN];
int ans;

struct person {
    int lg[MAXN];
    int l[MAXN][18];
    int r[MAXN][18];

    void lcalc() {
        lg[1] = 0;
        for (int i = 2; i < MAXN; i++) {
            lg[i] = lg[i / 2] + 1;
        }
    }

    void calc(int x[MAXN][18]) {
        for (int j = 1; j < 18; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                x[i][j] = max(x[i][j - 1], x[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int qry(int x[MAXN][18], int a, int b) {
        a = max(a, 0);
        b = min(b, n - 1);
        if (b < a) return 0;
        int log = lg[b - a + 1];
        return max(x[a][log], x[b - (1 << log) + 1][log]);
    }
} p1, p2;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    memset(p1.l, 0, sizeof p1.l);
    memset(p1.r, 0, sizeof p1.r);
    memset(p2.l, 0, sizeof p2.l);
    memset(p2.r, 0, sizeof p2.r);

    // solve for rightward movement
    for (int i = 1; i < n; i++) {
        if (nums[i - 1] < nums[i]) {
            p1.r[i][0] = p1.r[i - 1][0] + 1;
        } else {
            p2.r[i][0] = p2.r[i - 1][0] + 2;
        }
    }

    // solve for leftward movement
    for (int i = n - 2; i >= 0; i--) {
        if (nums[i] > nums[i + 1]) {
            p1.l[i][0] = p1.l[i + 1][0] + 1;
        } else {
            p2.l[i][0] = p2.l[i + 1][0] + 2;
        }
    }

    p2.lcalc();
    p2.calc(p2.l);
    p2.calc(p2.r);

    for (int i = 1; i < n - 1; i++) {
        if (p1.l[i] && p1.r[i]) {
            int can_move = p1.l[i][0];
            if (can_move % 2 == 0) can_move--;
            if (can_move >= p1.r[i][0]) continue;

            can_move = p1.r[i][0];
            if (can_move % 2 == 0) can_move--;
            if (can_move >= p1.l[i][0]) continue;

            int best = 0;
            best = max(best, p2.qry(p2.l, 0, i - p1.r[i][0] - 1));
            best = max(best, p2.qry(p2.l, i + 1, n - 1));
            best = max(best, p2.qry(p2.r, i + p1.l[i][0] + 1, n));
            best = max(best, p2.qry(p2.r, 0, i - 1));

            if (best >= max(p1.l[i][0], p1.r[i][0])) continue;

            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}

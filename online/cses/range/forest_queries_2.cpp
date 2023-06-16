// :pray: :steph:
// :pray: :bakekaga:

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
#define MAXN 1000

using namespace std;

int n, q;
int bit[MAXN + 1][MAXN + 1];
bool trees[MAXN + 1][MAXN + 1];

void update(int x, int y, int v) {
    while (x <= MAXN) {
        int y1 = y;
        while (y1 <= MAXN) {
            bit[x][y1] += v;
            y1 += (y1 & -y1);
        }
        x += (x & -x);
    }
}

int query(int x, int y) {
    int ans = 0;
    while (x > 0) {
        int y1 = y;
        while (y1 > 0) {
            ans += bit[x][y1];
            y1 -= (y1 & -y1);
        }
        x -= (x & -x);
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        for (int j = 1; j <= n; j++) {
            if (s[j - 1] == '*') {
                update(j, i, 1);
                trees[j][i] = true;
            }
        }
    }

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int y, x; cin >> y >> x;
            if (trees[x][y]) {
                update(x, y, -1);
                trees[x][y] = false;
            } else {
                update(x, y, 1);
                trees[x][y] = true;
            }
        } else {
            int y1, x1, y2, x2; cin >> y1 >> x1 >> y2 >> x2;
            cout << query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1) << '\n';
        }
    }

    return 0;
}

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
#include <cstring>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

int n, q;
int up[MAXN][20];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    memset(up, -1, sizeof up);
    for (int i = 1; i < n; i++) {
        int x; cin >> x;
        x--;
        up[i][0] = x;
    }

    for (int i = 1; i < 20; i++) {
        for (int j = 0; j < n; j++) {
            if (up[j][i - 1] != -1) up[j][i] = up[up[j][i - 1]][i - 1];
        }
    }

    while (q--) {
        int x, k; cin >> x >> k;
        x--;
        for (int i = 0; i < 20; i++) {
            if ((1 << i) & k) {
                x = up[x][i];
                if (x == -1) break;
            }
        }
        if (x == -1) cout << "-1\n";
        else cout << x + 1 << '\n';
    }

    return 0;
}

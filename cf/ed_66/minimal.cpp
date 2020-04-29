// seal orz

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
const int MAXN = 5e5 + 10;

using namespace std;

int n, m;
int mm;
vector<int> add[MAXN];
int nxt[MAXN][20];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        add[l].push_back(r);
    }

    for (int i = 1; i < MAXN; i++) {
        for (int j : add[i]) mm = max(mm, j);
        if (mm > i) nxt[i][0] = mm;
    }

    for (int p = 1; p < 20; p++) {
        for (int i = 1; i < MAXN; i++) {
            nxt[i][p] = nxt[nxt[i][p - 1]][p - 1];
        }
    }

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        int cnt = 0;
        for (int p = 19; p >= 0; p--) {
            if (nxt[a][p] < b && nxt[a][p]) {
                a = nxt[a][p];
                cnt += 1 << p;
            }
        }
        if (a != b) {
            cnt++;
            a = nxt[a][0];
        }
        if (a < b) {
            cout << "-1\n";
        } else {
            cout << cnt << '\n';
        }
    }

    return 0;
}

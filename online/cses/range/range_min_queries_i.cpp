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
#define MAXN 200010

using namespace std;

int n, q;
ll st[MAXN][20];
int l[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> st[i][0];
    }

    l[1] = 0;
    for (int i = 2; i <= n; i++) {
        l[i] = l[i / 2] + 1;
    }

    for (int i = 1; i < 20; i++) {
        for (int j = 0; j + (1 << i) <= n; j++) {
            st[j][i] = min(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
        }
    }

    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        int p = l[b - a + 1];
        cout << min(st[a][p], st[b - (1 << p) + 1][p]) << '\n';
    }

    return 0;
}

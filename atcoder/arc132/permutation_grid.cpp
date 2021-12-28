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
#define MAXN 100010

using namespace std;

int n, q;
int r[MAXN];
int inv_r[MAXN];
int inv_c[MAXN];

vector<array<int, 2>> solve_r[MAXN];
char ans[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        r[i] = x;
        inv_r[x] = i;
    }

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        inv_c[x] = i;
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        solve_r[r[a]].push_back({b, i});
    }

    set<int> cur;
    for (int i = 0; i < n; i++) {
        cur.insert(inv_c[n - i - 1]);
        for (auto [c, idx] : solve_r[i]) {
            if (cur.count(c)) {
                ans[idx] = '#';
            } else {
                ans[idx] = '.';
            }
        }
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}

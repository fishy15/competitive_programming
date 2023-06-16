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

int twook[MAXN + 10];
int ans[MAXN + 10];
vector<int> pre[MAXN + 10];

void precalc() {
    for (ll i = 2; i <= MAXN; i++) {
        ans[i] = 1;
        twook[i] = 1;
        for (int x : pre[i]) {
            twook[i] = max(twook[i], twook[i / x - 1] + 1);
            if (x > 2) ans[i] = max(ans[i], twook[i / x - 1] + 1);
        }
        for (ll j = 2; i * j <= MAXN; j++) {
            ll idx = i * j;
            pre[idx].push_back(i);
        }
    }
}

void solve() {
    int n; cin >> n;
    cout << ans[n] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

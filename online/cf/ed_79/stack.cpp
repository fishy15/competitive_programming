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
#include <stack>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> pos(n + 1);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        pos[x] = i;
    }

    int max_done = -1;
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        if (pos[x] < max_done) {
            ans++;
        } else {
            ans += 2 * (pos[x] - i + 1) - 1;
            max_done = pos[x];
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

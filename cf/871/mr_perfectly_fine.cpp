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
#define MAXN 1000000

using namespace std;

void solve() {
    int n;
    cin >> n;

    array<int, 4> best = {INF, INF, INF, INF};
    for (int i = 0; i < n; i++) {
        int t;
        string s;
        cin >> t >> s;

        if (s == "00") {
            best[0] = min(best[0], t);
        } else if (s == "01") {
            best[1] = min(best[1], t);
        } else if (s == "10") {
            best[2] = min(best[2], t);
        } else {
            best[3] = min(best[3], t);
        }
    }

    int ans = min({INF, best[1] + best[2], best[3]});
    if (ans == INF) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

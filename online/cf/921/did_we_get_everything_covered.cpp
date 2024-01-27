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
    int n, k, m;
    cin >> n >> k >> m;

    string s;
    cin >> s;

    int r = 0;
    string res;
    for (int i = 0; i < n; i++) {
        array<int, 26> first_loc{};
        first_loc.fill(m);

        for (int j = r; j < m; j++) {
            auto c = s[j] - 'a';
            if (first_loc[c] == m) {
                first_loc[c] = j;
            }
        }

        pair<int, int> latest = {-1, -1};
        for (int c = 0; c < k; c++) {
            latest = max(latest, {first_loc[c], c});
        }

        res += (char) ('a' + latest.second);
        r = latest.first + 1;
    }

    if (r == m + 1) {
        cout << "NO\n";
        cout << res << '\n';
    } else {
        cout << "YES\n";
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

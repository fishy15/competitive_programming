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
    int n, m; cin >> n >> m;
    vector<int> x, y;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == 'B') {
                x.push_back(i + j);
                y.push_back(i - j);
            }
        }
    }

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    auto get_d = [](const vector<int> &s, int x) {
        int upper = abs(s.back() - x);
        int lower = abs(x - s[0]);
        return max(upper, lower);
    };

    array<int, 3> ans = {INF, 0, 0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int d = max(get_d(x, i + j), get_d(y, i - j));
            ans = min(ans, {d, i + 1, j + 1});
        }
    }

    cout << ans[1] << ' ' << ans[2] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

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

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> days(m);
    vector<int> ans(m);
    map<int, int> cnt;

    for (int i = 0; i < m; i++) {
        int sz; cin >> sz;
        for (int j = 0; j < sz; j++) {
            int x; cin >> x;
            days[i].push_back(x);
        }
        ans[i] = days[i][0];
        cnt[days[i][0]]++;
    }

    int to_fix = -1;
    for (auto [val, cnt] : cnt) {
        if (cnt > (m + 1) / 2) {
            to_fix = val;
        }
    }

    int left = 0;
    if (to_fix != -1) {
        left = cnt[to_fix] - (m + 1) / 2;;
        for (int i = 0; i < m && left > 0; i++) {
            if (days[i][0] == to_fix && days[i].size() > 1) {
                ans[i] = days[i][1];
                left--;
            }
        }
    }

    if (left > 0) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    for (int i = 0; i < m; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

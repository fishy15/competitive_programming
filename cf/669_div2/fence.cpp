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
    vector<int> a(n), b(n), c(m);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    for (int i = 0; i < m; i++) {
        cin >> c[i];
    }

    vector<vector<int>> need(n + 1);
    vector<int> has_loc(n + 1, -1);
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            need[b[i]].push_back(i);
        } else {
            has_loc[a[i]] = i;
        }
    }

    vector<int> ans(m);
    vector<int> q;
    for (int i = 0; i < m; i++) {
        if (need[c[i]].empty()) {
            if (has_loc[c[i]] != -1) {
                for (int x : q) {
                    ans[x] = has_loc[c[i]];
                }
                q = {};
                ans[i] = has_loc[c[i]];
            } else {
                q.push_back(i);
            }
        } else {
            int y = need[c[i]].back();
            for (int x : q) {
                ans[x] = y;
            }
            q = {};
            ans[i] = y;
            need[c[i]].pop_back();
            has_loc[c[i]] = y;
        }
    }

    if (!q.empty()) {
        cout << "NO\n";
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (!need[i].empty()) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
    for (int i : ans) {
        cout << i + 1 << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

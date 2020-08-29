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
    vector<int> st;
    vector<vector<int>> r(n);
    vector<int> bestpos(n, INF);
    vector<int> bestm(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        st.push_back(x);
    }

    for (int i = 0; i < n; i++) {
        int maxp = 0;
        for (int j = 0; j < m; j++) {
            int d; cin >> d;
            st[i] += d;
            r[i].push_back(st[i]);
            if (st[i] > r[i][maxp]) {
                maxp = j;
            }
        }
        r[i].push_back(maxp);
    }

    for (int i = 0; i < m; i++) {
        vector<pair<int, int>> v;
        vector<int> pos(n);
        for (int j = 0; j < n; j++) {
            v.push_back({r[j][i], j});
        }
        sort(v.begin(), v.end(), greater<pair<int, int>>());
        for (int j = 0; j < n; j++) {
            if (j > 0 && v[j - 1].first == v[j].first) {
                pos[v[j].second] = pos[v[j - 1].second];
            } else {
                pos[v[j].second] = j;
            }

            int q = v[j].second;
            /* cout << i << ' ' << q << ' ' << pos[q] << ' ' << bestpos[q] << '\n'; */
            if (pos[q] < bestpos[q]) {
                bestpos[q] = pos[q];
                bestm[q] = i;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += r[i][m] != bestm[i];
        /* cout << r[i][m] << ' ' << bestm[i] << '\n'; */
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

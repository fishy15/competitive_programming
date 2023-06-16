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
#define MAXN 1000000

using namespace std;

void solve() {
    int n; cin >> n;
    vector<vector<int>> m(n);
    int t = 0;
    vector<set<int>> r(n);
    vector<set<int>> c(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x; cin >> x;
            m[i].push_back(x);
            if (i == j) t += x;
            r[i].insert(x);
            c[j].insert(x);
        }
    }

    int rr = 0;
    for (int i = 0; i < n; i++) {
        if (r[i].size() < n) rr++;
    }

    int cc = 0;
    for (int i = 0; i < n; i++) {
        if (c[i].size() < n) cc++;
    }

    cout << t << ' ' << rr << ' ' << cc << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

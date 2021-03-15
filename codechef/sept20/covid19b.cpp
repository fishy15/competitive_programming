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
    int n; cin >> n;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        v.push_back(x);
    }

    int maxans = 0;
    int minans = INF;
    for (int i = 0; i < n; i++) {
        double t = 0;
        vector<bool> vis(n);
        vis[i] = true;
        int cnt = 1;
        for (int j = 0; j < n - 1; j++) {
            double mint = INF;
            int pos = -1;
            for (int k = 0; k < n; k++) {
                if (vis[k]) continue;
                for (int a = 0; a < n; a++) {
                    if (!vis[a]) continue;
                    if (v[k] == v[a]) continue;
                    double tt = 1.0 * (k - a) / (v[a] - v[k]);
                    if (tt >= t && tt < mint) {
                        mint = tt;
                        pos = k;
                    }
                }
            }
            if (pos == -1) break;
            cnt++;
            vis[pos] = true;
            t = mint;
        }
        maxans = max(maxans, cnt);
        minans = min(minans, cnt);
    }

    cout << minans << ' ' << maxans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

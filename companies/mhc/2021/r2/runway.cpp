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
    multiset<int> no_change;
    multiset<int> change;
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        no_change.insert(x);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        vector<int> p(m);
        vector<int> done(m, false);
        for (int j = 0; j < m; j++) {
            cin >> p[j];
        }

        multiset<int> nxt_no_change;
        multiset<int> nxt_change;
        // move what we can w/o change
        for (int j = 0; j < m; j++) {
            int c = p[j];
            if (change.find(c) != change.end()) {
                done[j] = true;
                nxt_change.insert(c);
                change.erase(change.find(c)); // erase only 1 copy
            } else if (no_change.find(c) != no_change.end()) {
                done[j] = true;
                nxt_no_change.insert(c);
                no_change.erase(no_change.find(c)); // erase only 1 copy
            }
        }

        // change without cost
        for (int j = 0; j < m; j++) {
            if (!done[j] && !no_change.empty()) {
                done[j] = true;
                no_change.erase(no_change.begin());
                nxt_change.insert(p[j]);
            }
        }

        // change with cost
        for (int j = 0; j < m; j++) {
            if (!done[j]) {
                ans++;
                nxt_change.insert(p[j]);
            }
        }

        swap(no_change, nxt_no_change);
        swap(change, nxt_change);
    }

    cout << ans << '\n';
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

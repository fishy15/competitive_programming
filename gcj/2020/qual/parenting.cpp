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
    set<int> cur;
    vector<pair<int, int>> proc;
    vector<char> ans(n);
    for (int i = 1; i <= n; i++) {
        int a, b; cin >> a >> b;
        proc.push_back({a, i});
        proc.push_back({b, -i});
    }
    sort(proc.begin(), proc.end());
    bool used[] = {false, false};
    for (auto p : proc) {
        if (p.second > 0) {
            if (!used[0]) {
                ans[p.second - 1] = 'J';
                used[0] = true;
            } else if (!used[1]) {
                ans[p.second - 1] = 'C';
                used[1] = true;
            } else {
                cout << "IMPOSSIBLE\n";
                return;
            }
        } else {
            int pos = -p.second - 1;
            if (ans[pos] == 'J') {
                used[0] = false;
            } else {
                used[1] = false;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        cout << ans[i];
    } cout << '\n';
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

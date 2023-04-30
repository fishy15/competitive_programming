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
    int n, k; cin >> n >> k;
    vector<map<int, int>> path;
    path.emplace_back();
    path.back()[k] = -1;

    for (int i = 1; i <= n; i *= 2) {
        map<int, int> nxt;
        for (auto it = path.back().rbegin(); it != path.back().rend(); it++) {
            int c = it->first;
            if (c & i) {
                if (c - i >= 0) {
                    nxt[c - i] = c;
                }

                if (c + i <= n) {
                    nxt[c + i] = c;
                }
            }
        }
        path.push_back(nxt);
    }

    for (int i = 0; i < (int) path.size(); i++) {
        if (path[i].count(0)) {
            int cur_idx = i;
            int cur_val = 0;
            vector<int> vals;
            while (cur_idx >= 0) {
                vals.push_back(cur_val); 
                cur_val = path[cur_idx][cur_val];
                cur_idx--;
            }

            reverse(vals.begin(), vals.end());
            int sz = vals.size();

            cout << "YES\n";
            cout << sz - 1 << '\n';

            int r = k;
            for (int j = 0; j < sz - 1; j++) {
                if (vals[j + 1] > vals[j]) {
                    cout << r + 1 << '\n';
                    r += (1 << j);
                } else {
                    r -= (1 << j);
                    cout << r + 1 << '\n';
                }
            }

            return;
        }
    }

    cout << "NO\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

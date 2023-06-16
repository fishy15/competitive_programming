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
    int n, k, x;
    cin >> n >> k >> x;

    vector<bool> present(n + 1, true);
    present[0] = false;

    vector<vector<int>> ans;

    for (int i = 1; i <= n; i++) {
        if ((int) ans.size() + 1 == k) {
            break;
        }

        if (present[i]) {
            if (i == x) {
                ans.push_back({i});
                present[i] = false;
            } else if ((i ^ x) <= n && present[i ^ x]) {
                ans.push_back({i, i ^ x});
                present[i] = false;
                present[i ^ x] = false;
            }
        }
    }

    int last_xor = 0;
    ans.push_back({});

    // add remaining to the last group
    for (int i = 1; i <= n; i++) {
        if (present[i]) {
            last_xor ^= i;
            ans.back().push_back(i);
        }
    }

    if ((int) ans.size() < k || ans.back().empty() || last_xor != x) {
        cout << "NO\n"; 
    } else {
        cout << "YES\n";
        for (auto &v : ans) {
            cout << v.size();
            for (auto x : v) {
                cout << ' ' << x;
            }
            cout << '\n';
        }
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

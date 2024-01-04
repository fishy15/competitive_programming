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

int get_bit(int m, int i) {
    return (m >> i) & 1;
}

array<vector<int>, 20> valid_masks;

void precomp() {
    for (int n = 1; n < 20; n++) {
        for (int mask = 1; mask < (1 << n); mask++) {
            int m2 = mask << 1;
            vector<int> ans;
            vector<bool> set(n + 1);
            for (int i = 1; i <= n; i++) {
                if (get_bit(m2, i)) {
                    ans.push_back(i);
                    for (int j = i; j <= n; j += i) {
                        set[j] = !set[j];
                    }
                }
            }

            int cnt = count(set.begin(), set.end(), true);
            if (cnt <= n / 5) {
                valid_masks[n].push_back(m2);
            }
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }

    if (n >= 20) {
        // we can just toggle everything
        cout << n << '\n';
        for (int i = 1; i <= n; i++) {
            cout << i << ' ';
        }
        cout << '\n';
        return;
    } else {
        // try every possibility
        for (auto m2 : valid_masks[n]) {
            bool valid = true;
            for (auto [u, v] : edges) {
                if (get_bit(m2, u) && !get_bit(m2, v)) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                vector<int> ans;
                for (int i = 1; i <= n; i++) {
                    if (get_bit(m2, i)) {
                        ans.push_back(i);
                    }
                }

                cout << ans.size() << '\n';
                for (auto x : ans) {
                    cout << x << ' ';
                }
                cout << '\n';
                return;
            }
        }
    }

    cout << "-1\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

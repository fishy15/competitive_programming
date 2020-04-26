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

int n, k;
vector<vector<int>> m;
vector<int> c;
vector<vector<int>> ans;
vector<int> sz;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    m.resize(k + 1);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        m[x].push_back(i);
    }

    ans.resize(n);
    sz.resize(n);
    int cur = 0;
    ll extra = 0;
    for (int i = 0; i < k; i++) {
        int x; cin >> x;
        c.push_back(x);
    }
    c.push_back(0);

    for (int i = k; i >= 1; i--) {
        extra += (c[i - 1] - c[i]) * cur;
        if (extra < m[i].size()) {
            int need = m[i].size() - extra;
            int pp = ceil(1.0 * need / c[i - 1]);
            cur += pp;
            extra += pp * c[i - 1];
        }
        auto it = lower_bound(sz.begin() + (n - cur), sz.end(), c[i - 1]) - 1;
        auto it2 = m[i].begin();
        for (;;it--) {
            int j = it - sz.begin();
            while (it2 != m[i].end() && sz[j] < c[i - 1]) {
                ans[j].push_back(i);
                extra--;
                sz[j]++;
                it2++;
            }
            if (it2 == m[i].end()) break;
        }
    }

    cout << cur << '\n';
    for (int i = n - cur; i < n; i++) {
        cout << sz[i] << ' ';
        for (int j : ans[i]) cout << j << ' ';
        cout << '\n';
    }

    return 0;
}

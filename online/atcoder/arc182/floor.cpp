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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    int init = 1 << (k - 1);

    vector<int> res = {init};
    queue<pair<int, int>> q;
    if (k > 1) {
        q.push({init, k - 2});
    }

    while (!q.empty() && sz(res) < n) {
        auto [num, idx] = q.front();
        q.pop();

        auto flipped = num ^ (1 << idx);
        res.push_back(flipped);

        if (idx > 0) {
            q.push({num, idx - 1});
            q.push({flipped, idx - 1});
        }
    }

    while (sz(res) < n) {
        res.push_back(1);
    }

    for (auto x : res) {
        cout << x << ' ';
    }
    cout << '\n';
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

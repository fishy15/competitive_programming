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

    map<int, int> cnt;
    rep(i, 0, n) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    vector<int> grps;
    for (auto [_, v] : cnt) {
        grps.push_back(v);
    }
    sort(all(grps));

    int cur_size = 0;
    int inserted = 0;
    for (auto x : grps) {
        if (cur_size + x <= k) {
            cur_size += x;
            inserted++;
        }
    }

    if (inserted == sz(grps)) {
        cout << "1\n";
    } else {
        cout << sz(grps) - inserted << '\n';
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

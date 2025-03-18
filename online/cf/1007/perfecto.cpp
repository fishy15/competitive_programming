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

bool is_square(ll x) {
    auto sq = (ll) sqrt(x);
    while (sq * sq < x) sq++;
    while (sq * sq > x) sq--;
    return sq * sq == x;
}

void solve() {
    int n;
    cin >> n;

    if (is_square((ll) n * (n + 1) / 2)) {
        cout << "-1\n";
        return;
    }

    ll cur_sum = 0;
    int cur = 1;
    vector<int> ans;
    while (cur <= n) {
        if (is_square(cur_sum + cur)) {
            ans.push_back(cur + 1);
            ans.push_back(cur);
            cur_sum += cur + (cur + 1);
            cur += 2;
        } else {
            ans.push_back(cur);
            cur_sum += cur;
            cur += 1;
        }
    }

    for (auto x : ans) {
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

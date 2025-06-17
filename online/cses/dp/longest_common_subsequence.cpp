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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(m);
    rep(i, 0, n) {
        cin >> a[i];
    }
    rep(i, 0, m) {
        cin >> b[i];
    }

    vector dp(n+1, vector(m+1, tuple{0, -1, -1, false}));
    rep(i, 0, n) {
        rep(j, 0, m) {
            auto skip1 = tuple{get<0>(dp[i+1][j]), i+1, j, false};
            auto skip2 = tuple{get<0>(dp[i][j+1]), i, j+1, false};
            auto same = 
                a[i] == b[j] ? tuple{get<0>(dp[i][j]) + 1, i, j, true}
                             : tuple{get<0>(dp[i][j]), i, j, false};
            dp[i+1][j+1] = max({skip1, skip2, same});
        }
    }

    vector<int> seq;
    int cur_x = n;
    int cur_y = m;
    while (cur_x != -1 && cur_y != -1) {
        auto [_, new_x, new_y, kept] = dp[cur_x][cur_y];
        if (kept) {
            seq.push_back(a[new_x]);
        }
        tie(cur_x, cur_y) = {new_x, new_y};
    }

    reverse(all(seq));
    cout << sz(seq) << '\n';
    for (auto x : seq) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}

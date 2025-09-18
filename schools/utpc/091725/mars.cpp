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

    int n;
    cin >> n;

    vector<array<int, 3>> ships(n);
    for (auto &[a, b, c] : ships) {
        cin >> a >> b >> c;
    }

    sort(all(ships), [](const auto &a, const auto &b) { return a[1] < b[1]; });

    int earth1 = INF;
    int earth2 = INF;
    int mars1 = -1;
    int mars2 = -1;

    int ans = 0;

    for (auto [l, r, t] : ships) {
        if (t == 0) {
            // going to earth
            if (mars1 <= l) {
                if (earth1 == INF) earth1 = r;
                else earth2 = r;
                mars1 = INF;
            } else if (mars2 <= l) {
                if (earth1 == INF) earth1 = r;
                else earth2 = r;
                mars2 = INF;
            }
        } else {
            if (earth1 <= l) {
                if (mars1 == INF) mars1 = r;
                else mars2 = r;
                earth1 = INF;
                ans++;
            } else if (earth2 <= l) {
                if (mars1 == INF) mars1 = r;
                else mars2 = r;
                earth2 = INF;
                ans++;
            }
        }

        if (earth1 < earth2) swap(earth1, earth2);
        if (mars1 < mars2) swap(mars1, mars2);
    }

    cout << ans << '\n';

    return 0;
}

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

    vector<ll> on_size(n + 1);
    rep(i, 0, n) {
        cin >> on_size[i+1];
    }

    vector<ll> gain(n);
    rep(i, 0, n) {
        cin >> gain[i];
    }

    pair<ll, ll> best{0, 1};
    rep(msk, 1, 1 << n) {
        ll sum = 0;
        rep(i, 0, n) {
            if ((msk >> i) & 1) {
                sum += gain[i];
            }
        }

        auto size = __builtin_popcount(msk);
        sum += on_size[size];

        if (best.first * size < sum * best.second) {
            best = {sum, size};
        }
    }

    ld ans = 1.0 * best.first / best.second;
    cout << fixed << setprecision(15);
    cout << ans << '\n';

    return 0;
}

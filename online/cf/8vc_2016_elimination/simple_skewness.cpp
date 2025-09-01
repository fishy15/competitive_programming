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

struct frac {
    __int128_t num, denom;
    frac(__int128_t x) : num(x), denom(1) {}
    frac(__int128_t x, __int128_t y) : num(x), denom(y) { reduce(); }
    frac operator-(const frac &other) const {
        auto res = frac{num * other.denom - other.num * denom, denom * other.denom};
        res.reduce();
        return res;
    }
    bool operator<(const frac &other) const {
        return num * other.denom < other.num * denom;
    }
    void reduce() {
        auto g = __gcd(num, denom);
        if (g != 0) {
            num /= g;
            denom /= g;
        }
        if (denom < 0) {
            num *= -1;
            denom *= -1;
        }
    }
    void pr() {
        cout << (ll) num << '/' << (ll) denom;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<ll> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    sort(all(nums));

    vector<ll> psum(n+1);
    rep(i, 0, n) {
        psum[i+1] = psum[i] + nums[i];
    }

    auto get_sum = [&](int l, int r) {
        return psum[r] - psum[l];
    };

    frac best_diff = 0;
    pair<int, int> config = {0, 0};
    rep(i, 0, n) {
        int space_left = i;
        int space_right = n - i - 1;

        int r = min(space_left, space_right);
        int ans = 0;
        if (r > 0) {
            int l = 1;
            while (l <= r) {
                int m = (l + r) / 2;
                auto prev_sum = get_sum(i - m + 1, i + 1) + get_sum(n - m + 1, n);
                auto prev_mean = frac{prev_sum, 2 * (m - 1) + 1};
                auto cur_sum = get_sum(i - m , i + 1) + get_sum(n - m, n);
                auto cur_mean = frac{cur_sum, 2 * m + 1};
                if (prev_mean < cur_mean) {
                    ans = m;
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }
        }
        
        auto sum = get_sum(i - ans, i + 1) + get_sum(n - ans, n);
        auto mean = frac{sum, 2 * ans + 1};
        auto median = frac{nums[i]};
        auto diff = mean - median;
        if (best_diff < diff) {
            best_diff = diff;
            config = {i, ans};
        }
    }

    vector<int> idx = {config.first};
    rep(i, 0, config.second) {
        idx.push_back(config.first - i - 1);
        idx.push_back(n - i - 1);
    }

    cout << sz(idx) << '\n';
    for (auto x : idx) {
        cout << nums[x] << ' ';
    }
    cout << '\n';

    return 0;
}

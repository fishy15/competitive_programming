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
#include <chrono>
#include <random>
#include <bit>

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

using u32 = unsigned int;
using u64 = unsigned long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

u64 get_rand(u64 l, u64 r) {
    return uniform_int_distribution(l, r)(rng);
}

__int128_t gcd(__int128_t a, __int128_t b, __int128_t& x, __int128_t& y) {
    x = 1, y = 0;
    __int128_t x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        __int128_t q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

void solve() {
    u64 t;
    cin >> t;
    
    u64 a, b;
    bool found_a = false;
    bool found_b = false;

    constexpr u64 M = 0x9E3779B97F4A7C15ULL;
    constexpr u64 C = 0xD1B54A32D192ED03ULL;

    __int128_t x, y;
    gcd(M, ((__int128_t) 1) << 64, x, y);

    auto inv = (u64) x;

    while (!found_b) {
        auto k = get_rand(0, (1ULL << 32) - 1);
        auto goal = k << 32 | (t ^ k);

        auto rotated = rotr(goal, 23);
        
        // mx = prod
        auto prod = rotated - C;
        if (prod % 2 == 0) {
            continue;
        }

        auto ans = inv * prod;

        // check that it works
        auto check_lin = M * ans + C;
        auto check_rot = rotl(check_lin, 23);
        auto check_t = (u32) (check_rot ^ (check_rot >> 32));
        if (t != check_t) {
            continue;
        }

        if (!found_a) {
            a = ans;
            found_a = true;
        } else {
            b = ans;
            found_b = true;
        }
    }

    cout << a << ' ' << b << '\n';
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

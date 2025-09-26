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

#define ll __int128_t
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

// cp algos
ll egcd(ll a, ll b, ll& x, ll& y) {
    x = 1, y = 0;
    ll x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        ll q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

ll mod_inv(ll x, ll m) {
    ll trash, inv;
    auto g = egcd(m, x, trash, inv);
    if (g != 1) {
        return -1;
    }
    return (inv % m + m) % m;
}

// cp algos
struct Congruence {
    ll a, m;
};

ll chinese_remainder_theorem(vector<Congruence> const& congruences) {
    ll M = 1;
    for (auto const& congruence : congruences) {
        M *= congruence.m;
    }

    ll solution = 0;
    for (auto const& congruence : congruences) {
        ll a_i = congruence.a;
        ll M_i = M / congruence.m;
        ll N_i = mod_inv(M_i, congruence.m);
        solution = (solution + a_i * M_i % M * N_i) % M;
    }
    return solution;
}

// all solutions first mod second are valid t
pair<ll, ll> t_class(ll vx, ll x, ll n) {
    ll trash1, trash2;
    auto g = egcd(egcd(vx, x, trash1, trash2), n, trash1, trash2);
    vx /= g;
    x /= g;
    n /= g;

    auto vx_inv = mod_inv(vx % n, n);
    auto neg_x = (n - x % n) % n;

    if (vx_inv == -1) {
        return {-1, -1};
    }
    return {(neg_x * vx_inv) % n, n};
}

vector<ll> primes(ll n) {
    vector<ll> res;
    auto factor_out = [&](ll p) {
        if (n % p == 0) {
            res.push_back(p);
            while (n % p == 0) {
                n /= p;
            }
        }
    };

    factor_out(2);
    ll cur = 3;
    while (cur * cur <= n) {
        factor_out(cur);
        cur += 2;
    }

    if (n != 1) {
        factor_out(n);
    }
    
    return res;
}

ll num_div(ll n, ll p) {
    ll num = 1;
    while (n % p == 0) {
        n /= p;
        num *= p;
    }
    return num;
}

ll min_t(pair<ll, ll> class1, pair<ll, ll> class2) {
    // smallest t such that t > 0, t = class1.first mod class1.second, same w 2
    auto [x1, m1] = class1;
    auto [x2, m2] = class2;

    auto p1 = primes(m1);
    auto p2 = primes(m2);
    auto ps = p1;
    for (auto x : p2) {
        ps.push_back(x);
    }
    sort(all(ps));
    ps.erase(unique(all(ps)), end(ps));

    vector<Congruence> cong;
    for (auto p : ps) {
        auto in_m1 = num_div(m1, p);
        auto in_m2 = num_div(m2, p);
        auto in_x1 = x1 % in_m1;
        auto in_x2 = x2 % in_m2;

        if (in_m1 < in_m2) {
            swap(in_m1, in_m2);
            swap(in_x1, in_x2);
        }

        // check that in_x1, in_m1 imply in_x2, in_m2
        if (in_x1 % in_m2 != in_x2) {
            return -1;
        }

        cong.push_back({in_x1, in_m1});
    }

    return chinese_remainder_theorem(cong);
}

ll ceil_div(ll a, ll b) {
    return a / b + ((a ^ b) > 0 && a % b != 0);
}

ll count(ll sx, ll ex, ll n) {
    if (sx > ex) swap(sx, ex);
    if (sx < 0) {
        auto to_push = ceil_div(-sx, n);
        sx += to_push * n;
        ex += to_push * n;
    }
    auto n_before_start = sx / n;
    auto n_before_end = ex / n;
    if (ex % n == 0) {
        n_before_end--;
    }
    return n_before_end - n_before_start;
}

ll count(ll sx, ll sy, ll ex, ll ey, ll n) {
    return count(sx, ex, n) + count(sy, ey, n);
}

void solve() {
    long long np, xp, yp, vxp, vyp;
    cin >> np >> xp >> yp >> vxp >> vyp;

    ll n, x, y, vx, vy;
    n = np;
    x = xp;
    y = yp;
    vx = vxp;
    vy = vyp;

    ll trash1, trash2;
    auto v_gcd = egcd(vx, vy, trash1, trash2);
    vx /= v_gcd;
    vy /= v_gcd;

    // find end point
    // want -vx * x^-1 mod n
    auto class1 = t_class(vx, x, n);
    auto class2 = t_class(vy, y, n);
    if (class1.first == -1 || class2.first == -1) {
        cout << "-1\n";
        return;
    }

    auto t = min_t(class1, class2);
    if (t == -1) {
        cout << "-1\n";
        return;
    }

    auto end_x = x + vx * t;
    auto end_y = y + vy * t;
    auto axis = count(x, y, end_x, end_y, n);
    auto diag = count(x + y + n, x - y + n, end_x + end_y + n, end_x - end_y + n, 2 * n);

    cout << (long long) (axis + diag) << '\n';
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

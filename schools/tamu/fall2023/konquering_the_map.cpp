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
#include <complex>

#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 2000

using namespace std;

using ll = long long;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : mi((int)(_v % MOD)) {}
    mi operator+(const mi &m2) const { return mi(v + m2.v); }
    mi operator-(const mi &m2) const { return mi(v - m2.v); }
    mi operator*(const mi &m2) const { return mi((ll) v * m2.v); }
    mi operator/(const mi &m2) const { return mi((ll) v * m2.inv().v); }
    mi &operator+=(const mi &m2) { return *this = *this + m2; }
    mi &operator-=(const mi &m2) { return *this = *this - m2; }
    mi &operator*=(const mi &m2) { return *this = *this * m2; }
    mi &operator/=(const mi &m2) { return *this = *this / m2; }
    mi pow(ll e) const {
        mi res = 1;
        mi n = *this;
        while (e > 0) {
            if (e & 1) res *= n;
            n *= n;
            e >>= 1;
        }
        return res;
    }
    mi inv() const {
        return pow(MOD - 2);
    }
};

template<typename F>
struct y_combinator_result {
    F f;
    template<typename T> explicit y_combinator_result(T &&f) : f(std::forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), std::forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(std::forward<F>(f));
}

// kactl

#define sz(x) ((int) (x).size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using vi = vector<int>;

typedef complex<double> C;
void fft(vector<C>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}

typedef vector<ll> vl;
template<int M> vl convMod(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	vl res(sz(a) + sz(b) - 1);
	int B=32-__builtin_clz(sz(res)), n=1<<B, cut=int(sqrt(M));
	vector<C> L(n), R(n), outs(n), outl(n);
	rep(i,0,sz(a)) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
	rep(i,0,sz(b)) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
	fft(L), fft(R);
	rep(i,0,n) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}
	fft(outl), fft(outs);
	rep(i,0,sz(res)) {
		ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
		ll bv = ll(imag(outl[i])+.5) + ll(real(outs[i])+.5);
		res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
	}
	return res;
}

mi f[4 * MAXN];
mi inv_f[4 * MAXN];

void precomp() {
    f[0] = 1;
    for (int i = 1; i < 4 * MAXN; i++) {
        f[i] = f[i - 1] * i;
    }
    inv_f[4 * MAXN - 1] = f[4 * MAXN - 1].inv();
    for (int i = 4 * MAXN - 2; i >= 0; i--) {
        inv_f[i] = inv_f[i + 1] * (i + 1);
    }
}

vl prepare(const vector<mi> &nums) {
    int sz = nums.size();
    vl res(sz);
    for (int i = 0; i < sz; i++) {
        res[i] = (nums[i] * inv_f[i]).v;
    }
    return res;
}

vector<mi> unprepare(const vl &nums) {
    int sz = nums.size();
    vector<mi> res(sz);
    for (int i = 0; i < sz; i++) {
        res[i] = mi(nums[i]) * f[i];
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for (int v = 1; v < n; v++) {
        int p;
        cin >> p;
        p--;

        adj[p].push_back(v);
        adj[v].push_back(p);
    }

    // {is above end, combos}
    auto dfs = y_combinator([&](auto self, int v, int p) -> pair<bool, vector<mi>> {
        if (v == n - 1) {
            return {true, {1}};
        } else {
            // currently can only make 1 path of length 0
            auto res = prepare({1});

            bool is_above = false;
            for (auto e : adj[v]) {
                if (e != p) {
                    auto [aa, combo] = self(e, v);
                    is_above |= aa;
                    auto nxt = prepare(combo);
                    res = convMod<MOD>(res, nxt);
                }
            }

            auto res2 = unprepare(res);

            // add a path of length 0 that doesn't go further down
            // also pushes everything up 1 to forcing current node
            // to be added first
            res2.insert(res2.begin(), is_above ? 0 : 1);

            return {is_above, res2};
        }
    });

    auto res = dfs(0, 0).second;

    auto tot = accumulate(res.begin(), res.end(), mi(0));
    mi ans;
    for (int i = 0; i < (int) res.size(); i++) {
        ans += res[i] * (i + 1);
    }
    cout << (ans / tot).v << '\n';

    return 0;
}

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
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 530000

using namespace std;

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

mi f[MAXN];

void precalc() {
    f[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        f[i] = f[i - 1] * i;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    int k;
    cin >> k;

    int n = 1 << k;
    vector<int> teams(n);
    vector<bool> missing(n + 1, true);
    for (int i = 0; i < n; i++) {
        cin >> teams[i];
        if (teams[i] != -1) {
            missing[teams[i]] = false;
        }
    }

    mi ans = 1;
    while (teams.size() > 1) {
        int n = teams.size();
        int unknown = 0;

        vector<int> nxt;
        for (int i = 0; i < n; i += 2) {
            if (teams[i] == -1 && teams[i + 1] == -1) {
                ans *= 2;
                unknown++;
                nxt.push_back(-1);
            } else if (teams[i] == -1 || teams[i + 1] == -1) {
                int other = max(teams[i], teams[i + 1]);
                if (other <= n / 2) {
                    unknown++;
                    nxt.push_back(other);
                } else {
                    nxt.push_back(-1);
                }
            } else {
                if (max(teams[i], teams[i + 1]) <= n / 2) {
                    ans = 0;
                    goto end;
                }
                nxt.push_back(min(teams[i], teams[i + 1]));
            }
        }

        int needed = 0;
        for (int i = n / 2 + 1; i <= n; i++) {
            if (missing[i]) {
                needed++;
            }
        }

        if (needed != unknown) {
            ans = 0;
            break;
        }

        ans *= f[needed];

        teams = nxt;
    }

end:
    cout << ans.v << '\n';

    return 0;
}

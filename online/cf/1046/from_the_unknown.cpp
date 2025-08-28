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
#include <cassert>

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

int W;

int place(const vector<int> &xs) {
    int l = 1;
    int s = 0;
    for (auto x : xs) {
        if (x > W) {
            return 0;
        } else if (s + x <= W) {
            s += x;
        } else {
            l += 1;
            s = x;
        }
    }
    return l;
}

int ask(const vector<int> &a) {
#ifdef LOCAL
    cout << "using " << sz(a) << " queries" << endl;
    return place(a);
#else
    cout << "? ";
    cout << sz(a) << ' ';
    for (auto x : a) cout << x << ' ';
    cout << endl;

    int res;
    cin >> res;
    if (res == -1) {
        exit(0);
    }
    return res;
#endif
}

void answer(int w) {
    cout << "! " << w << endl;
#ifdef LOCAL
    assert(w == W);
#endif
}

constexpr int N = 1e5;

int comp_constant(int x, int n, int W) {
    if (x > W) {
        return 0;
    }
    auto can_fit = W / x;
    return (n + can_fit - 1) / can_fit;
}

void solve() {
#ifdef LOCAL
    cin >> W;
#endif
    constexpr int total = 25000;
    constexpr int ask_first = 10500;
    constexpr int ask_later = total - ask_first;
    constexpr int ask_value = 120;

    vector<int> init(ask_first, ask_value);
    auto res1 = ask(init);

    vector<int> poss;
    rep(i, 1, N+1) {
        if (comp_constant(ask_value, ask_first, i) == res1) {
            poss.push_back(i);
        }
    }

    if (sz(poss) == 1) {
        answer(poss[0]);
    } else if (res1 == 0) {
        vector<int> all_ones(ask_later, 1);
        auto res2 = ask(all_ones);
        for (auto x : poss) {
            if (comp_constant(1, ask_later, x) == res2) {
                answer(x);
                return;
            }
        }
    } else {
        vector<int> to_ask;
        rep(i, 1, sz(poss)) {
            to_ask.push_back(poss[0]);
            to_ask.push_back(poss[i] - poss[0]);
        }

        auto res2 = ask(to_ask);
        auto saved = sz(to_ask) - res2;
        answer(poss[0] + saved);
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

#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

struct FT {
    vector<ll> s;
    FT(int n) : s(n) {}
    void update(int pos, ll dif) {
        for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
    }
    ll query(int pos) {
        ll res = 0;
        for (; pos > 0; pos &= pos - 1) res += s[pos-1];
        return res;
    }
    int lower_bound(ll sum) {
        //
        if (sum <= 0) return -1;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1) {
            if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
                pos += pw, sum -= s[pos-1];
        }
        return pos;
    }
};

constexpr int LIMIT = 2e5;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> h(n), g(n);
    rep(i, 0, n) {
        cin >> g[i];
    }
    rep(i, 0, n) {
        cin >> h[i];
    }

    auto xs = h;
    sort(all(xs));
    xs.erase(unique(all(xs)), end(xs));

    auto compress = [&](int x) {
        return (int) (lower_bound(all(xs), x) - begin(xs));
    };
    for (auto &x : g) {
        x = compress(x);
    }
    for (auto &x : h) {
        x = compress(x);
    }

    vector<vector<int>> h_pos(sz(xs));
    vector<vector<int>> g_pos(sz(xs));
    rep(i, 0, n) {
        g_pos[g[i]].push_back(i);
    }
    rep(i, 0, n) {
        h_pos[h[i]].push_back(i);
    }

    reverse(all(xs));

    ll moves = 0;
    FT rel_g(n), rel_h(n);
    for (int x = sz(xs) - 1; x >= 0; x--) {
        auto &my_g = g_pos[x];
        auto &my_h = h_pos[x];
        for (auto y : my_g) {
            rel_g.update(y, +1);
        }
        for (auto y : my_h) {
            rel_h.update(y, +1);
        }
        rep(i, 0, sz(my_g)) {
            auto orig = my_g[i];
            auto want = my_h[i];
            auto orig_relative = rel_g.query(orig+1);
            auto want_relative = rel_h.query(want+1);
            moves += abs(orig_relative - want_relative);
        }
    }

    set<int> bigger;
    vector<pair<int, int>> ops;
    rep(i, 0, n) {
        bigger.insert(i);
    }

    vector<int> start = {0};
    rep(i, 0, n) {
        start.push_back(start.back() + sz(g_pos[i]));
    }

    auto fixed = [&](int x, int i) {
        return start[x] + i;
    };

    vector<int> cur_pos(n);
    for (int x = sz(xs) - 1; x >= 0; x--) {
        rep(i, 0, sz(g_pos[x])) {
            cur_pos[fixed(x, i)] = g_pos[x][i];
        }
    }

    auto get_pos = [&](int idx) -> int {
        int ch = g[idx];
        return (int) (lower_bound(all(g_pos[ch]), idx) - begin(g_pos[ch]));
    };

    // swapping values at these indices
    auto swap = [&](int x, int y) {
        int xh = g[x];
        int yh = g[y];
        int x_idx = get_pos(x);
        int y_idx = get_pos(y);

        ops.push_back({x, y});
        g_pos[g[x]][x_idx] = y;
        g_pos[g[y]][y_idx] = x;
        ::swap(g[x], g[y]);
        ::swap(cur_pos[fixed(xh, x_idx)], cur_pos[fixed(yh, y_idx)]);
    };

    rep(x, 0, sz(xs)) {
        if (sz(ops) >= LIMIT) break;
        auto &my_g = g_pos[x];
        auto &my_h = h_pos[x];
        auto fix = [&](ll orig_relative, ll want_relative, ll i) {
            if (orig_relative < want_relative) {
                auto steps = want_relative - orig_relative;
                rep(_, 0, steps) {
                    if (sz(ops) < LIMIT) {
                        auto cur = cur_pos[fixed(x, i)];
                        auto nxt = *next(bigger.find(cur));
                        swap(cur, nxt);
                    }
                }
            } else if (orig_relative > want_relative) {
                auto steps = orig_relative - want_relative;
                rep(_, 0, steps) {
                    if (sz(ops) < LIMIT) {
                        auto cur = cur_pos[fixed(x, i)];
                        auto nxt = *prev(bigger.find(cur));
                        swap(cur, nxt);
                    }
                }
            }
        };

        vector<vector<array<ll, 3>>> runs;
        int last = -1; // 0 = L, R = 1

        rep(i, 0, sz(my_g)) {
            auto orig = my_g[i];
            auto want = my_h[i];
            auto orig_relative = rel_g.query(orig+1);
            auto want_relative = rel_h.query(want+1);
            if (orig_relative < want_relative) {
                if (last != 1) {
                    runs.push_back({});
                    last = 1;
                }
                runs.back().push_back({orig_relative, want_relative, i});
            } else {
                if (last != 0) {
                    runs.push_back({});
                    last = 0;
                }
                runs.back().push_back({orig_relative, want_relative, i});
            }
        }

        for (auto &v : runs) {
            if (sz(ops) >= LIMIT) break;
            auto [a, b, _] = v[0];
            if (a < b) {
                reverse(all(v));
            }
            for (auto [x2, y2, i] : v) {
                if (sz(ops) >= LIMIT) break;
                fix(x2, y2, i);
            }
        }

        for (auto y : my_g) {
            rel_g.update(y, -1);
        }
        for (auto y : my_h) {
            rel_h.update(y, -1);
            bigger.erase(y);
        }
    }

    cout << moves << '\n';
    for (auto [x, y] : ops) {
        cout << x+1 << ' ' << y+1 << '\n';
    }

    return 0;
}


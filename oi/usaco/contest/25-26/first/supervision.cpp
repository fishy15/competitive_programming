#include <array>
#include <iostream>
#include <vector>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using ll = long long;

constexpr int MOD = 1e9 + 7;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : v((int)(_v % MOD)) {}

    mi operator+(mi other) const { return mi(v + other.v); }
    mi operator-(mi other) const { return mi(v - other.v); }
    mi operator*(mi other) const { return mi((ll) v * other.v); }
    mi &operator+=(mi other) { return *this = *this + other; }
    mi &operator-=(mi other) { return *this = *this - other; }
    mi &operator*=(mi other) { return *this = *this * other; }

    mi pow(ll e) const {
        mi res = 1;
        mi cur = *this;
        while (e > 0) {
            if (e & 1) res *= cur;
            cur *= cur;
            e >>= 1;
        }
        return res;
    }
};

struct segtree {
    int n;
    vector<mi> st;
    vector<mi> lazy;
    segtree(int n) : n(n), st(4 * n, 0), lazy(4 * n, 1) {}

    void push(int v, int l, int r) {
        if (r - l > 1) {
            lazy[2 * v] *= lazy[v];
            lazy[2 * v + 1] *= lazy[v];
        }
        st[v] *= lazy[v];
        lazy[v] = 1;
    }

    void set(int x, mi q) {
        set(1, 0, n, x, q);
    }
    void set(int v, int l, int r, int x, mi q) {
        push(v, l, r);
        if (r - l == 1) {
            st[v] = q;
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                set(2 * v, l, m, x, q);
            } else {
                set(2 * v + 1, m, r, x, q);
            }
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }

    void upd(int x, int y, mi q) {
        upd(1, 0, n, x, y, q);
    }
    void upd(int v, int l, int r, int x, int y, mi q) {
        push(v, l, r);
        if (r <= x || y <= l) return;
        if (x <= l && r <= y) {
            lazy[v] *= q;
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(2 * v, l, m, x, y, q);
            upd(2 * v + 1, m, r, x, y, q);
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }

    mi qry(int x, int y) {
        return qry(1, 0, n, x, y);
    }
    mi qry(int v, int l, int r, int x, int y) {
        push(v, l, r);
        if (r <= x || y <= l) return 0;
        else if (x <= l && r <= y) {
            return st[v];
        } else {
            int m = (l + r) / 2;
            return qry(2 * v, l, m, x, y) + qry(2 * v + 1, m, r, x, y);
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, d;
    cin >> n >> d;

    vector<array<int, 2>> cows(n);
    vector<int> coaches;
    rep(i, 0, n) {
        cin >> cows[i][0] >> cows[i][1];
        if (cows[i][1] == 1) {
            coaches.push_back(cows[i][0]);
        }
    }

    segtree st(sz(coaches));
    int l_coach = 0;
    int r_coach = 0;
    rep(i, 0, n) {
        if (cows[i][1] == 0) {
            // is a camper
            auto pos = cows[i][0];
            while (l_coach < sz(coaches) && pos - coaches[l_coach] > d) {
                l_coach++;
            }
            if (l_coach < r_coach) {
                st.upd(l_coach, r_coach, 2);
            }
        } else {
            // is a coach
            auto prev = st.qry(0, r_coach);
            st.set(r_coach, prev + 1);
            r_coach++;
        }
    }

    auto ans = st.qry(0, sz(coaches));
    cout << ans.v << '\n';

    return 0;
}

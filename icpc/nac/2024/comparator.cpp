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
#include <bitset>

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

constexpr int MAXN = 1024;

struct expr {
    virtual bool eval(bool x, bool y) = 0;
};

struct x_expr : public expr {
    virtual bool eval(bool x, bool y) { return x; }
};

struct y_expr : public expr {
    virtual bool eval(bool x, bool y) { return y; }
};

struct zero_expr : public expr {
    virtual bool eval(bool x, bool y) { return 0; }
};

struct one_expr : public expr {
    virtual bool eval(bool x, bool y) { return 1; }
};

struct not_expr : public expr {
    expr *subexpr;
    not_expr(expr *e) : subexpr(e) {}
    virtual bool eval(bool x, bool y) {
        return !subexpr->eval(x, y);
    }
};

struct eq_expr : public expr {
    expr *left, *right;
    eq_expr(expr *l, expr *r) : left(l), right(r) {}
    virtual bool eval(bool x, bool y) {
        return left->eval(x, y) == right->eval(x, y); 
    }
};

struct and_expr : public expr {
    expr *left, *right;
    and_expr(expr *l, expr *r) : left(l), right(r) {}
    virtual bool eval(bool x, bool y) {
        return left->eval(x, y) && right->eval(x, y); 
    }
};

struct or_expr : public expr {
    expr *left, *right;
    or_expr(expr *l, expr *r) : left(l), right(r) {}
    virtual bool eval(bool x, bool y) {
        return left->eval(x, y) || right->eval(x, y); 
    }
};

struct xor_expr : public expr {
    expr *left, *right;
    xor_expr(expr *l, expr *r) : left(l), right(r) {}
    virtual bool eval(bool x, bool y) {
        return left->eval(x, y) ^ right->eval(x, y); 
    }
};

using It = string::iterator;

// priority: !=&|^
pair<expr *, It> read_expr0(It start, It end);
pair<expr *, It> read_expr_not(It start, It end);
pair<expr *, It> read_expr_eq(It start, It end);
pair<expr *, It> read_expr_and(It start, It end);
pair<expr *, It> read_expr_or(It start, It end);
pair<expr *, It> read_expr_xor(It start, It end);
pair<expr *, It> read_expr(It start, It end);

pair<expr *, It> read_expr0(It start, It end) {
    if (*start == '(') {
        auto [e, cur] = read_expr(start+1, end);
        return {e, cur+1}; // read in ')' as well
    } else {
        expr *res;
        if (*start == 'x') {
            res = new x_expr;
        } else if (*start == 'y') {
            res = new y_expr;
        } else if (*start == '0') {
            res = new zero_expr;
        } else if (*start == '1') {
            res = new one_expr;
        } else {
            cout << "failed expr0 parsing\n";
            exit(-1);
        }
        return {res, start+1};
    }
}

pair<expr *, It> read_expr_not(It start, It end) {
    int num_nots = 0;
    while (*start == '!') {
        num_nots++;
        start++;
    }

    auto [e, cur] = read_expr0(start, end);
    if (num_nots % 2 == 1) {
        return {new not_expr(e), cur};
    } else {
        return {e, cur};
    }
}

pair<expr *, It> read_expr_eq(It start, It end) {
    auto [e, nxt] = read_expr_not(start, end);
    while (nxt != end && *nxt == '=') {
        auto [e2, nxt2] = read_expr_not(nxt+1, end);
        e = new eq_expr(e, e2);
        nxt = nxt2;
    }
    return {e, nxt};
}

pair<expr *, It> read_expr_and(It start, It end) {
    auto [e, nxt] = read_expr_eq(start, end);
    while (nxt != end && *nxt == '&') {
        auto [e2, nxt2] = read_expr_eq(nxt+1, end);
        e = new and_expr(e, e2);
        nxt = nxt2;
    }
    return {e, nxt};
}

pair<expr *, It> read_expr_or(It start, It end) {
    auto [e, nxt] = read_expr_and(start, end);
    while (nxt != end && *nxt == '|') {
        auto [e2, nxt2] = read_expr_and(nxt+1, end);
        e = new or_expr(e, e2);
        nxt = nxt2;
    }
    return {e, nxt};
}

pair<expr *, It> read_expr_xor(It start, It end) {
    auto [e, nxt] = read_expr_or(start, end);
    while (nxt != end && *nxt == '^') {
        auto [e2, nxt2] = read_expr_or(nxt+1, end);
        e = new xor_expr(e, e2);
        nxt = nxt2;
    }
    return {e, nxt};
}

pair<expr *, It> read_expr(It start, It end) {
    return read_expr_xor(start, end);
}

struct rule_step {
    int a, b;
    array<array<bool, 2>, 2> truth;
    bool ret;
};

struct rule {
    vector<rule_step> rules;
    bool ret;

    bool comp(int x, int y) {
        for (auto &r : rules) {
            // in reality it should be querying from the msb,
            // but this should be equivalent and simpler
            auto b1 = (x >> r.a) & 1;
            auto b2 = (y >> r.b) & 1;
            if (r.truth[b1][b2]) {
                return r.ret;
            }
        }
        return ret;
    }
};

ll count_refl(const vector<bitset<MAXN>> &adj) {
    auto n = sz(adj);
    int ans = 0;
    rep(i, 0, n) {
        if (adj[i][i]) {
            ans++;
        }
    }
    return ans;
}

ll count_sym(const vector<bitset<MAXN>> &adj) {
    auto n = sz(adj);
    int ans = 0;
    rep(i, 0, n) {
        rep(j, 0, n) {
            if (adj[i][j] && adj[j][i]) {
                ans++;
            }
        }
    }
    return ans;
}

ll count_trans(const vector<bitset<MAXN>> &adj) {
    auto n = sz(adj);
    ll ans = 0;
    rep(i, 0, n) {
        rep(j, 0, n) {
            if (adj[i][j]) {
                // want adj[j][k] but not adj[i][k]
                auto res = ~adj[i] & adj[j];
                ans += res.count();
            }
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    // used[a][b][b1][b2] if there is something that sets it already
    vector used(k, vector(k, array<array<bool, 2>, 2>{}));

    rule comp; 
    rep(i, 0, n) {
        int a, b;
        string estr;
        int r;
        cin >> a >> b >> estr >> r;
        a--;
        b--;
        auto [e, _] = read_expr(all(estr));

        rule_step rs;
        rs.a = a;
        rs.b = b;

        bool important = false;
        rep(b1, 0, 2) {
            rep(b2, 0, 2) {
                auto v = e->eval(b1 == 1, b2 == 1);
                rs.truth[b1][b2] = v;
                if (v) {
                    if (!used[a][b][b1][b2]) {
                        used[a][b][b1][b2] = true;
                        important = true;
                    }
                }
            }
        }

        rs.ret = r == 1;
        
        if (important) {
            comp.rules.push_back(rs);
        }
    }

    int r;
    cin >> r;
    comp.ret = r == 1;

    int tot = 1 << k;
    vector adj(tot, bitset<MAXN>{});
    rep(a, 0, tot) {
        rep(b, 0, tot) {
            adj[a][b] = comp.comp(a, b);
        }
    }

    cout << count_refl(adj) << ' ' << count_sym(adj) << ' ' << count_trans(adj) << '\n';

    return 0;
}

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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

struct node {
    int m[3][3];

    node() { memset(m, 0x3f, sizeof(m)); }

    node operator+(const node &b) const {
        node res;
        for (int k = 0; k < 3; k++) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    ckmin(res.m[i][j], m[i][k] + b.m[k][j]);
                }
            }
        }
        return res;
    }

    node rev() const {
        node res;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                res.m[j][i] = m[i][j];
            }
        }
        return res;
    }

    static node I() {
        node res;
        for (int i = 0; i < 3; i++) {
            res.m[i][i] = 0;
        }
        return res;
    }
};

struct segtree {
    int n;
    vector<node> st;

    segtree(int n) : n(n), st(4 * n) {}

    void upd(int x, node y) { upd(x, y, 1, 0, n - 1); }
    void upd(int x, node y, int v, int l, int r) {
        if (l == r) {
            st[v] = y;
        } else {
            int m = (l + r) / 2;
            if (x <= m) {
                upd(x, y, 2 * v, l, m);
            } else {
                upd(x, y, 2 * v + 1, m + 1, r);
            }
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }

    node qry(int x, int y) { return qry(x, y, 1, 0, n - 1); }
    node qry(int x, int y, int v, int l, int r) {
        if (r < x || l > y) return node::I();
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return qry(x, y, 2 * v, l, m) + qry(x, y, 2 * v + 1, m + 1, r);
    }
};

struct BIT {
    int n;
    vector<int> bit;
    BIT(int n) : n(n), bit(n + 1) {}
    
    void upd(int x, int v) {
        x++;
        while (x <= n) {
            bit[x] += v;
            x += x & -x;
        }
    }

    int qry(int x) {
        x++;
        int res = 0;
        while (x > 0) {
            res += bit[x];
            x -= x & -x;
        }
        return res;
    }

    int qry(int l, int r) {
        return qry(r) - qry(l - 1);
    }
};

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

node combos[1 << 6];
node row[1 << 3];

bool ok(int m, int j) {
    return (m >> j) & 1;
}

void precomp() {
    for (int i = 0; i < (1 << 6); i++) {
        int d[6][6];
        memset(d, 0x3f, sizeof(d));

        for (int j = 0; j < 6; j++) {
            d[j][j] = 0;
        }

        for (int j = 0; j < 3; j++) {
            if (j != 2) {
                if (ok(i, j) && ok(i, j + 1)) {
                    d[j][j + 1] = 1;
                    d[j + 1][j] = 1;
                }

                j += 3;
                if (ok(i, j) && ok(i, j + 1)) {
                    d[j][j + 1] = 1;
                    d[j + 1][j] = 1;
                }
                j -= 3;
            }

            if (ok(i, j) && ok(i, j + 3)) {
                d[j][j + 3] = 1;
                d[j + 3][j] = 1;
            }
        }

        for (int c = 0; c < 6; c++) {
            for (int a = 0; a < 6; a++) {
                for (int b = 0; b < 6; b++) {
                    ckmin(d[a][b], d[a][c] + d[c][b]);
                }
            }
        }

        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                combos[i].m[j][k] = d[j][k + 3];
            }
        }
    }
}

void precomp2() {
    for (int i = 0; i < (1 << 3); i++) {
        for (int j = 0; j < 3; j++) {
            bool good = true;
            for (int k = j; k < 3; k++) {
                good &= ok(i, k);
                if (good) {
                    row[i].m[j][k] = k - j;
                    row[i].m[k][j] = k - j;
                }
            }
        }
    }
}

int get_num(array<bool, 3> a) {
    int res = 0;
    for (int i = 0; i < 3; i++) {
        if (a[i]) res += 1 << i;
    }
    return res;
}

int get_num(array<bool, 3> a, array<bool, 3> b) {
    int res = 0;
    for (int i = 0; i < 3; i++) {
        if (a[i]) res += 1 << i;
        if (b[i]) res += 1 << (i + 3);
    }
    return res;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<array<int, 3>> grid(n);
    map<int, vector<array<int, 2>>> loc;
    for (int i = 0; i < n; i++) {
        cin >> grid[i][0] >> grid[i][1] >> grid[i][2];
        for (int j = 0; j < 3; j++) {
            loc[grid[i][j]].push_back({i, j});
        }
    }

    vector<array<int, 5>> qry(m);
    for (int i = 0; i < m; i++) {
        cin >> qry[i][0] >> qry[i][1] >> qry[i][2] >> qry[i][3] >> qry[i][4];
        for (int j = 0; j < 4; j++) {
            qry[i][j]--;
        }
    }

    /* cout << "done" << endl; */

    sort(qry.begin(), qry.end(), [](auto a, auto b) { return a[4] < b[4]; });
    auto it = loc.begin();
    segtree st(n - 1);
    vector<array<bool, 3>> vis(n, array<bool, 3>{});
    vector<int> cnt(n);
    set<int> bar;
    BIT top(n), bottom(n);
    
    /* cout << "done" << endl; */

    auto add = [&](array<int, 2> p) {
        auto [x, y] = p;
        vis[x][y] = true;
        if (x > 0) {
            st.upd(x - 1, combos[get_num(vis[x - 1], vis[x])]);
        }
        if (x < n - 1) {
            st.upd(x, combos[get_num(vis[x], vis[x + 1])]);
        }
        if (y == 0) {
            top.upd(x, 1);
        }
        if (y == 2) {
            bottom.upd(x, 1);
        }
        cnt[x]++;
    };

    vector<int> start, end;
    mi tot = 1;
    for (int i = 0; i < m; i++) {
        /* cout << i << endl; */
        auto q = qry[i];
        while (it != loc.end() && it->first <= q[4]) {
            for (auto p : it->second) {
                add(p);
                if (cnt[p[0]] == 3) {
                    bar.insert(p[0]); 
                }
            }
            it++;
        }

        if (q[0] > q[2]) {
            swap(q[0], q[2]);
            swap(q[1], q[3]);
        }

        start.clear();
        end.clear();
        start.push_back(q[0]);
        end.push_back(q[2]);
        set<int>::iterator it;
        if (it = bar.upper_bound(q[0]), it != bar.begin()) {
            it--;
            if (q[1] == 0) {
                if (top.qry(*it, q[0]) == q[0] - *it + 1) {
                    start.push_back(*it);
                }
            } else if (q[1] == 2) {
                if (bottom.qry(*it, q[0]) == q[0] - *it + 1) {
                    start.push_back(*it);
                }
            }
        }

        if (it = bar.lower_bound(q[2]), it != bar.end()) {
            if (q[3] == 0) {
                if (top.qry(q[2], *it) == *it - q[2] + 1) {
                    end.push_back(*it);
                }
            } else if (q[3] == 2) {
                if (bottom.qry(q[2], *it) == *it - q[2] + 1) {
                    end.push_back(*it);
                }
            }
        }

        int ans = INF;
        for (int x : start) {
            for (int y : end) {
                node d1, d2;
                if (x == q[0]) {
                    d1 = row[get_num(vis[x])];
                } else {
                    d1 = st.qry(x, q[0] - 1);
                }

                if (y == q[2]) {
                    d2 = row[get_num(vis[y])];
                } else {
                    d2 = st.qry(q[2], y - 1);
                }

                node d3;
                if (x == y) {
                    d3 = row[get_num(vis[x])];
                } else {
                    d3 = st.qry(x, y - 1);
                }

                node res = d1.rev() + d3 + d2.rev();
                ckmin(ans, res.m[q[1]][q[3]]);
            }
        }

        if (ans != INF) {
            tot *= ans;
        }
    }

    for (int i = 0; i < 3; i++) {
        
    }

    cout << tot.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();
    precomp2();

    /* node x = combos[get_num({1, 1, 1}, {1, 0, 0})]; */

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

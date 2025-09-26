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

mi compute(const vector<vector<int>> &adj) {
    int edge_count = 0;
    for (const auto &v : adj) {
        edge_count += sz(v);
    }
    edge_count /= 2;

    int n = sz(adj);

    if (edge_count == n - 1) {
        return n;
    } else if (edge_count == n) {
        return 2;
    } else {
        return 0;
    }
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<pair<int, int>> pts(k+1);
    for (auto &[x, y] : pts) {
        cin >> x >> y;
        x--;
        y--;
    }

    vector other(n, vector(m, vector<int>{}));
    vector assign(n, vector(m, -1));
    vector<bool> is_forced(k);
    rep(i, 0, k) {
        auto p1 = pts[i];
        auto p2 = pts[i+1];
        if (abs(p1.first - p2.first) + abs(p1.second - p2.second) != 2) {
            cout << "0\n";
            return;
        }
        if (p1.first != p2.first && p1.second != p2.second) {
            auto opt1 = pair{p1.first, p2.second};
            auto opt2 = pair{p2.first, p1.second};
            other[opt1.first][opt1.second].push_back(i);
            other[opt2.first][opt2.second].push_back(i);
        }
    }

    bool valid = true;
    auto set_val = [&](auto &&self, int x, int y, int i) -> void {
        if (assign[x][y] != -1) {
            if (assign[x][y] != i) {
                valid = false;
            }
        } else {
            is_forced[i] = true;
            assign[x][y] = i;
            for (auto idx : other[x][y]) {
                if (idx != i) {
                    auto p1 = pts[idx];
                    auto p2 = pts[idx+1];
                    auto opt1 = pair{p1.first, p2.second};
                    auto opt2 = pair{p2.first, p1.second};
                    if (pair{x, y} == opt1) {
                        self(self, opt2.first, opt2.second, idx);
                    } else {
                        self(self, opt1.first, opt1.second, idx);
                    }
                }
            }
        }
    };

    rep(i, 0, k) {
        auto p1 = pts[i];
        auto p2 = pts[i+1];
        if (p1.first == p2.first || p1.second == p2.second) {
            auto middle = pair{
                (p1.first + p2.first) / 2,
                (p1.second + p2.second) / 2,
            };
            set_val(set_val, middle.first, middle.second, i);
        }
    }

    if (!valid) {
        cout << "0\n";
        return;
    }

    mi ans = 1;
    vector val(n, vector(m, -1));
    rep(i, 0, k) {
        auto p1 = pts[i];
        auto p2 = pts[i+1];
        auto start = pair{p1.first, p2.second};
        if (!is_forced[i] && val[start.first][start.second] == -1) {
            vector<vector<int>> adj{};
            auto construct_gr = [&](auto &&self, int x, int y, int pc) -> int {
                if (val[x][y] == -1) {
                    val[x][y] = sz(adj);
                    adj.push_back({});
                    for (auto idx : other[x][y]) {
                        auto p1 = pts[idx];
                        auto p2 = pts[idx+1];
                        auto opt1 = pair{p1.first, p2.second};
                        auto opt2 = pair{p2.first, p1.second};
                        pair<int, int> opt;
                        if (pair{x, y} == opt1) {
                            opt = opt2;
                        } else {
                            opt = opt1;
                        }

                        auto o = self(self, opt.first, opt.second, val[x][y]);
                        if (o < val[x][y]) {
                            adj[o].push_back(val[x][y]);
                            adj[val[x][y]].push_back(o);
                        }
                    }
                }

                return val[x][y];
            };

            construct_gr(construct_gr, start.first, start.second, -1);
            ans *= compute(adj);
        }
    }

    cout << ans.v << '\n';
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

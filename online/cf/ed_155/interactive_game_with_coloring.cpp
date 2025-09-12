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

enum result {
    ODD,
    EVEN,
    INVALID,
    UNKNOWN,
};

result comb(result a, result b) {
    if (a == INVALID || b == INVALID) {
        return INVALID;
    } else if (a == UNKNOWN) {
        return b;
    } else if (b == UNKNOWN) {
        return a;
    } else if (a == b) {
        return a;
    } else {
        return INVALID;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> par(n);
    vector<vector<int>> child(n);

    rep(i, 1, n) {
        int p;
        cin >> p;
        p--;

        par[i] = p;
        child[p].push_back(i);
    }

    // try coloring with two
    auto dfs = [&](auto &&self, int v, int d) -> result {
        result res = UNKNOWN;
        if (sz(child[v]) == 1) {
            if (d % 2 == 0) {
                res = EVEN;
            } else {
                res = ODD;
            }
        }

        for (auto e : child[v]) {
            res = comb(res, self(self, e, d + 1));
        }

        return res;
    };

    vector<int> c(n);
    auto color2 = [&](auto &&self, int v, int d) -> void {
        c[v] = d % 2;
        for (auto e : child[v]) {
            self(self, e, d + 1);
        }
    };

    bool two_works = true;
    for (auto rc : child[0]) {
        auto res = dfs(dfs, rc, 0);
        if (res == INVALID) {
            two_works = false;
            break;
        } else if (res == UNKNOWN || res == EVEN) {
            color2(color2, rc, 0);
        } else {
            color2(color2, rc, 1);
        }
    }

    if (!two_works) {
        auto color3 = [&](auto &&self, int v, int d) -> void {
            c[v] = d % 3;
            for (auto e : child[v]) {
                self(self, e, d + 1);
            }
        };

        for (auto rc : child[0]) {
            color3(color3, rc, 0);
        }
    }

    auto colors_used = *max_element(all(c)) + 1;
    cout << colors_used << ' ';
    rep(i, 1, n) {
        cout << c[i] + 1 << ' ';
    }
    cout << endl;

    while (true) {
        int typ;
        cin >> typ;

        if (typ == 0) {
            vector<int> cnt(colors_used);
            rep(i, 0, colors_used) {
                cin >> cnt[i];
            }

            int col = -1;
            if (two_works) {
                if (count(all(cnt), 1) > 1) {
                    col = 0;
                } else {
                    col = find(all(cnt), 1) - begin(cnt);
                }
            } else {
                if (cnt[0] && cnt[1]) {
                    col = 0;
                } else if (cnt[0] && cnt[2]) {
                    col = 2;
                } else if (cnt[1] && cnt[2]) {
                    col = 1;
                } else {
                    col = find(all(cnt), 1) - begin(cnt);
                }
            }

            assert(0 <= col && col < colors_used && cnt[col] > 0);
            cout << col + 1 << endl; 
        } else {
            break;
        }
    }

    return 0;
}

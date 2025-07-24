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

template<typename T, typename F>
struct segtree {
    int n;
    vector<T> st;
    F op;
    T id;
    segtree(int n, F op, T id) : n(n), st(2 * n, id), op(op), id(id) {}
    segtree(vector<T> &nums, F op, T id) : segtree(sz(nums), op, id) {
        copy(all(nums), begin(st) + n);
        for (int i = n-1; i >= 0; i--) {
            st[i] = op(st[i<<1], st[i<<1|1]);
        }
    }
    void upd(int x, T y) {
        for (x += n, st[x] = y; x > 1; x >>= 1) {
            st[x>>1] = op(st[x], st[x^1]);
        }
    }
    T qry(int l, int r) const {
        T left = id, right = id;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) left = op(left, st[l++]);
            if (r & 1) right = op(st[--r], right);
        }
        return op(left, right);
    }
};

struct DSU {
    vector<int> dsu, size;
    DSU(int n) : dsu(n), size(n, 1) {
        iota(all(dsu), 0);
    }
    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }
    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (size[x] < size[y]) swap(x, y);
            dsu[y] = x;
            size[x] += size[y];
        }
    }
};

struct comp {
    bool id;
    int comp_cnt;
    array<int, 6> comps;
    friend ostream &operator<<(ostream &os, const comp &c) {
        os << c.id << ' ' << c.comp_cnt << " [ ";
        rep(i, 0, 6) cout << c.comps[i] << ' ';
        os << "]";
        return os;
    }
};

constexpr int MAX_LABEL = 4;
DSU dsu(2 * MAX_LABEL);

comp combine(const comp &comp1, const comp &comp2) {
    if (comp1.id) return comp2;
    if (comp2.id) return comp1;

    iota(all(dsu.dsu), 0);
    fill(all(dsu.size), 1);

    rep(i, 0, 3) {
        if (comp1.comps[3+i] != -1 && comp2.comps[i] != -1) {
            dsu.join(comp1.comps[3+i], comp2.comps[i] + MAX_LABEL);
        }
    }

    int outside_cnt = 0;
    array<int, 2 * MAX_LABEL> outside;
    outside.fill(-1);

    rep(i, 0, 3) {
        if (comp1.comps[i] != -1) {
            auto label = dsu.find(comp1.comps[i]);
            if (outside[label] == -1) {
                outside[label] = outside_cnt;
                outside_cnt++;
            }
        }
    }
    rep(i, 0, 3) {
        if (comp2.comps[3+i] != -1) {
            auto label = dsu.find(comp2.comps[3+i] + MAX_LABEL);
            if (outside[label] == -1) {
                outside[label] = outside_cnt;
                outside_cnt++;
            }
        }
    }

    int complete_ccs = comp1.comp_cnt + comp2.comp_cnt;
    bitset<2 * MAX_LABEL> finished_middle;
    rep(i, 0, 3) {
        if (comp1.comps[3+i] != -1) {
            auto label = dsu.find(comp1.comps[3+i]);
            if (outside[label] == -1) {
                finished_middle[label] = true;
            }
        }
    }
    rep(i, 0, 3) {
        if (comp2.comps[i] != -1) {
            auto label = dsu.find(comp2.comps[i] + MAX_LABEL);
            if (outside[label] == -1) {
                finished_middle[label] = true;
            }
        }
    }
    complete_ccs += finished_middle.count();

    array<int, 6> side;
    side.fill(-1);
    rep(i, 0, 3) {
        if (comp1.comps[i] != -1) {
            auto label = dsu.find(comp1.comps[i]);
            side[i] = outside[label];
        }
    }
    rep(i, 0, 3) {
        if (comp2.comps[3+i] != -1) {
            auto label = dsu.find(comp2.comps[3+i] + MAX_LABEL);
            side[3+i] = outside[label];
        }
    }

    auto res = comp {
        false,
        complete_ccs,
        side,
    };

    return res;
}

int get_ccs(const comp &info) {
    set<int> s;
    rep(i, 0, 6) {
        if (info.comps[i] != -1) {
            s.insert(info.comps[i]);
        }
    }
    return info.comp_cnt + sz(s);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    array<string, 3> grid{};
    rep(i, 0, 3) {
        cin >> grid[i];
    }

    vector<comp> init_comps(n);
    rep(i, 0, n) {
        array<int, 6> side;
        side.fill(-1);
        int cur = 0;
        rep(j, 0, 3) {
            if (grid[j][i] == '1') {
                if (j > 0 && grid[j-1][i] == '1') {
                    side[j] = side[3+j] = side[j-1];
                } else {
                    side[j] = side[3+j] = cur;
                    cur++;
                }
            }
        }
        init_comps[i] = comp {
            false,
            0,
            side,
        };
    }

    comp id{true, {}, {}};
    segtree st(init_comps, combine, id);

    int q;
    cin >> q;

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;
        cout << get_ccs(st.qry(l, r)) << '\n';
    }

    return 0;
}

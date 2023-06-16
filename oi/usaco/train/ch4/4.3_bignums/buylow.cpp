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

struct bigint {
    vector<int> vals;

    bigint() : bigint(0) {}
    bigint(int n) {
        while (n > 0) {
            vals.push_back(n % 10);
            n /= 10;
        }
    }

    bigint operator+(const bigint &bi) const {
        bigint res;
        int carry = 0;
        int digs = max(vals.size(), bi.vals.size());
        for (int i = 0; i < digs; i++) {
            int a = i >= (int)(vals.size()) ? 0 : vals[i];
            int b = i >= (int)(bi.vals.size()) ? 0 : bi.vals[i];
            int tot = a + b + carry;
            res.vals.push_back(tot % 10);
            carry = tot / 10;
        }

        if (carry > 0) {
            res.vals.push_back(carry);
        }

        return res;
    }
};

struct node {
    int len;
    bigint combo;
    node() : node(0, 0) {}
    node(int len, bigint combo) : len(len), combo(combo) {}

    node operator+(const node &n2) const {
        if (len > n2.len) {
            return *this;
        } else if (len < n2.len) {
            return n2;
        } else {
            return node(len, combo + n2.combo);
        }
    }
};

struct segtree {
    int n;
    vector<node> st;
    segtree(int n) : n(n) {
        st.resize(4 * n);
    }

    void upd(int x, node y) { upd(1, x, y, 1, n); } 
    void upd(int v, int x, node y, int l, int r) {
        if (l == r) {
            st[v] = y;
        } else {
            int m = (l + r) / 2;
            if (x <= m) {
                upd(2 * v, x, y, l, m);
            } else {
                upd(2 * v + 1, x, y, m + 1, r);
            }
            st[v] = st[2 * v] + st[2 * v + 1];
        }
    }

    node qry(int x, int y) const { return qry(1, x, y, 1, n); }
    node qry(int v, int x, int y, int l, int r) const {
        if (y < l || x > r) {
            return node();
        } else if (l <= x && y <= r) {
            return st[v];
        } else {
            int m = (l + r) / 2;
            return qry(2 * v, x, y, l, m) + qry(2 * v + 1, x, y, m + 1, r);
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    return 0;
}

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

// change if necessary
#define MAXN 1000000

using namespace std;

struct lazy_segtree {
    int n;
    mutable vector<int> st;
    mutable vector<int> lazy;
    lazy_segtree() : lazy_segtree(0) {}
    lazy_segtree(int n) : n(n), st(4 * n), lazy(4 * n) {}
    lazy_segtree(int n, vector<int> &nums) : lazy_segtree(n) { build(1, 0, n - 1, nums); }
    void build(int v, int l, int r, const vector<int> &nums) {
        if (l == r) {
            st[v] = nums[l];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, nums);
            build(2 * v + 1, m + 1, r, nums);
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }
    void push(int v, int l, int r) const {
        if (l != r) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        st[v] += lazy[v];
        lazy[v] = 0;
    }
    void upd(int x, int y, int q) { upd(x, y, q, 1, 0, n - 1); }
    void upd(int x, int y, int q, int v, int l, int r) {
        push(v, l, r);
        if (r < x || l > y) return;
        if (x <= l && r <= y) {
            lazy[v] += q;
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(x, y, q, 2 * v, l, m);
            upd(x, y, q, 2 * v + 1, m + 1, r);
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }
    int qry(int x, int y) const { return qry(x, y, 1, 0, n - 1); }
    int qry(int x, int y, int v, int l, int r) const {
        push(v, l, r);
        if (r < x || l > y) return INF;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return min(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m + 1, r));
    }
};

struct info {
    int n;
    string s;
    lazy_segtree st;
    set<int> two_start;

    info(const string &s) : n(s.size()), s(s) {
        vector<int> delta(n);
        for (int i = 0; i < n; i++) {
            auto d = (s[i] == '(') ? 1 : -1;
            delta[i] = d + (i > 0 ? delta[i - 1] : 0);
        }

        st = lazy_segtree(n, delta);

        for (int i = 0; i < n; i++) {
            if (i < n - 1 && s[i] == '(' && s[i + 1] == '(') {
                two_start.insert(i);
            }
        }

        two_start.insert(n);
    }

    void upd(int x) {
        if (s[x] == '(') {
            s[x] = ')';
            st.upd(x, n, -2);

            if (x > 0) {
                if (s[x - 1] == '(') {
                    two_start.erase(x - 1);
                }
            }

            if (x < n - 1) {
                if (s[x + 1] == '(') {
                    two_start.erase(x);
                }
            }
        } else {
            s[x] = '(';
            st.upd(x, n, 2);

            if (x > 0) {
                if (s[x - 1] == '(') {
                    two_start.insert(x - 1);
                }
            }

            if (x < n - 1) {
                if (s[x + 1] == '(') {
                    two_start.insert(x);
                }
            }
        }
    }

    bool qry() const {
        return st.qry(0, *two_start.begin() - 1) >= 0;
    }
};

string rev(string s) {
    reverse(s.begin(), s.end());
    for (char &c : s) {
        if (c == '(') {
            c = ')';
        } else {
            c = '(';
        }
    }
    return s;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;

    if (n % 2 == 1) {
        while (q--) {
            cout << "NO\n";
        }
        return 0;
    }

    info front(s), back(rev(s));

    while (q--) {
        int x;
        cin >> x;
        x--;

        front.upd(x);
        back.upd(n - x - 1);
        cout << (front.qry() && back.qry() ? "YES" : "NO") << '\n';
    }

    return 0;
}

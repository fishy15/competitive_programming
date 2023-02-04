// segtree (point add update, range min query)
struct segtree {
    int n;
    vector<int> st;
    segtree(int n) : n(n), st(4 * n) {}
    segtree(int n, vector<int> &nums) : segtree(n) { build(1, 0, n, nums); }
    void build(int v, int l, int r, vector<int> &nums) {
        if (l + 1 == r) {
            st[v] = nums[l];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, nums);
            build(2 * v + 1, m, r, nums);
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }
    void upd(int x, int y) { upd(1, 0, n, x, y); }
    void upd(int v, int l, int r, int x, int y) {
        if (l + 1 == r) {
            st[v] = y;
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                upd(2 * v, l, m, x, y);
            } else {
                upd(2 * v + 1, m, r, x, y);
            }
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }
    int qry(int x, int y) const { return qry(1, 0, n, x, y + 1); }
    int qry(int v, int l, int r, int x, int y) const {
        if (r <= x || y <= l) return 0;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return max(qry(2 * v, l, m, x, y), qry(2 * v + 1, m, r, x, y));
    }
};

#include <vector>
using namespace std;

// lazy segtree (range add update, range min query)
struct lazy_segtree {
    int n;
    mutable vector<int> st;
    mutable vector<int> lazy;
    lazy_segtree(int n) : n(n), st(4 * n), lazy(4 * n) {}
    lazy_segtree(int n, vector<int> &nums) : lazy_segtree(n) { build(1, 0, n - 1, nums); }
    void build(int v, int l, int r, const vector<int> &nums) {
        if (l == r) {
            st[v] = nums[l];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, nums);
            build(2 * v + 1, m + 1, r, nums);
            st[v] = max(st[2 * v], st[2 * v + 1]);
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
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }
    int qry(int x, int y) const { return qry(x, y, 1, 0, n - 1); }
    int qry(int x, int y, int v, int l, int r) const {
        push(v, l, r);
        if (r < x || l > y) return 0;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return max(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m + 1, r));
    }
};

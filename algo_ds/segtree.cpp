// segtree (point add update, range min query)
struct segtree {
    int st[4 * MAXN];
    void build(int v, int l, int r) {
        if (l == r) {
            st[v] = nums[l];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m);
            build(2 * v + 1, m + 1, r);
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }
    void upd(int x, int y, int v = 1, int l = 0. int r = n - 1) {
        if (l == r) {
            st[v] = y;
        } else {
            int m = (l + r) / 2;
            if (m <= x) {
                upd(x, y, 2 * v, l, m);
            } else {
                upd(x, y, 2 * v + 1, m + 1, r);
            }
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }
    int qry(int x, int y, int v = 1, int l = 0, int r = n - 1) {
        if (r < x || l > y) return 0;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return max(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m + 1, r));
    }
};

// lazy segtree (range add update, range min query)
struct lazy_segtree {
    int st[4 * MAXN];
    int lazy[4 * MAXN];
    void build(int v, int l, int r) {
        if (l == r) {
            st[v] = nums[l];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m);
            build(2 * v + 1, m + 1, r);
            st[v] = max(st[2 * v], st[2 * v + 1]);
        }
    }
    void push(int v, int l, int r) {
        if (l != r) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        st[v] += lazy[v];
        lazy[v] = 0;
    }
    void upd(int x, int y, int q, int v = 1, int l = 0, int r = m - 1) {
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
    int qry(int x, int y, int v = 1, int l = 0, int r = m - 1) {
        push(v, l, r);
        if (r < x || l > y) return 0;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return max(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m + 1, r));
    }
};

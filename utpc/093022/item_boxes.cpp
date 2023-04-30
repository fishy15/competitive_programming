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

struct lazyst {
    struct node {
        int v;
        bool set;
        node *l, *r;
        node() : node(0) {}
        node(int v) : v(v), set(false), l(nullptr), r(nullptr) {}
    };

    int n;
    int total_l, total_r;
    node *root;
    deque<node> buffer;

    lazyst(int l, int r) : total_l(l), total_r(r) {
        root = new_node();
    }

    void push(node *cur, int l, int r) {
        if (cur->set) {
            cur->v = (r - l);
            cur->set = false;
            
            if (l != r + 1) {
                if (cur->l == nullptr) cur->l = new_node();
                if (cur->r == nullptr) cur->r = new_node();

                cur->l->set = true;
                cur->r->set = true;
            }
        }
    }

    void set(int x, int y) {
        set(root, x, y, total_l, total_r);
    }

    int get(node *cur) {
        return cur == nullptr ? 0 : cur->v;
    }

    void set(node *&cur, int x, int y, int l, int r) {
        if (cur == nullptr) cur = new_node();
        push(cur, l, r);

        if (y <= l || x >= r) return;
        if (x <= l && r <= y) {
            cur->set = true;
            push(cur, l, r);
        } else {
            int m = l + (r - l) / 2;
            set(cur->l, x, y, l, m);
            set(cur->r, x, y, m, r);
            cur->v = get(cur->l) + get(cur->r);
        }
    }

    int qry(int x, int y) {
        return qry(root, x, y, total_l, total_r);
    }

    int qry(node *p, int x, int y, int l, int r) {
        if (p == nullptr) return 0;

        push(p, l, r);
        if (y <= l || x >= r) {
            return 0;
        } else if (x <= l && r <= y) {
            return p->v;
        } else {
            int m = l + (r - l) / 2;
            return qry(p->l, x, y, l, m) + qry(p->r, x, y, m, r);
        }
    }

    template<typename... Args>
    node *new_node(Args... args) {
        buffer.emplace_back(args...);
        return &buffer.back();
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    lazyst st(0, 1'000'000'000);

    int q;
    cin >> q;

    while (q--) {
        int t, x, y;
        cin >> t >> x >> y;
        x--;
        if (t == 1) {
            cout << st.qry(x, y) << '\n';
        } else {
            st.set(x, y);
        }
    }

    return 0;
}

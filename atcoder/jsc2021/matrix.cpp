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
#define MAXN 200010

using namespace std;

struct segtree {
    struct Node {
        Node *l, *r;
        int cnt;
        ll sum;

        Node() {
            l = r = nullptr;
            cnt = sum = 0;
        }

        Node operator+(const Node &b) const {
            Node res;
            res.cnt = this->cnt + b.cnt;
            res.sum = this->sum + b.sum;
            return res;
        }
    };

    deque<Node> dq;
    segtree() {
        dq.push_back(Node());
    }

    Node *new_node() {
        dq.push_back(Node());
        return &dq.back();
    }

    Node get(Node *p) {
        return p ? *p : Node();
    }

    void upd(int x, int y) { upd(&dq[0], 0, 1e8, x, y); }
    void upd(Node *p, int l, int r, int x, int y) {
        if (l == r) {
            p->cnt += y;
            p->sum += x * y;
        } else {
            int m = (l + r) / 2;
            if (x <= m) {
                if (!p->l) p->l = new_node();
                upd(p->l, l, m, x, y);
            } else {
                if (!p->r) p->r = new_node();
                upd(p->r, m + 1, r, x, y);
            }

            Node res = get(p->l) + get(p->r);
            p->cnt = res.cnt;
            p->sum = res.sum;
        }
    }

    Node qry(int x, int y) { return qry(&dq[0], 0, 1e8, x, y); }
    Node qry(Node *p, int l, int r, int x, int y) {
        if (p == nullptr || r < x || l > y) return Node();
        if (x <= l && r <= y) {
            return *p;
        }
        int m = (l + r) / 2;
        return qry(p->l, l, m, x, y) + qry(p->r, m + 1, r, x, y);
    }
};

segtree a, b;
ll cur_a[MAXN];
ll cur_b[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, q;
    cin >> n >> m >> q;

    a.upd(0, n);
    b.upd(0, m);
    ll ans = 0;

    while (q--) {
        int t, x, y; 
        cin >> t >> x >> y;
        x--;
        if (t == 1) {
            auto res = b.qry(cur_a[x], 1e8);
            ans -= res.sum;
            ans -= (m - res.cnt) * cur_a[x];

            a.upd(cur_a[x], -1);
            cur_a[x] = y;
            a.upd(cur_a[x], 1);

            res = b.qry(cur_a[x], 1e8);
            ans += res.sum;
            ans += (m - res.cnt) * cur_a[x];
        } else {
            auto res = a.qry(cur_b[x], 1e8);
            ans -= res.sum;
            ans -= (n - res.cnt) * cur_b[x];

            b.upd(cur_b[x], -1);
            cur_b[x] = y;
            b.upd(cur_b[x], 1);

            res = a.qry(cur_b[x], 1e8);
            ans += res.sum;
            ans += (n - res.cnt) * cur_b[x];
        }

        cout << ans << '\n';
    }

    return 0;
}

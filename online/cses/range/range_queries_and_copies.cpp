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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200000

using namespace std;

struct node {
    int l, r; ll v;
    node *c[2];
    node(int l, int r, ll v) : l(l), r(r), v(v) {
        if (l != r) {
            int m = (l + r) / 2;
            c[0] = new node(l, m, 0);
            c[1] = new node(m + 1, r, 0);
        } else {
            c[0] = nullptr;
            c[1] = nullptr;
        }
    }
    node(node* other) {
        l = other->l;
        r = other->r;
        v = other->v;
        c[0] = other->c[0];
        c[1] = other->c[1];
    }
    void upd(int x, int v) {
        if (l == r) {
            this->v = v;
        } else {
            int m = (l + r) / 2;
            if (x <= m) {
                c[0] = new node(c[0]);
                c[0]->upd(x, v);
            } else {
                c[1] = new node(c[1]);
                c[1]->upd(x, v);
            }
            this->v = c[0]->v + c[1]->v;
        }
    }
    ll qry(int x, int y) {
        if (x <= l && r <= y) return v;
        if (r < x || l > y) return 0;
        return c[0]->qry(x, y) + c[1]->qry(x, y);
    }
};

int n, q;
vector<node*> st;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    st.push_back(new node(1, n, 0));

    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        st[0]->upd(i, x);
    }

    for (int i = 0; i < q; i++) {
        int t, k; cin >> t >> k;
        k--;
        if (t == 1) {
            int a, x; cin >> a >> x;
            st[k]->upd(a, x);
        } else if (t == 2) {
            int a, b; cin >> a >> b;
            cout << st[k]->qry(a, b) << '\n';
        } else {
            st.push_back(new node(st[k]));
        }
    }

    return 0;
}

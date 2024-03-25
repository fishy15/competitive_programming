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
#define MAXN 200010

using namespace std;

struct st {
    struct node {
        int l, r, v;
        int c[2];
        node(int l, int r) : l(l), r(r) {
            v = 0;
            c[0] = -1;
            c[1] = -1;
        } 
    };
    vector<node> dq;
    int head = -1;
    int nn(int l, int r) { dq.emplace_back(l, r); return dq.size() - 1; }
    void upd(int n, int x, int v) {
        dq[n].v += v;
        int l = dq[n].l;
        int r = dq[n].r;
        if (l != r) {
            int m = l + (r - l) / 2;
            if (x <= m) {
                if (dq[n].c[0] == -1) dq[n].c[0] = nn(l, m);
                upd(dq[n].c[0], x, v);
            } else {
                if (dq[n].c[1] == -1) dq[n].c[1] = nn(m + 1, r);
                upd(dq[n].c[1], x, v);
            }
        }
    }
    int qry(int n, int x, int y) {
        int l = dq[n].l;
        int r = dq[n].r;
        if (x <= l && r <= y) return dq[n].v;
        if (y < l || x > r) return 0;
        int res = 0;
        if (dq[n].c[0] != -1) res += qry(dq[n].c[0], x, y);
        if (dq[n].c[1] != -1) res += qry(dq[n].c[1], x, y);
        return res;
    }
    st(int x, int y) { head = nn(x, y); }
    void upd(int x, int v) { return upd(head, x, v); };
    int qry(int x, int y) { return qry(head, x, y); };
};

int n, q;
int nums[MAXN];
st segtree = st(1, 1000000000);

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        segtree.upd(nums[i], 1);
    }

    while (q--) {
        char t; cin >> t;
        if (t == '!') {
            int k, x; cin >> k >> x;
            segtree.upd(nums[k], -1);
            nums[k] = x;
            segtree.upd(nums[k], 1);
        } else {
            int a, b; cin >> a >> b;
            cout << segtree.qry(a, b) << '\n';
        }
    }

    return 0;
}

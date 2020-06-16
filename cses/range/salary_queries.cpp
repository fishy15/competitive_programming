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

struct node {
    int l, r, v;
    node *c[2];
    node(int l, int r) : l{l}, r{r} {
        v = 0;
        c[0] = nullptr;
        c[1] = nullptr;
    } 
    void upd(int x, int v) {
        this->v += v;
        if (l != r) {
            int m = l + (r - l) / 2;
            if (x <= m) {
                if (!c[0]) c[0] = new node(l, m);
                c[0]->upd(x, v);
            } else {
                if (!c[1]) c[1] = new node(m + 1, r);
                c[1]->upd(x, v);
            }
        }
    }
    int qry(int x, int y) {
        if (x <= l && r <= y) return v;
        if (y < l || x > r) return 0;
        int res = 0;
        if (c[0]) res += c[0]->qry(x, y);
        if (c[1]) res += c[1]->qry(x, y);
        return res;
    }
};

int n, q;
int nums[MAXN];
node *st = new node(1, 1000000000);

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        st->upd(nums[i], 1);
    }

    while (q--) {
        char t; cin >> t;
        if (t == '!') {
            int k, x; cin >> k >> x;
            st->upd(nums[k], -1);
            nums[k] = x;
            st->upd(nums[k], 1);
        } else {
            int a, b; cin >> a >> b;
            cout << st->qry(a, b) << '\n';
        }
    }

    return 0;
}

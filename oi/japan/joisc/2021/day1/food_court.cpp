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
#define MAXN 250010

using namespace std;

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

struct BIT {
    int n;
    vector<ll> bit;

    BIT(int n) : n(n), bit(n) {}

    void upd(int x, ll q) {
        x++;
        while (x <= n) {
            bit[x - 1] += q;
            x += x & -x;
        }
    }

    ll qry(int x) {
        ll res = 0;
        while (x > 0) {
            res += bit[x - 1];
            x -= x & -x;
        }
        return res;
    }

    int bsearch(ll r) {
        int cur = 0;
        ll sum = 0;
        for (int i = (1 << 20); i > 0; i /= 2) {
            if (cur + i <= n && sum + bit[cur + i - 1] <= r) {
                cur += i;
                sum += bit[cur - 1];
            }
        }
        return cur;
    }
};

BIT tot_add(0);

// represents max(a, x + b)
struct Func {
    ll a, b;

    Func() : Func(0, 0) {}
    Func(ll a, ll b) : a(a), b(b) {}

    ll operator()() { return max(a, b); }

    Func operator+(const Func &f2) const {
        return Func(max(a, b + f2.a), b + f2.b);
    }
};

template<typename Node>
struct segtree {
    int n;
    vector<Node> lazy;

    segtree(int n) : n(n), lazy(4 * n) {}

    void push(int v, int l, int r) {
        if (l + 1 != r) {
            lazy[2 * v] = lazy[v] + lazy[2 * v];
            lazy[2 * v + 1] = lazy[v] + lazy[2 * v + 1];
            lazy[v] = Node();
        }
    }

    void upd(int x, int y, Node q) { upd(1, 0, n, x, y, q); }
    void upd(int v, int l, int r, int x, int y, Node q) {
        push(v, l, r);
        if (r <= x || l >= y) return;
        if (x <= l && r <= y) {
            lazy[v] = q + lazy[v];
            push(v, l, r);
        } else {
            int m = (l + r) / 2;
            upd(2 * v, l, m, x, y, q);
            upd(2 * v + 1, m, r, x, y, q);
        }
    }

    ll qry(int a) { return qry(1, 0, n, a)(); }
    Node qry(int v, int l, int r, int a) {
        push(v, l, r);
        if (l + 1 == r) {
            return lazy[v];
        } else {
            int m = (l + r) / 2;
            if (a < m) {
                return qry(2 * v, l, m, a);
            } else {
                return qry(2 * v + 1, m, r, a);
            }
        }
    }
};

int n, m, q;
array<ll, 5> qry[MAXN];
vector<pair<ll, int>> in_q;
vector<int> add[MAXN]; // elements to add to the queue
vector<int> rem[MAXN]; // elements to remove from the queue
vector<pair<ll, int>> to_ans[MAXN];
vector<ll> ans;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> q;
    for (int i = 0; i < q; i++) {
        qry[i] = {0, 0, 0, 0, 0};
        cin >> qry[i][0];
        switch (qry[i][0]) {
            case 1: 
                cin >> qry[i][1] >> qry[i][2] >> qry[i][3] >> qry[i][4];
                break;
            case 2:
                cin >> qry[i][1] >> qry[i][2] >> qry[i][3];
                break;
            case 3:
                cin >> qry[i][1] >> qry[i][2];
                break;
        }
    }

    segtree<Func> st(n);
    tot_add = BIT(n);

    for (int i = 0; i < q; i++) {
        auto qq = qry[i];
        if (qq[0] == 1) {
            auto [t, l, r, c, k] = qq;
            l--;
            add[l].push_back(in_q.size());
            rem[r].push_back(in_q.size());
            in_q.push_back({k, c});
            st.upd(l, r, Func(k, k));
            tot_add.upd(l, k);
            tot_add.upd(r, -k);
        } else if (qq[0] == 2) {
            auto [t, l, r, k, _] = qq;
            l--;
            st.upd(l, r, Func(0, -k));
        } else {
            auto [t, a, b, _, __] = qq;
            a--; b--;
            ll num_q = st.qry(a);
            ll p_idx = num_q <= b ? -1 : tot_add.qry(a + 1) - num_q + b;
            to_ans[a].push_back({p_idx, ans.size()});
            ans.emplace_back();
        }
    }

    int sz = in_q.size();
    BIT bit(sz);
    for (int i = 0; i < n; i++) {
        for (int x : add[i]) {
            bit.upd(x, in_q[x].first);
        }

        for (int x : rem[i]) {
            bit.upd(x, -in_q[x].first);
        }

        for (auto [loc, idx] : to_ans[i]) {
            if (loc == -1) {
                ans[idx] = 0;
            } else {
                int pos = bit.bsearch(loc);
                ans[idx] = in_q[pos].second;
            }
        }
    }

    for (int x : ans) {
        cout << x << '\n';
    }

    return 0;
}

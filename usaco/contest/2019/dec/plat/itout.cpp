/*
 * Note that the values that we don't pick have to form an increasing sequence, and then everything else can
 * be moved appropriately. Therefore, we want to figure out the LIS of the sequence to get the answer. In 
 * order to determine what is the kth smallest set of values to pick, we need to figure out the kth 
 * biggest LIS and take its compliment. We can do this by storing {length[i], cnt[i]}, which tells us the
 * length of the longest increasing subsequence that starts at i and the number of increasing subsequences
 * of that length. By storing this value in a persistent segtree, where we update vertices in order from
 * the biggest value to the smallest value, we will be able to query LIS information over intervals where
 * we ignore all values less than a given value. All we have to do know is binary search for the 
 * largest value where at least k LIS's exist and then recurse from there.
 */

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
#define MAXN 100010

using namespace std;

int n;
ll k;
int nums[MAXN];
int inv[MAXN];
bool ok[MAXN];

struct pst {
    struct node {
        pair<ll, ll> v; // length, count
        int l, r;
        node *c[2];
    };

    pair<ll, ll> comb(pair<ll, ll> p1, pair<ll, ll> p2) {
        if (p1.first == p2.first) {
            return {p1.first, min<ll>(p1.second + p2.second, INFLL)};
        }
        return max(p1, p2);
    }

    deque<node> dq;
    vector<node*> st; // 0 is default value, will be replaced at the end
    node *cur;

    pst(int n) {
        st.resize(n + 1);
        cur = st[0] = new_node(0, n);
    }

    node *new_node(node *old) {
        dq.push_back(*old);
        return &dq.back();
    }

    node *new_node(int l, int r) {
        node n;
        n.l = l;
        n.r = r;
        if (l == r) {
            n.c[0] = n.c[1] = nullptr;
        } else {
            int m = (l + r) / 2;
            n.c[0] = new_node(l, m);
            n.c[1] = new_node(m + 1, r);
        }
        dq.push_back(n);
        return &dq.back();
    }

    void upd(node *p, int x, pair<ll, ll> v) {
        if (p->l == p->r) {
            p->v = v;
        } else {
            int m = (p->l + p->r) / 2;
            if (x <= m) {
                p->c[0] = new_node(p->c[0]);
                upd(p->c[0], x, v);
            } else {
                p->c[1] = new_node(p->c[1]);
                upd(p->c[1], x, v);
            }
            p->v = comb(p->c[0]->v, p->c[1]->v);
        }
    }

    pair<ll, ll> qry(node *p, int x, int y) {
        if (x > p->r || y < p->l) {
            return {0, 0};
        } else if (x <= p->l && p->r <= y) {
            return p->v;
        } else {
            return comb(qry(p->c[0], x, y), qry(p->c[1], x, y));
        }
    }
} st(0);

int main() {
    ifstream fin("itout.in");
    ofstream fout("itout.out");

    fin >> n >> k;
    for (int i = 1; i <= n; i++) {
        fin >> nums[i];
        inv[nums[i]] = i;
    }

    st = pst(n);
    vector<pair<int, int>> ord;

    for (int i = 0; i <= n; i++) {
        ord.push_back({-nums[i], i});
    }

    sort(ord.begin(), ord.end());

    for (auto [_, loc] : ord) {
        auto res = st.qry(st.cur, loc + 1, n);
        if (res.first == 0) {
            st.cur = st.st[loc] = st.new_node(st.cur);
            st.upd(st.cur, loc, {1, 1});
        } else {
            st.cur = st.st[loc] = st.new_node(st.cur);
            st.upd(st.cur, loc, {res.first + 1, res.second});
        }
    }

    int cur = 0;
    int ans = n + 1;
    while (cur != -1) {
        ok[cur] = true;
        ans--;
        int loc = inv[cur];
        pair<ll, ll> cur_q = st.qry(st.st[loc], loc, loc);
        if (cur_q.first == 1) break;
        int l = cur + 1;
        int r = n;
        int ans = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            pair<ll, ll> qry = st.qry(st.st[inv[m]], loc + 1, n);
            if (qry.first + 1 != cur_q.first || qry.second < k) {
                r = m - 1;
            } else {
                l = m + 1;
                ans = m;
            }
        }
        if (ans != -1) {
            auto q = st.qry(st.st[inv[ans + 1]], loc + 1, n);
            if (q.first + 1 == cur_q.first) {
                k -= st.qry(st.st[inv[ans + 1]], loc + 1, n).second;
            }
        }
        cur = ans;
    }

    fout << ans << '\n';
    for (int i = 1; i <= n; i++) {
        if (!ok[i]) {
            fout << i << '\n';
        }
    }

    return 0;
}

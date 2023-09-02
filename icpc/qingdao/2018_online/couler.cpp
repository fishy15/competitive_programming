#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define INF 0x3f3f3f3f

struct pst {
    struct node {
        node *left, *right;
        int cnt;
        
        node() : left(nullptr), right(nullptr), cnt{} {}
    };
    
    deque<node> buffer;
    vector<node *> roots;
    
    node *new_node() {
        buffer.emplace_back();
        return &buffer.back();
    }
    
    int n;
    pst(int _n) : n(_n) { 
        roots.push_back(build(0, n));
    }
    
    node *build(int l, int r) {
        auto res = new_node();
        if (l + 1 != r) {
            int m = (l + r) / 2;
            res->left = build(l, m);
            res->right = build(m, r);
        }
        return res;
    }
    
    void upd(int x, int q) {
        roots.push_back(upd(x, q, roots.back(), 0, n));
    }
    node *upd(int x, int q, node *v, int l, int r) {
        auto res = new_node();
        *res = *v;
        if (l + 1 == r) {
            res->cnt += q;
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                res->left = upd(x, q, v->left, l, m);
            } else {
                res->right = upd(x, q, v->right, m, r);
            }
            res->cnt = res->left->cnt + res->right->cnt;
        }
        return res;
    }
    
    int qry(int tl, int tr, int x, int y) { return qry(tr, x, y) - qry(tl, x, y); }
    int qry(int t, int x, int y) { return qry(x, y, roots[t], 0, n); }
    int qry(int x, int y, node *v, int l, int r) {
        if (r <= x || l >= y) return 0;
        if (x <= l && r <= y) return v->cnt;
        int m = (l + r) / 2;
        return qry(x, y, v->left, l, m) + qry(x, y, v->right, m, r);
    }
};

int sz(pair<int, int> i) {
    return i.second - i.first;
}

void solve() {
    int n;
    cin >> n;
    
    vector<int> nums(n);
    for (auto &x : nums) {
        cin >> x;
        x--;
    }
    
    vector<ll> p_enc(n);
    for (auto &x : p_enc) {
        cin >> x;
    }
    
    pst st(n);
    for (int i = 0; i < n; i++) {
        st.upd(nums[i], 1);
    }
    
    multiset<ll, greater<>> cur_ans;
    map<pair<int, int>, ll> int_ans;
    
    ll init_tot = 0;
    for (int i = 0; i < n; i++) {
        init_tot += st.qry(i, nums[i]+1, n);
        st.upd(nums[i], 1);
    }

    cur_ans.insert(init_tot);
    int_ans[{0, n}] = init_tot;
    
    vector<ll> ans;
    for (int i = 0; i < n; i++) {
        ll pans = *cur_ans.begin();
        ans.push_back(pans);
        int to_rem = (int) (p_enc[i] ^ pans) - 1;
        auto [a, b] = *prev(int_ans.upper_bound({to_rem, INF}));
        auto inter = a;
        auto prev_total = b;
        int_ans.erase(inter);
        cur_ans.erase(cur_ans.find(prev_total));
        
        pair<int, int> inter1 = {inter.first, to_rem};
        pair<int, int> inter2 = {to_rem + 1, inter.second};

        auto total = prev_total;
        total -= st.qry(inter2.first, inter2.second, 0, nums[to_rem]);
        total -= st.qry(inter1.first, inter1.second, nums[to_rem]+1, n);
        
        ll left_total = 0;
        ll right_total = 0;
        if (sz(inter1) < sz(inter2)) {
            for (int j = inter1.first; j < inter1.second; j++) {
                total -= st.qry(inter2.first, inter2.second, 0, nums[j]);
                left_total += st.qry(j, inter1.second, 0, nums[j]);
            }
            
            right_total = total - left_total;
        } else {
            for (int j = inter2.first; j < inter2.second; j++) {
                total -= st.qry(inter1.first, inter1.second, nums[j]+1, n);
                right_total += st.qry(j, inter2.second, 0, nums[j]);
            }
            
            left_total = total - right_total;
        }

        if (sz(inter1) > 0) {
            int_ans[inter1] = left_total;
            cur_ans.insert(left_total);
        }
        
        if (sz(inter2) > 0) {
            int_ans[inter2] = right_total;
            cur_ans.insert(right_total);
        }
    }
    
    for (int i = 0; i < n; i++) {
        cout << ans[i];
        if (i < n - 1) {
            cout << ' ';
        } else {
            cout << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        solve();
    }
    
}

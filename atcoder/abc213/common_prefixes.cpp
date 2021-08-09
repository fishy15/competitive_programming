/*
 * For answering the sum for S_k, we note that this is equal to sum(LCP(S_i, S_k)) for all values of i. We 
 * also know that the LCP for S_SA_i to S_SA_j where SA is the suffix array and i < j is min(LCP_i, LCP_i+1,
 * ..., LCP_j-1). Therefore, we can maintain the sum of the LCP in the prefix of each position and the
 * suffix of each position, which we can do using a stack.
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

int n;
string s;
vector<int> sa, lcp;
vector<ll> ans;

vector<int> suffix_array(const string &s) {
    int n = s.size();
    vector<int> sa(n), c(n);
    for (int i = 0; i < n; i++) {
        sa[i] = n - i - 1;
        c[i] = s[i];
    }

    stable_sort(sa.begin(), sa.end(), [&s](int i, int j) { return s[i] < s[j]; });

    for (int len = 1; len < n; len *= 2) {
        vector<int> old_c(c), idx(n), old_sa(sa);
        iota(idx.begin(), idx.end(), 0);

        for (int i = 0; i < n; i++) {
            bool same = i > 0 && sa[i - 1] + len < n
                && old_c[sa[i - 1]] == old_c[sa[i]]
                && old_c[sa[i - 1] + len / 2] == old_c[sa[i] + len / 2];
            c[sa[i]] = same ? c[sa[i - 1]] : i;
        }

        for (int i = 0; i < n; i++) {
            int loc = old_sa[i] - len;
            if (loc >= 0) {
                sa[idx[c[loc]]++] = loc;
            }
        }
    }

    return sa;
}

vector<int> find_lcp(const string &s, const vector<int> &sa) {
    int n = s.size();
    vector<int> rank(n);
    for (int i = 0; i < n; i++) {
        rank[sa[i]] = i;
    }

    int len = 0;
    vector<int> lcp(n - 1);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            len = 0;
        } else {
            int j = sa[rank[i] + 1];
            while (max(i, j) + len < n && s[i + len] == s[j + len]) len++;
            lcp[rank[i]] = len;
            if (len > 0) len--;
        }
    }

    return lcp;
}

struct cnt_stack {
    ll cur_val;
    vector<pair<int, int>> st;

    cnt_stack() : cur_val(0) {}
    
    void min_by(int val) {
        int sz = st.size();
        while (sz >= 2 && st[sz - 2].first >= val) {
            cur_val += (ll) (st[sz - 2].first - st[sz - 1].first) * st[sz - 1].second;
            st[sz - 2].second += st[sz - 1].second;
            st.pop_back();
            sz--;
        }

        if (!st.empty() && st[sz - 1].first > val) {
            cur_val += (ll) (val - st[sz - 1].first) * st[sz - 1].second;
            st[sz - 1].first = val;
        }
    }

    void add_val(int val) {
        min_by(val);
        if (!st.empty() && st.back().first == val) {
            st.back().second++;
        } else {
            st.push_back({val, 1});
        }

        cur_val += val;
    }

    void clear() {
        st.clear();
        cur_val = 0;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    cin >> s;

    sa = suffix_array(s);
    lcp = find_lcp(s, sa);

    vector<ll> ans(n);

    cnt_stack st;
    for (int i = 0; i < n - 1; i++) {
        st.add_val(lcp[i]);
        ans[sa[i + 1]] += st.cur_val;
    }

    st.clear();
    for (int i = n - 2; i >= 0; i--) {
        st.add_val(lcp[i]);
        ans[sa[i]] += st.cur_val;
    }

    for (int i = 0; i < n; i++) {
        ans[i] += n - i;
        cout << ans[i] << '\n';
    }

    return 0;
}

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

struct segtree {
    int n;
    int st[4 * MAXN];
    void build(int v, int l, int r, const vector<int> &nums) {
        if (l == r) {
            st[v] = nums[l];
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m, nums);
            build(2 * v + 1, m + 1, r, nums);
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }
    void upd(int x, int y) { return upd(x, y, 1, 0, n - 1); }
    void upd(int x, int y, int v, int l, int r) {
        if (l == r) {
            st[v] = y;
        } else {
            int m = (l + r) / 2;
            if (x <= m) {
                upd(x, y, 2 * v, l, m);
            } else {
                upd(x, y, 2 * v + 1, m + 1, r);
            }
            st[v] = min(st[2 * v], st[2 * v + 1]);
        }
    }
    int qry(int x, int y) { return qry(x, y, 1, 0, n - 1); }
    int qry(int x, int y, int v, int l, int r) {
        if (r < x || l > y) return INF;
        if (x <= l && r <= y) return st[v];
        int m = (l + r) / 2;
        return min(qry(x, y, 2 * v, l, m), qry(x, y, 2 * v + 1, m + 1, r));
    }
};

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

int n;
vector<int> sa, lcp;
segtree st;

int cmp(int x, int y, int len) {
    if (x == y) return true;
    if (x > y) swap(x, y);

    // flipping
    int cx = n - x - 1;
    int cy = n - y - 1;

    auto [a, b] = minmax(cx, cy);
    if (st.qry(a, b - 1) >= len) {
        return 0;
    }

    return sa[x] > sa[y] ? -1 : 1;
}

// flipping first x vs flipping first y
int cmp(int x, int y) {
    int len = min(x, y);
    
    int c = cmp(x, y, len);
    if (c == -1) return x;
    if (c == 1) return y;

    len = max(x, y) - min(x, y);
    if (x < y) {

    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s; cin >> s;
    n = s.size();

    std::reverse(s.begin(), s.end());
    sa = suffix_array(s);
    lcp = find_lcp(s, sa);

    st.n = n - 1;
    st.build(1, 0, n - 2, lcp);

    int cur = 1;
    for (int i = 2; i < n - 1; i++) {
        cur = cmp(cur, i);
    }

    cout << cur << '\n';

    return 0;
}

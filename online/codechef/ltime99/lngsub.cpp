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

struct DSU {
    vector<int> dsu;
    vector<int> sz;

    DSU(int n) {
        dsu.resize(n);
        sz.resize(n);
        iota(dsu.begin(), dsu.end(), 0);
        fill(sz.begin(), sz.end(), 1); 
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            dsu[y] = x;
            sz[x] += sz[y];
        }
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

void solve() {
    int n; cin >> n;
    vector<string> ss(n);
    string tot;
    vector<int> sz;

    for (int i = 0; i < n; i++) {
        cin >> ss[i];
        if (!tot.empty()) tot += '$';
        tot += ss[i];
        sz.push_back(ss[i].size());
    }

    for (int i = 1; i < n; i++) {
        sz[i] += sz[i - 1] + 1;
    }

    vector<int> sa = suffix_array(tot);
    vector<int> lcp = find_lcp(tot, sa);

    auto get_comp = [&](int x) { return upper_bound(sz.begin(), sz.end(), x) - sz.begin(); };

    vector<array<int, 3>> edges;
    for (int i = 0; i < sz[n - 1] - 1; i++) {
        if (tot[sa[i]] == '$') continue;
        int a = get_comp(sa[i]);
        int b = get_comp(sa[i + 1]);

        if (a != b) {
            int w = min({lcp[i], sz[a] - sa[i], sz[b] - sa[i + 1]});
            edges.push_back({w, a, b});
        }
    }

    sort(edges.rbegin(), edges.rend());

    DSU dsu(n);
    ll ans = 0;
    for (auto [w, a, b] : edges) {
        if (dsu.find(a) != dsu.find(b)) {
            dsu.join(a, b);
            ans += w;
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

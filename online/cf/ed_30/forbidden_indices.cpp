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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

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

struct DSU {
    vector<int> dsu;
    vector<int> size;
    vector<int> ok_cnt;
    int max_ok;

    DSU(int n) : dsu(n), size(n, 1), ok_cnt(n), max_ok{} {
        iota(all(dsu), 0);
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (size[x] < size[y]) swap(x, y);
            dsu[y] = x;
            size[x] += size[y];
            ok_cnt[x] += ok_cnt[y];
            max_ok = max(max_ok, ok_cnt[x]);
        }
    }

    void add(int x) {
        x = find(x);
        ok_cnt[x]++;
        max_ok = max(max_ok, ok_cnt[x]);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    string s;
    cin >> s;

    string ok;
    cin >> ok;

    reverse(all(s));
    reverse(all(ok));

    auto sa = suffix_array(s);
    auto lcp = find_lcp(s, sa);

    DSU dsu(n);
    vector<vector<pair<int, int>>> events(n + 1);
    rep(i, 0, n-1) {
        events[lcp[i]].push_back({sa[i], sa[i+1]});
    }

    ll ans = 0;
    for (int i = n; i >= 0; i--) {
        if (i > 0) {
            // enable the string with length i
            auto idx = n - i;
            if (ok[idx] == '0') {
                dsu.add(idx);
            }
        }

        for (auto [x, y] : events[i]) {
            dsu.join(x, y);
        }
        ans = max(ans, (ll) dsu.max_ok * i);
    }

    cout << ans << '\n';

    return 0;
}

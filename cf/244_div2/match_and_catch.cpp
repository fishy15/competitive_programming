/*
 * We can create the suffix array for s1$s2. If there is a unique common substring between the two strings,
 * they have to be next to each other in the suffix array. We can also use the LCP array to compare on both
 * sides to see if the common substring is longer than adjacent common substrings (which would mean that it
 * is not unique in each string).
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

int n, m;
string s1, s2;
string tot;
vector<int> sa, lcp;

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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s1 >> s2;
    n = s1.size();
    m = s2.size();

    tot = s1 + "$" + s2;

    sa = suffix_array(tot);
    lcp = find_lcp(tot, sa);

    int ans = INF;
    for (int i = 0; i < n + m; i++) {
        auto [lo, hi] = minmax(sa[i], sa[i + 1]);
        if (lo < n && hi > n) {
            int prev = i == 0 ? 0 : lcp[i - 1];
            int cur = lcp[i];
            int nxt = i == n + m - 1 ? 0 : lcp[i + 1];
            
            if (max(prev, nxt) < cur) {
                ans = min(ans, max(prev, nxt) + 1);
            }
        }
    }

    if (ans == INF) ans = -1;
    cout << ans << '\n';

    return 0;
}

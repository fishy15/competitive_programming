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

void solve(const string &s, int m) {
    int n = s.size();
    if (m > n) {
        cout << "none\n";
        return;
    } else if (m == 1) {
        cout << n << ' ' << 0 << '\n';
        return;
    }

    auto sa = suffix_array(s);
    auto lcp = find_lcp(s, sa);

    set<int> starts;
    multiset<int> comm;
    pair<int, int> ans{};

    for (int i = 0; i < m; i++) {
        starts.insert(sa[i]);
        if (i < m - 1) comm.insert(lcp[i]);
    }

    ans = {*comm.begin(), *starts.rbegin()}; 
    
    for (int i = m; i < n; i++) {
        starts.erase(sa[i - m]);
        comm.erase(comm.find(lcp[i - m]));
        starts.insert(sa[i]);
        comm.insert(lcp[i - 1]);

        pair<int, int> cur = {*comm.begin(), *starts.rbegin()};
        if (ans.first == cur.first) {
            ans.second = max(ans.second, cur.second);
        } else if (ans.first < cur.first) {
            ans = cur;
        }
    }

    if (ans.first == 0) {
        cout << "none\n";
    } else {
        cout << ans.first << ' ' << ans.second << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    while (true) {
        int m; cin >> m;
        if (m == 0) break;
        string s; cin >> s;
        solve(s, m);
    }

    return 0;
}

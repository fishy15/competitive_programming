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

template<typename T>
T &ckmax(T &a, T b) {
    return a = max(a, b);
}

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

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

    int n; cin >> n;
    vector<string> words(n);

    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }

    string tot;
    vector<int> begin;
    vector<int> end;

    for (string s : words) {
        begin.push_back(tot.size());
        tot += s;
        end.push_back(tot.size());
        tot += "$";
    }

    auto sa = suffix_array(tot);
    auto lcp = find_lcp(tot, sa);

    auto get_begin = [&](int idx) -> int {
        auto it = lower_bound(begin.begin(), begin.end(), idx);
        if (it != begin.end() && *it == idx) {
            return it - begin.begin();
        }

        return -1;
    };

    auto get_idx = [&](int idx) -> int {
        if (tot[idx] == '$') return -1;
        auto low = upper_bound(begin.begin(), begin.end(), idx) - 1;
        return low - begin.begin();
    };

    auto len = [&](int idx) -> {
        return end[idx] - begin[idx];
    };

    vector<vector<int>> dist(n, vector<int>(n, -1));

    int cur_b = -1;
    int cur_lcp = INF;
    for (int i = 0; i < (int) sa.size(); i++) {
        cout << tot.substr(sa[i], tot.size() - sa[i]) << '\n';
        int bb = get_begin(sa[i]);
        if (bb != -1) {
            cur_b = bb;
            cur_lcp = INF;
        } else {
            if (cur_b == -1) continue;

            int other = get_idx(sa[i]);
            ckmin(cur_lcp, lcp[i - 1]);
            if (other != -1 && cur_lcp > 0) ckmax(dist[other][cur_b], min({cur_lcp);
            cout << other << ' ' << cur_b << ' ' << cur_lcp << '\n';
        }
    }

    cur_b = -1;
    cur_lcp = INF;
    for (int i = (int) sa.size() - 1; i >= 0; i--) {
        cout << tot.substr(sa[i], tot.size() - sa[i]) << '\n';
        int bb = get_begin(sa[i]);
        if (bb != -1) {
            cur_b = bb;
            cur_lcp = INF;
        } else {
            if (cur_b == -1) continue;

            int other = get_idx(sa[i]);
            ckmin(cur_lcp, lcp[i]);
            if (other != -1 && cur_lcp > 0) ckmax(dist[cur_b][other], cur_lcp);
            cout << other << ' ' << cur_b << ' ' << cur_lcp << '\n';
        }
    }

    for (int i = 0; i < n; i++) {
        dist[i][i] = -1;

        for (int j = 0; j < n; j++) {
            cout << dist[i][j] << ' ';
        }
        cout << '\n';
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != -1 && dist[k][j] != -1) {
                    ckmax(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
        if (dist[i][i] != -1) {
            cout << "Shakespeare, who?\n";
            return 0;
        }

        for (int j = 0; j < n; j++) {
            ckmax(ans, dist[i][j]);
        }
    }

    cout << ans << '\n';

    return 0;
}

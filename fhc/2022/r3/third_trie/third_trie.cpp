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

template<int SZ>
struct aho_corasick {
    struct node {
        array<int, SZ> next;
        int depth, link, cnt, leafcnt;
        bool is_first;
        node() : depth(0), link(-1), cnt(0), leafcnt(0), is_first(false) { next.fill(0); }
    };
    vector<node> trie;
    aho_corasick() : trie(1) {}
    aho_corasick(const vector<string> &v) : aho_corasick() {
        for (auto s : v) insert(s);
        build();
    }
    void clear() { trie = vector<node>(1); }
    int conv(int c) { return c - 'a'; }
    int insert(const string &s) {
        int v = 0;
        trie[0].cnt++;
        for (auto ch : s) {
            int c = conv(ch);
            if (!trie[v].next[c]) {
                trie[v].next[c] = trie.size();
                trie.emplace_back();
                trie.back().depth = trie[v].depth + 1;
            }
            v = trie[v].next[c];
            trie[v].cnt++;
        }
        trie[v].leafcnt++;
        return v;
    }
    int get_next(int v, int c) {
        return trie[v].next[conv(c)];
    }
    void build() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int c = 0; c < SZ; c++) {
                if (trie[v].next[c]) {
                    int e = trie[v].next[c];
                    trie[e].link = 0; // not like normal aho-corasick, just acting like a trie
                    q.push(e);
                }
            }
            if (v != 0) {
                for (int c = 0; c < SZ; c++) {
                    if (!trie[v].next[c]) {
                        trie[v].next[c] = trie[trie[v].link].next[c];
                    }
                }
            }
        }
        for (int i = 0; i < SZ; i++) {
            if (trie[0].next[i] > 0) {
                trie[trie[0].next[i]].is_first = true;
            }
        }
    }
};

template<typename F>
struct y_combinator_result {
    F f;
    template<typename T> explicit y_combinator_result(T &&f) : f(forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(forward<F>(f));
}

void solve() {
    int n;
    cin >> n;

    vector<array<pair<int, ll>, 26>> overall;

    auto new_node = [&] {
        int idx = overall.size();
        overall.emplace_back();

        auto &last = overall.back();
        fill(last.begin(), last.end(), pair<int, ll>{-1, 0});
        return idx;
    };

    new_node();

    auto insert = y_combinator([&](auto self, auto &trie, int v1, int v2) -> void {
        for (auto [n, c] : trie[v2]) {
            auto &cur = overall[v1][c - 'a'];
            if (cur.first == -1) {
                cur.first = new_node();
            }

            cur.second++;
            self(trie, cur.first, n);
        }
    });

    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        vector<vector<pair<int, char>>> trie(m + 1);

        for (int i = 0; i < m; i++) {
            int p;
            char c;
            cin >> p >> c;
            p--;
            trie[p].push_back({i, c});
        }

        insert(trie, 0, 0);
        cout << "inserted " << i << endl;
    }

    auto choose = [](ll n, ll k) -> ll {
        ll res = 1;
        for (int i = 0; i < k; i++) {
            res *= n - i;
        }
        for (int i = 0; i < k; i++) {
            res /= i + 1;
        }
        return res;
    };

    ll ans = 0;
    auto dfs = y_combinator([&](auto self, int v) -> void {
        for (int i = 0; i < 26; i++) {
            auto &cur = overall[v][i];
            if (cur.first != -1) {
                int has = cur.second;
                int doesnt = n - has;

                ans += choose(has, 3);
                ans += choose(has, 2) * choose(doesnt, 1);
                ans += choose(has, 1) * choose(doesnt, 2);

                self(cur.first);
            }
        }
    });

    dfs(0);

    ans += choose(n, 3);
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

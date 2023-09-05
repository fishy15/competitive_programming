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
#include <cassert>

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
        int depth, link, exit_link, cnt, leafcnt;
        ll gain;
        node() : depth(0), link(-1), exit_link(-1), cnt(0), leafcnt(0), gain(0) { next.fill(0); }
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
                    int link = trie[e].link = trie[v].link == -1 ? 0 : trie[trie[v].link].next[c]; 
                    trie[e].gain += trie[link].gain;
                    trie[e].exit_link = trie[link].leafcnt ? link : trie[link].exit_link;
                    q.push(e);
                }
            }
            if (v) {
                for (int c = 0; c < SZ; c++) {
                    if (!trie[v].next[c]) {
                        trie[v].next[c] = trie[trie[v].link].next[c];
                    }
                }
            }
        }
    }
};

template<typename T>
T &ckmax(T &a, T b) {
    return a = max(a, b);
}

struct M {
    const static int n = 201;
    ll m[n][n]; 
    M() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                m[i][j] = -1;
            }
        }
    }
    M operator*(const M &m2) {
        M res;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int a = 0; a < n; a++) {
                    if (m[i][a] != -1 && m2[a][j] != -1) {
                        ckmax(res[i][j], m[i][a] + m2[a][j]);
                    }
                }
            }
        }
        return res;
    }
    ll *operator[](const int x) { return m[x]; }
    const ll *operator[](const int x) const { return m[x]; }
    static M pow(M m, ll e) {
        M res = I();
        while (e > 0) {
            if (e & 1) res = res * m;
            m = m * m;
            e >>= 1;
        }
        return res;
    }
    static M I() {
        M m;
        for (int i = 0; i < n; i++) m[i][i] = 0;
        return m;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    ll l;
    cin >> n >> l;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    aho_corasick<26> trie;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        auto end_loc = trie.insert(s);
        trie.trie[end_loc].gain += a[i];
    }

    trie.build();

    M mat;
    for (int i = 0; i < (int) trie.trie.size(); i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            auto nxt = trie.get_next(i, c);
            mat[i][nxt] = trie.trie[nxt].gain;
        }
    }

    auto res = M::pow(mat, l);
    ll ans = 0;
    for (int e = 0; e < (int) trie.trie.size(); e++) {
        ckmax(ans, res[0][e]);
    }
    cout << ans << '\n';

    return 0;
}

/*
 * We can insert all of the strings of the set into a trie and then conduct 0-1 BFS, where each node has 
 * is defined by the index in the string and the node in the trie that it represents. Two nodes are
 * connected by a directed edge of weight 0 if the first leads to the next in the trie and the string index
 * is incremented if it had just been covered by the character in the trie. Two nodes are connected by
 * an edge of weight 1 if it takes us back to the beginning of the trie. The shortest point that gets us
 * through the string gives us the answer.
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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 2510

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

// dist[idx in string][idx in trie]
int dist[MAXN][MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<string> strs(n);
    string tot;

    for (int i = 0; i < n; i++) {
        cin >> strs[i];
    }

    cin >> tot;

    aho_corasick<26> ac(strs);

    for (int i = 0; i <= (int)(tot.size()); i++) {
        for (int j = 0; j <= (int)(ac.trie.size()); j++) {
            dist[i][j] = INF;
        }
    }

    deque<array<int, 3>> dq;
    dq.push_back({0, 0, 0});

    while (!dq.empty()) {
        auto [si, ti, d] = dq.front();
        dq.pop_front();
        if (dist[si][ti] != INF) continue;
        dist[si][ti] = d;

        if (si == (int)(tot.size())) {
            cout << d << '\n';
            return 0;
        }

        for (int i = 0; i < 26; i++) {
            int nxt_si = si;
            if ('a' + i == tot[si]) nxt_si++;
            int nxt_ti = ac.trie[ti].next[i];
            if (dist[nxt_si][nxt_ti] != INF || nxt_ti == 0) continue;

            if (ac.trie[nxt_ti].is_first) {
                dq.push_back({nxt_si, nxt_ti, d + 1});
            } else {
                dq.push_front({nxt_si, nxt_ti, d});
            }
        }
    }

    cout << "-1\n";

    return 0;
}

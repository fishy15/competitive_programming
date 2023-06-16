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
#define MAXN 500010

using namespace std;

template<int SZ>
struct aho_corasick {
    struct node {
        array<int, SZ> next;
        int depth, link, exit_link, cnt, leafcnt, end;
        node() : depth(0), link(-1), exit_link(-1), cnt(0), leafcnt(0), end(-1) { next.fill(0); }
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

string s;
aho_corasick<26> aho;
int n;
int p[MAXN];
int ans[MAXN];
int sz[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s;
    cin >> n;

    memset(p, -1, sizeof p);
    memset(ans, -1, sizeof ans);
    for (int i = 1; i <= n; i++) {
        string q; cin >> q;
        int loc = aho.insert(q);
        if (aho.trie[loc].end == -1) {
            aho.trie[loc].end = i;
            p[i] = i;
        } else {
            p[i] = aho.trie[loc].end;
        }
        sz[i] = q.size();
    }

    aho.build();

    int v = 0;
    for (int i = 0; i < (int)(s.size()); i++) {
        char c = s[i];
        v = aho.get_next(v, c);
        int cur = v;
        while (cur != -1) {
            if (aho.trie[cur].leafcnt && ans[aho.trie[cur].end] == -1) {
                ans[aho.trie[cur].end] = i + 1;
            }
            cur = aho.trie[cur].exit_link;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (ans[p[i]] != -1) {
            cout << ans[p[i]] - sz[i] + 1 << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}

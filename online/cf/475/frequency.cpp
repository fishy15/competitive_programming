/*
 * We are given that each query has a distinct string for a query. For each given length of a substring, there
 * are at max O(n) matches, and there are O(sqrt(n)) possible distinct lengths, so there are O(n sqrt(n)) 
 * matches. Using Aho-Corasick, we can find all of the matches for each query string, and then we can loop
 * over the matches to find the minimum length needed.
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
#include <random>
#include <chrono>
#include <unordered_map>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100010

using namespace std;

template<int SZ>
struct aho_corasick {
    struct node {
        array<int, SZ> next;
        int depth, link, exit_link, cnt, leafcnt;
        node() : depth(0), link(-1), exit_link(-1), cnt(0), leafcnt(0) { next.fill(0); }
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

struct qry {
    int k;
    string s;
    int pos;
};

string s;
int n, sz;
int ans[MAXN];
qry qq[MAXN];
aho_corasick<26> ac;
vector<int> match[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s;
    sz = s.size();
    cin >> n;

    for (int i = 0; i < n; i++) {
        qry q;
        cin >> q.k >> q.s;
        q.pos = ac.insert(q.s);
        qq[i] = q;
    }

    ac.build();

    int v = 0;
    for (int i = 0; i < sz; i++) {
        v = ac.get_next(v, s[i]);
        int cur = v;
        while (cur != -1) {
            if (ac.trie[cur].leafcnt) {
                match[cur].push_back(i);
            }
            cur = ac.trie[cur].exit_link;
        }
    }

    for (int i = 0; i < n; i++) {
        auto &q = qq[i];
        auto &v = match[q.pos];
        sort(v.begin(), v.end());
        if ((int)v.size() < q.k) {
            cout << "-1\n";
        } else {
            int ans = INF;
            for (int i = 0; i < (int)v.size() - q.k + 1; i++) {
                ans = min(ans, v[i + q.k - 1] - v[i]);
            }
            cout << ans + q.s.size() << '\n';
        }
    }

    return 0;
}

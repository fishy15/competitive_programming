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
        vector<int> end;
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

string s;
aho_corasick<26> aho;
int n;
map<int, vector<int>> qry;
bool ans[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string q; cin >> q;
        int loc = aho.insert(q);
        aho.trie[loc].end.push_back(i);
    }

    aho.build();

    int v = 0;
    for (char c : s) {
        v = aho.get_next(v, c);
        int cur = v;
        while (cur != -1) {
            for (int x : aho.trie[cur].end) {
                ans[x] = true;
            }
            aho.trie[cur].end.clear();
            cur = aho.trie[cur].exit_link;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << (ans[i] ? "YES\n" : "NO\n");
    }

    return 0;
}

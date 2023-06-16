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
        int depth, link, exit_link, cnt, leafcnt;
        vector<int> leaf_idx;
        node() : depth(0), link(-1), exit_link(-1), cnt(0), leafcnt(0) { next.fill(0); }
    };
    vector<node> trie;
    aho_corasick() : trie(1) {}
    void clear() { trie = vector<node>(1); }
    int conv(int c) { 
        return c - 32;
    }
    int insert(const string &s, int idx) {
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
        trie[v].leaf_idx.push_back(idx);
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

using aho = aho_corasick<96>;

void solve() {
    int n; cin >> n;
    aho ac; 
    vector<string> strs(n);
    vector<vector<int>> loc(n);

    // read in extra newline
    string trash; 
    getline(cin, trash);

    for (int i = 0; i < n; i++) {
        getline(cin, strs[i]);
        ac.insert(strs[i], i);
    }

    ac.build();
    int ptr = 0;

    string text;
    getline(cin, text);
    for (int i = 0; i < (int) text.size(); i++) {
        char c = text[i];
        ptr = ac.get_next(ptr, c);

        int end_ptr = ptr;
        while (end_ptr > 0) {
            for (int x : ac.trie[end_ptr].leaf_idx) {
                loc[x].push_back(i);
            }
            end_ptr = ac.trie[end_ptr].exit_link;
        }
    }

    for (int i = 0; i < n; i++) {
        int sz = strs[i].size();
        for (int j : loc[i]) {
            cout << j - sz + 1 << ' ';
        }
        cout << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    while (cin) {
        solve();
    }

    return 0;
}

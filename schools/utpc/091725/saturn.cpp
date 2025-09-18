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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

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

using aho = aho_corasick<26>;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string t;
    cin >> t;

    aho ac;
    ac.insert(t);
    ac.build();

    int n;
    cin >> n;

    vector<int> best(sz(t)+1, -INF);
    best[0] = 0;

    rep(i, 0, n) {
        string s;
        cin >> s;

        // if we feed in positions 0..t+1
        vector<pair<int, int>> gain(sz(t)+1);
        rep(st, 0, sz(t)+1) {
            int cur = st;
            for (auto c : s) {
                cur = ac.get_next(cur, c);
                if (cur == sz(t)) {
                    gain[st].first++;
                }
            }
            gain[st].second = cur;
        }

        auto nxt = best;
        rep(st, 0, sz(t)+1) {
            auto val = best[st] + gain[st].first;
            auto end = gain[st].second;
            nxt[end] = max(nxt[end], val);
        }

        best = nxt;
    }

    cout << *max_element(all(best)) << '\n';

    return 0;
}

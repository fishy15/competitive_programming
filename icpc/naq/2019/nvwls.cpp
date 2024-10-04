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

bool vowel(char c) {
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

bool skip(char c) {
    return vowel(c) || c == ' ';
}

template<typename T>
T &ckmax(T &a, T b) {
    return a = max(a, b);
}

template<int SZ>
struct aho_corasick {
    struct node {
        array<int, SZ> next;
        int depth, link, exit_link;
        pair<int, int> value;
        node() : depth(0), link(-1), exit_link(-1), value{-1, -1} { next.fill(0); }
    };
    vector<node> trie;
    aho_corasick() : trie(1) {}
    aho_corasick(const vector<string> &v) : aho_corasick() {
        for (auto s : v) insert(s);
        build();
    }
    void clear() { trie = vector<node>(1); }
    int conv(int c) { 
        int idx = c - 'A';
        idx -= c > 'A';
        idx -= c > 'E';
        idx -= c > 'I';
        idx -= c > 'O';
        idx -= c > 'U';
        return idx;
    }
    int insert(const string &s, int idx) {
        int v = 0;
        int value = count_if(all(s), &vowel);
        for (auto ch : s) {
            if (skip(ch)) continue;
            int c = conv(ch);
            if (!trie[v].next[c]) {
                trie[v].next[c] = trie.size();
                trie.emplace_back();
                trie.back().depth = trie[v].depth + 1;
            }
            v = trie[v].next[c];
        }
        ckmax(trie[v].value, {value, idx});
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
                    trie[e].exit_link = trie[link].value.first != -1 ? link : trie[link].exit_link;
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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    aho_corasick<21> aho;
    vector<string> words;
    rep(i, 0, n) {
        string s;
        cin >> s;
        aho.insert(s, i);
        words.push_back(s);
    }

    aho.build();

    string goal;
    cin >> goal;

    vector<array<int, 3>> dp(sz(goal) + 1, {-1, -1, -1});
    dp[0] = {0, 0, 0};

    int v = 0;
    rep(i, 0, sz(goal)) {
        auto c = goal[i];
        v = aho.get_next(v, c);

        int cur = v;
        while (cur != -1) {
            auto len = aho.trie[cur].depth;
            auto [value, word_idx] = aho.trie[cur].value;
            if (dp[i+1-len][0] != -1) {
                auto new_value = dp[i+1-len][0] + value;
                if (new_value > dp[i+1][0] && value != -1) {
                    dp[i+1][0] = new_value;
                    dp[i+1][1] = len;
                    dp[i+1][2] = word_idx;
                }
            }
            cur = aho.trie[cur].exit_link;
        }
    }

    vector<int> sentence;
    int cur = sz(goal);
    while (cur > 0) {
        auto [_, len, idx] = dp[cur];
        cur -= len;
        sentence.push_back(idx);
    }

    reverse(all(sentence));
    for (auto x : sentence) {
        cout << words[x] << ' ';
    }
    cout << '\n';

    return 0;
}


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
struct trie {
    struct node {
        array<int, SZ> next;
        node() { next.fill(0); }
    };
    vector<node> t;
    trie() : t(1) {}
    int conv(int c) { return c - 'a'; }
    int insert(const string &s) {
        int v = 0;
        for (auto ch : s) {
            int c = conv(ch);
            if (!t[v].next[c]) {
                t[v].next[c] = t.size();
                t.emplace_back();
            }
            v = t[v].next[c];
        }
        return v;
    }
    int get_next(int v, int c) {
        return t[v].next[conv(c)];
    }
    bool in(const string &s) {
        int v = 0;
        for (char c : s) {
            v = get_next(v, c);
            if (v == 0) return false;
        }
        return true;
    }
};

using tr = trie<26>;
tr cur[2];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int q; cin >> q;

    int x = 0;
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            string s; cin >> s;
            cur[x].insert(s);
            reverse(s.begin(), s.end());
            cur[1 - x].insert(s);
        } else if (t == 2) {
            string s; cin >> s;
            cout << cur[x].in(s) << '\n';
        } else {
            x = 1 - x;
        }
    }

    return 0;
}

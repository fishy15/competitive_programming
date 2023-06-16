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

struct trie {
    struct node {
        int cnt, depth;
        array<int, 26> nxt;   
        node(int depth) : cnt(0), depth(depth) { nxt.fill(-1); }
    };

    vector<node> nodes;
    int root;

    trie() {
        root = alloc(0);
    }

    int alloc(int depth) {
        auto sz = nodes.size();
        nodes.emplace_back(depth);
        return sz;
    }

    int insert(const string &s) {
        int v = root;
        for (char c : s) {
            nodes[v].cnt++;
            if (nodes[v].nxt[c - 'a'] == -1) {
                nodes[v].nxt[c - 'a'] = alloc(nodes[v].depth + 1);
            }
            v = nodes[v].nxt[c - 'a'];
        }

        nodes[v].cnt++;
        return v;
    }

    int get_max_common(const string &s) const {
        int v = root;
        int ans = nodes[v].depth;
        for (char c : s) {
            auto &cur = nodes[v];
            v = cur.nxt[c - 'a'];
            if (nodes[v].cnt < 2) {
                break;
            } else {
                ans = nodes[v].depth;
            }
        }
        return ans;
    }

};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<string> s(n);
    trie t;

    for (int i = 0; i < n; i++) {
        cin >> s[i];
        t.insert(s[i]);
    }

    for (int i = 0; i < n; i++) {
        cout << t.get_max_common(s[i]) << '\n';
    }

    return 0;
}

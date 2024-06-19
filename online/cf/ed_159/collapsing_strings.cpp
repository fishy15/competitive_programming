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
    map<pair<int, int>, int> nxt;
    struct node {
        int cnt_front, cnt_back;
        node() : cnt_front(0), cnt_back() {}
    };

    vector<node> nodes;
    int root;

    trie() {
        root = alloc();
    }

    int alloc() {
        auto sz = nodes.size();
        nodes.emplace_back();
        return sz;
    }

    int insert(const string &s, bool front) {
        int v = root;
        auto inc = [&] {
            if (front) {
                nodes[v].cnt_front++;
            } else {
                nodes[v].cnt_back++;
            }
        };

        for (char c : s) {
            inc();
            int cc = c - 'a';
            auto it = nxt.find({v, cc});
            if (it == nxt.end()) {
                v = nxt[{v, cc}] = alloc();
            } else {
                v = it->second;
            }
        }

        inc();
        return v;
    }

    ll get_common() {
        ll total = 0;
        for (int i = 1; i < (int) nodes.size(); i++) {
            auto n = nodes[i];
            total += (ll) n.cnt_front * n.cnt_back;
        }
        return total;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    int total_len = 0;
    trie t;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        auto rev = s;
        reverse(rev.begin(), rev.end());

        total_len += s.size();
        t.insert(s, true);
        t.insert(rev, false);
    }

    ll ans = 2LL * n * total_len;
    ans -= 2 * t.get_common();

    cout << ans << '\n';

    return 0;
}

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

template<typename F>
struct y_combinator_result {
    F f;
    template<typename T> explicit y_combinator_result(T &&f) : f(std::forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), std::forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(std::forward<F>(f));
}

struct suffix_automaton {
    struct node {
        int len;
        int link;
        ll cnt;
        ll cnt_below;
        array<int, 26> nxt;
        node() : len{0}, link{-1}, cnt{1}, cnt_below{} {
            nxt.fill(-1);
        }
    };

    int root;
    int last;

    suffix_automaton() {
        root = last = new_node();
        buf[root].cnt = 0;
    }

    suffix_automaton(const string &s) : suffix_automaton{} {
        for (auto c : s) {
            add_char(c);
        }
        compute_counts();
    }

    void add_char(char nxt_char) {
        auto c = nxt_char - 'a';
        auto cur = new_node();
        buf[cur].len = buf[last].len + 1;

        auto p = last;
        while (p != -1 && buf[p].nxt[c] == -1) {
            buf[p].nxt[c] = cur;
            p = buf[p].link;
        }

        if (p == -1) {
            buf[cur].link = 0;
        } else {
            auto q = buf[p].nxt[c];
            if (buf[p].len + 1 == buf[q].len) {
                buf[cur].link = q;
            } else {
                auto clone = new_node(buf[q]);
                buf[clone].len = buf[p].len + 1;
                buf[clone].cnt = 0;
                while (p != -1 && buf[p].nxt[c] == q) {
                    buf[p].nxt[c] = clone;
                    p = buf[p].link;
                }
                buf[q].link = buf[cur].link = clone;
            }
        }
        
        last = cur;
    }

    void compute_counts() {
        vector<int> idx(buf.size());
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [this](int i, int j) { return buf[i].len > buf[j].len; });
        for (auto i : idx) {
            if (buf[i].link != -1) {
                buf[buf[i].link].cnt += buf[i].cnt;
            }
        }

        // dont care about empty string
        buf[root].cnt = 0;

        vector<bool> vis(buf.size());;
        auto dfs = y_combinator([&](auto self, int v) -> ll {
            if (!vis[v]) {
                vis[v] = true;
                buf[v].cnt_below = buf[v].cnt;
                for (auto n : buf[v].nxt) {
                    if (n != -1) {
                        buf[v].cnt_below += self(n);
                    }
                }
            }
            return buf[v].cnt_below;
        });
        dfs(root);
    }

    vector<node> buf;
    template<typename ...Args>
    int new_node(Args ...args) {
        buf.emplace_back(args...);
        return buf.size() - 1;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s;
    cin >> s;

    ll k;
    cin >> k;
    k--;

    auto sa = suffix_automaton(s);

    auto cur = sa.root;
    string res;
    while (true) {
        if (k < sa.buf[cur].cnt) {
            cout << res << '\n';
            return 0;
        } else {
            k -= sa.buf[cur].cnt;
            for (int i = 0; i < 26; i++) {
                auto nxt = sa.buf[cur].nxt[i];
                if (nxt != -1) {
                    auto cnt = sa.buf[nxt].cnt_below;
                    if (k < cnt) {
                        // continue on the next iteration
                        res += (char) ('a' + i);
                        cur = nxt;
                        break;
                    } else {
                        k -= cnt;
                    }
                }
            }
        }
    }
    
    return 0;
}

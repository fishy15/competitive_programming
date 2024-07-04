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

struct cmp {
    bool operator()(pair<int, bool> a, pair<int, bool> b) {
        return a.first + (a.second ? 2 : 0) > b.first + (b.second ? 2 : 0);
    }
};

using min_pq = priority_queue<pair<int, bool>, vector<pair<int, bool>>, cmp>;

void merge_into(min_pq &q1, min_pq &q2) {
    if (sz(q1) < sz(q2)) swap(q1, q2);
    while (!q2.empty()) {
        q1.push(q2.top());
        q2.pop();
    }
}

struct trie {
    struct node {
        array<node *, 2> child;
        int depth;
        int count;
        node(int d) : child{nullptr, nullptr}, depth{d}, count{} {}

        bool leaf() const {
            return child[0] == nullptr && child[1] == nullptr;
        }

        pair<min_pq, ll> solve() {
            min_pq pq;
            ll total = 0;

            if (leaf()) {
                pq.push({depth, false});
            } else {
                if (child[0] != nullptr) {
                    auto [lq, lcnt] = child[0]->solve();
                    merge_into(pq, lq);
                    total += lcnt;
                } else {
                    pq.push({depth + 1, false});
                }

                if (child[1] != nullptr) {
                    auto [rq, rcnt] = child[1]->solve();
                    merge_into(pq, rq);
                    total += rcnt;
                } else {
                    pq.push({depth + 1, false});
                }
            }

            rep(_, 0, count) {
                auto [v, occ] = pq.top();
                pq.pop();

                if (occ) {
                    total += v + 2;
                    pq.push({v + 1, true});
                    pq.push({v + 1, true});
                } else {
                    total += v;
                    pq.push({v, true});
                }
            }

            return {std::move(pq), total};
        }
    };

    node *root;
    trie() {
        root = new node(0);
    }

    void add(string s) {
        auto cur = root;
        rep(i, 0, sz(s)) {
            auto c = s[i] - '0';
            if (cur->child[c] == nullptr) {
                cur->child[c] = new node(i + 1);
            }
            cur = cur->child[c];
        }
        cur->count++;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    trie t;
    ll total_len = 0;
    rep(i, 0, n) {
        string s;
        cin >> s;
        t.add(s);
        total_len += sz(s);
    }

    cout << t.root->solve().second - total_len << '\n';

    return 0;
}

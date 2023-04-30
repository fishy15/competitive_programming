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

struct Node {
    Node *l = 0, *r = 0;
    int val, y, c = 1;
    ll sum;
    Node(int val) : val(val), y(rand()), sum(val) {}
    void recalc();
};

int cnt(Node* n) { return n ? n->c : 0; }
ll sum(Node *n) { return n ? n->sum : 0; }
void Node::recalc() { 
    c = cnt(l) + cnt(r) + 1;
    sum = ::sum(l) + ::sum(r) + val;
}

template<class F> void each(Node* n, F f) {
    if (n) { each(n->l, f); f(n->val); each(n->r, f); }
}

pair<Node*, Node*> split(Node* n, int k) {
    if (!n) return {};
    if (cnt(n->l) >= k) {
        auto pa = split(n->l, k);
        n->l = pa.second;
        n->recalc();
        return {pa.first, n};
    } else {
        auto pa = split(n->r, k - cnt(n->l) - 1);
        n->r = pa.first;
        n->recalc();
        return {n, pa.second};
    }
}

Node* merge(Node* l, Node* r) {
    if (!l) return r;
    if (!r) return l;
    if (l->y > r->y) {
        l->r = merge(l->r, r);
        l->recalc();
        return l;
    } else {
        r->l = merge(l, r->l);
        r->recalc();
        return r;
    }
}

void ins(Node *&t, Node* n, int pos) {
    auto pa = split(t, pos);
    t = merge(merge(pa.first, n), pa.second);
}

int lower_bound(Node *n, int val) {
    if (!n) return 0;
    if (val <= n->val) {
        return lower_bound(n->l, val);
    } else {
        return 1 + cnt(n->l) + lower_bound(n->r, val);
    }
}

int upper_bound(Node *n, int val) {
    if (!n) return 0;
    if (val < n->val) {
        return upper_bound(n->l, val);
    } else {
        return 1 + cnt(n->l) + upper_bound(n->r, val);
    }
}

template<int N>
struct piles {
    Node *overall = 0;
    array<Node *, N> trees{};

    void insert(int val) {
        array<Node *, N> tmp{};

        auto overall_idx = lower_bound(overall, val);
        ins(overall, new Node(val), overall_idx);

        for (int i = 0; i < N; i++) {
            auto split_idx = lower_bound(trees[i], val);
            auto [left, right] = split(trees[i], split_idx);
            trees[i] = left;
            tmp[i] = right;
        }

        ins(trees[overall_idx % N], new Node(val), overall_idx / N);

        for (int i = 0; i < N; i++) {
            trees[i] = merge(trees[i], tmp[(i - 1 + N) % N]);
        }
    }

    void remove(int val) {
        array<Node *, N> tmp{};

        auto overall_idx = lower_bound(overall, val);
        auto [left_overall, right_overall] = split(overall, overall_idx);
        right_overall = split(right_overall, 1).second;
        overall = merge(left_overall, right_overall);

        for (int i = 0; i < N; i++) {
            auto split_idx = lower_bound(trees[i], val);
            auto [left, right] = split(trees[i], split_idx);
            trees[i] = left;
            tmp[i] = right;
        }

        tmp[overall_idx % N] = split(tmp[overall_idx % N], 1).second;

        for (int i = 0; i < N; i++) {
            trees[i] = merge(trees[i], tmp[(i + 1) % N]);
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    piles<2> pos;
    piles<4> neg;

    ll bsum = 0;

    vector<int> a(n), b(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];

        int d = a[i] - b[i];
        if (d > 0) {
            pos.insert(d);
        } else {
            neg.insert(d);
        }

        bsum += b[i];
    }

    auto pr = [&]() {
        int idx = cnt(neg.overall) % 2;
        cout << bsum + sum(pos.trees[idx % 2]) + sum(neg.trees[0]) + sum(neg.trees[3]) << '\n';
    };

    pr();

    for (int i = 0; i < m; i++) {
        int t, x, y;
        cin >> t >> x >> y;
        t--;

        int old_d = a[t] - b[t];
        if (old_d > 0) {
            pos.remove(old_d);
        } else {
            neg.remove(old_d);
        }
        bsum -= b[t];

        a[t] = x;
        b[t] = y;

        int new_d = a[t] - b[t];
        if (new_d > 0) {
            pos.insert(new_d);
        } else {
            neg.insert(new_d);
        }
        bsum += b[t];

        pr();
    }

    return 0;
}

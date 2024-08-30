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

struct Node {
    Node *l = 0, *r = 0;
    int val, y, c = 1;
    bool flip{};
    Node(int val) : val(val), y(rand()) {}
    void recalc();
    void push();
};

int cnt(Node* n) { return n ? n->c : 0; }
void Node::recalc() { c = cnt(l) + cnt(r) + 1; }
void Node::push() {
    if (flip) {
        swap(l, r);
        if (l) l->flip = !l->flip;
        if (r) r->flip = !r->flip;
        flip = false;
    }
}

template<class F> void each(Node* n, F f) {
    if (n) { n->push(); each(n->l, f); f(n->val); each(n->r, f); }
}

pair<Node*, Node*> split(Node* n, int k) {
    if (!n) return {};
    n->push();
    if (cnt(n->l) >= k) { // "n->val >= k" for lower_bound(k)
        auto pa = split(n->l, k);
        n->l = pa.second;
        n->recalc();
        return {pa.first, n};
    } else {
        auto pa = split(n->r, k - cnt(n->l) - 1); // and just "k"
        n->r = pa.first;
        n->recalc();
        return {n, pa.second};
    }
}

Node* merge(Node* l, Node* r) {
    if (!l) return r;
    if (!r) return l;
    l->push();
    r->push();
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

Node* ins(Node* t, Node* n, int pos) {
    auto pa = split(t, pos);
    return merge(merge(pa.first, n), pa.second);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    Node *treap = 0;
    rep(i, 0, n) {
        treap = ins(treap, new Node(s[i]), i);
    }

    while (m--) {
        int l, r;
        cin >> l >> r;
        l--;

        auto [left, tail] = split(treap, l);
        auto [mid, right] = split(tail, r - l);
        mid->flip = !mid->flip;
        treap = merge(merge(left, mid), right);
    }

    each(treap, [](char v) {
        cout << (char) v;
    });
    cout << '\n';

    return 0;
}

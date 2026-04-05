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
#include <cassert>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : mi((int)(_v % MOD)) {}
    mi operator+(const mi &m2) const { return mi(v + m2.v); }
    mi operator-(const mi &m2) const { return mi(v - m2.v); }
    mi operator*(const mi &m2) const { return mi((ll) v * m2.v); }
    mi operator/(const mi &m2) const { return mi((ll) v * m2.inv().v); }
    mi &operator+=(const mi &m2) { return *this = *this + m2; }
    mi &operator-=(const mi &m2) { return *this = *this - m2; }
    mi &operator*=(const mi &m2) { return *this = *this * m2; }
    mi &operator/=(const mi &m2) { return *this = *this / m2; }
    mi pow(ll e) const {
        mi res = 1;
        mi n = *this;
        while (e > 0) {
            if (e & 1) res *= n;
            n *= n;
            e >>= 1;
        }
        return res;
    }
    mi inv() const {
        return pow(MOD - 2);
    }
};

vector<int> suffix_array(const string &s) {
    int n = s.size();
    vector<int> sa(n), c(n);
    for (int i = 0; i < n; i++) {
        sa[i] = n - i - 1;
        c[i] = s[i];
    }

    stable_sort(sa.begin(), sa.end(), [&s](int i, int j) { return s[i] < s[j]; });

    for (int len = 1; len < n; len *= 2) {
        vector<int> old_c(c), idx(n), old_sa(sa);
        iota(idx.begin(), idx.end(), 0);

        for (int i = 0; i < n; i++) {
            bool same = i > 0 && sa[i - 1] + len < n
                && old_c[sa[i - 1]] == old_c[sa[i]]
                && old_c[sa[i - 1] + len / 2] == old_c[sa[i] + len / 2];
            c[sa[i]] = same ? c[sa[i - 1]] : i;
        }

        for (int i = 0; i < n; i++) {
            int loc = old_sa[i] - len;
            if (loc >= 0) {
                sa[idx[c[loc]]++] = loc;
            }
        }
    }

    return sa;
}

vector<int> find_lcp(const string &s, const vector<int> &sa) {
    int n = s.size();
    vector<int> rank(n);
    for (int i = 0; i < n; i++) {
        rank[sa[i]] = i;
    }

    int len = 0;
    vector<int> lcp(n - 1);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            len = 0;
        } else {
            int j = sa[rank[i] + 1];
            while (max(i, j) + len < n && s[i + len] == s[j + len]) len++;
            lcp[rank[i]] = len;
            if (len > 0) len--;
        }
    }

    return lcp;
}

struct Node {
	Node *l = 0, *r = 0;
	int val, y, c = 1;
    mi sum = 0;
	Node(int val) : val(val), y(rand()), sum(val) {}
	void recalc();
};

int cnt(Node* n) { return n ? n->c : 0; }
mi sum(Node *n) { return n ? n->sum : 0; }
void Node::recalc() { c = cnt(l) + cnt(r) + 1; sum = ::sum(l) + ::sum(r) + val; }

template<class F> void each(Node* n, F f) {
	if (n) { each(n->l, f); f(n->val); each(n->r, f); }
}

pair<Node*, Node*> split(Node* n, int k) {
	if (!n) return {};
	// if (cnt(n->l) >= k) { // "n->val >= k" for lower_bound(k)
    if (n->val >= k) {
		auto [L,R] = split(n->l, k);
		n->l = R;
		n->recalc();
		return {L, n};
	} else {
		// auto [L,R] = split(n->r,k - cnt(n->l) - 1); // and just "k"
		auto [L,R] = split(n->r, k); // and just "k"
		n->r = L;
		n->recalc();
		return {n, R};
	}
}

Node* merge(Node* l, Node* r) {
	if (!l) return r;
	if (!r) return l;
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		return l->recalc(), l;
	} else {
		r->l = merge(l, r->l);
		return r->recalc(), r;
	}
}

Node* ins(Node* t, Node* n, int pos) {
	auto [l,r] = split(t, pos);
	return merge(merge(l, n), r);
}

struct NodeData {
    Node *group;
    mi sum_diffs;

    NodeData(int v) {
        group = new Node(v);
        sum_diffs = 0;
    }

    void join(NodeData &other) {
        auto big = group;
        auto small = other.group;
        assert(cnt(big) >= cnt(small));

        each(small, [&](int v) {
            auto [L, R] = split(big, v);
            sum_diffs += mi(v) * cnt(L) - sum(L);
            sum_diffs += sum(R) - mi(v) * cnt(R);
            big = merge(merge(L, new Node(v)), R);
        });

        group = big;
    }
};


struct DSU {
    vector<int> dsu, size;
    vector<NodeData> group;
    mi ans = 0;
    DSU(int n, const vector<int> &val) : dsu(n), size(n, 1) {
        iota(all(dsu), 0);
        for (auto v : val) {
            group.push_back(v); 
        }
    }
    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }
    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (size[x] < size[y]) {
                swap(x, y);
            }
            dsu[y] = x;
            size[x] += size[y];

            ans -= group[x].sum_diffs;
            ans -= group[y].sum_diffs;
            group[x].join(group[y]);
            ans += group[x].sum_diffs;
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    string s;
    cin >> s;

    auto sa = suffix_array(s);
    auto lcp = find_lcp(s, sa);
    vector<vector<int>> at_lcp(n+1);
    rep(i, 0, n-1) {
        at_lcp[lcp[i]].push_back(i);
    }

    DSU dsu(n, sa);

    mi ans = 0;
    for (int i = n; i >= 1; i--) {
        for (auto x : at_lcp[i]) {
            dsu.join(x, x+1);
        }
        ans += dsu.ans;
    }

    cout << ans.v << '\n';

    return 0;
}

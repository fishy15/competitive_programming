#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr int mod1 = 1000000007;
constexpr int mod2 = 1000000009;

template<int MOD>
struct mi2 {
    int v;
    mi2() : mi2(0) {}
    mi2(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi2(ll _v) : v((int)(_v % MOD)) {}

#define OP(op, typ) \
    mi2 operator op (mi2 other) const { return mi2((typ) v op other.v); } \
    mi2 &operator op##= (mi2 other) { return *this = *this op other; }
    OP(+, int); OP(-, int); OP(*, ll);
#undef OP
};

struct mi {
    mi2<mod1> v1;
    mi2<mod2> v2;

    mi() : mi(0) {}
    mi(int v) : v1(v), v2(v) {}
    mi(mi2<mod1> _v1, mi2<mod2> _v2) : v1(_v1), v2(_v2) {}

#define OP(op) \
    mi operator op (mi other) const { return {v1 op other.v1, v2 op other.v2}; } \
    mi operator op##= (mi other) { return *this = *this op other; }
    OP(+); OP(-); OP(*);

    pair<int, int> get() const {
        return {v1.v, v2.v};
    }
};

struct vec_hash {
    int n, t;
    vector<int> nums;
    set<pair<int, int>> vals;

    mi hash;
    vector<mi> pows;
    mi base = 234;

    vec_hash(int _n, int _t) : n(_n + 2*_t), t(_t), nums(n), pows(n) {
        pows[0] = base;
        rep(i, 1, n) {
            pows[i] = pows[i - 1] * base;
        }
    }

    void setv(int x, int y) {
        x += t;


        hash -= pows[x] * nums[x];
        if (nums[x] != 0) {
            vals.erase({nums[x], -x});
        }

        nums[x] += y;

        hash += pows[x] * nums[x];
        vals.insert({nums[x], -x});
    }

    int get(int x) {
        x += t;
        return nums[x];
    }

    pair<int, int> max_idx() {
        auto it = prev(vals.end());
        auto res = *it;
        res.second *= -1;
        return res;
    }

    void split(int idx, int white) {
        auto size = get(idx - t);
        // left is white, right is black
        if (white) {
            int right = size / 2;
            setv(idx - t, -right);
            setv(idx+1 - t, +right);
        } else {
            int left = size / 2;
            setv(idx-1 - t, +left);
            setv(idx - t, -left);
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ifstream fin("segments.in");
    ofstream fout("segments.out");

    int n, t;
    fin >> n >> t;

    bool init_white;
    {
        string s;
        fin >> s;
        init_white = (s == "white");
    }

    vec_hash vh(n, t);
    rep(i, 0, n) {
        int x;
        fin >> x;
        vh.setv(i, x);
    }

    set<pii> seen;
    seen.insert(vh.hash.get());
    rep(i, 0, t) {
        auto [size, idx] = vh.max_idx();

        if (size == 1) {
            fout << i << '\n';
            return 0;
        }

        bool white;
        if (init_white) white = abs(idx - t) % 2 == 0;
        else white = abs(idx - t) % 2 == 1;

        vh.split(idx, white);

        if (seen.count(vh.hash.get())) {
            fout << i+1 << '\n';
            return 0;
        }
        seen.insert(vh.hash.get());
    }

    fout << t << '\n';
    return 0;
}

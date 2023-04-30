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
    template<typename T> explicit y_combinator_result(T &&f) : f(forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(forward<F>(f));
}

template<int SZ>
struct trie {
    struct node {
        int l, r;
        array<int, SZ> next;
        node() : l(INF), r(-1) { next.fill(-1); }
    };
    vector<node> t;
    trie() : t(1) {}
    int insert(int x, int idx) {
        int v = 0;
        t[v].l = min(t[v].l, idx);
        t[v].r = max(t[v].r, idx + 1);
        for (int i = 30; i >= 0; i--) {
            int c = (x >> i) & 1;
            if (t[v].next[c] == -1) {
                t[v].next[c] = t.size();
                t.emplace_back();
            }
            v = t[v].next[c];
            t[v].l = min(t[v].l, idx);
            t[v].r = max(t[v].r, idx + 1);
        }
        return v;
    }
    int get_next(int v, int bit) {
        return t[v].next[bit];
    }
    bool in(int x) {
        int v = 0;
        for (int i = 30; i >= 0; i--) {
            int c = (x >> i) & 1;
            v = get_next(v, c);
            if (v == 0) return false;
        }
        return true;
    }
    int get_opposite(int x, int l, int r) {
        int ans = 0;
        int v = 0;
        for (int i = 30; i >= 0; i--) {
            int c = ((x >> i) & 1) ^ 1;
            if (t[v].next[c] == -1) {
                ans <<= 1;
                ans ^= (c ^ 1);
                v = get_next(v, c ^ 1);
            } else if (r <= t[t[v].next[c]].l || t[t[v].next[c]].r <= l) {
                ans <<= 1;
                ans ^= (c ^ 1);
                v = get_next(v, c ^ 1);
            } else {
                ans <<= 1;
                ans ^= c;
                v = get_next(v, c);
            }
        }

        return ans ^ x;
    }
};

void solve() {
    int n;
    cin >> n;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int ans = 0;

    vector<int> psum(n + 1);
    for (int i = 0; i < n; i++) {
        psum[i + 1] = psum[i] ^ nums[i];
    }

    trie<2> t;
    for (int i = 0; i <= n; i++) {
        t.insert(psum[i], i);
    }
    
    auto solve = y_combinator([&](auto self, auto l, auto r) {
        if (r - l <= 1) {
            return;
        }

        auto max_it = max_element(l, r);
        self(l, max_it);
        self(max_it + 1, r);

        // iterate through trie
        auto loop_it_l = l;
        auto loop_it_r = max_it;

        auto trie_it_l = max_it + 1;
        auto trie_it_r = r;

        if (trie_it_r - trie_it_l < loop_it_l - loop_it_r) {
            swap(loop_it_l, trie_it_l);
            swap(loop_it_r, trie_it_r);
        }

        int loop_start_psum = psum[loop_it_l - nums.begin()];
        int idx_l = trie_it_l - nums.begin();
        int idx_r = trie_it_r - nums.begin();

        cout << "overall " << (l - nums.begin()) << ' ' << (r - nums.begin()) << endl;
        cout << idx_l << ' ' << idx_r << '\n';
    
        for (auto it = loop_it_l; it != loop_it_r; it++) {
            auto cur_idx = it - nums.begin();
            ans = max(ans, t.get_opposite(loop_start_psum ^ psum[cur_idx + 1] ^ psum[idx_l], idx_l, idx_r + 1));
            cout << cur_idx << ' ' << t.get_opposite(psum[cur_idx + 1] ^ psum[idx_l], idx_l, idx_r + 1) << '\n';
        }
    });

    solve(nums.begin(), nums.end());
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

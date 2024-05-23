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

#define sz(x) (int) (x).size()

ll euclid(ll a, ll b, ll &x, ll &y) {
    if (!b) return x = 1, y = 0, a;
    ll d = euclid(b, a % b, y, x);
    return y -= a/b * x, d;
}

struct state {
    vector<int> nums;
    int index;
    int next;
};

state recalculate(int n, state st, int x) {
    // {value, origin}
    map<int, vector<pair<int, int>>> end_up;

    int cur_index = st.index;
    int cur_base = 0;
    int gap = n / sz(st.nums);
    for (int i = 0; i < sz(st.nums); i++) {
        auto value = st.nums[cur_base];
        auto new_loc = ((ll) cur_index * x) % n;
        end_up[new_loc].push_back({value, cur_index});

        cur_index = (cur_index + gap) % n;
        cur_base = (cur_base + st.next) % sz(st.nums);
    }

    state res;
    res.index = end_up.begin()->first;
    res.next = 1;

    for (auto [y, ends] : end_up) {
        pair<int, int> best = {INF, -1};

        for (auto [v, o] : ends) {
            int dist = y - o;
            if (dist < 0) dist += n;
            best = min(best, pair{dist, v});
        }

        res.nums.push_back(best.second);
    }

    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    state st;
    st.nums.resize(n);
    iota(st.nums.begin(), st.nums.end(), 0);
    st.index = 0;
    st.next = 1;

    while (q--) {
        char typ;
        cin >> typ;

        if (typ == '+') {
            int x;
            cin >> x;

            st.index += x;
            if (st.index >= n) {
                st.index -= n;
            }
        } else if (typ == '*') {
            int x;
            cin >> x;

            ll inv, garbage;
            auto g = euclid(x, sz(st.nums), inv, garbage);
            inv = inv % sz(st.nums);
            if (inv < 0) inv += sz(st.nums);
            if (g == 1) {
                st.index = ((ll) st.index * x) % n;
                st.next = ((ll) st.next * inv) % sz(st.nums);
            } else {
                st = recalculate(n, st, x);
            }
        } else {
            int x;
            cin >> x;
            x %= n;

            int gap = n / sz(st.nums);
            if (st.index % gap == x % gap) {
                if (x < st.index) x += n;
                int gaps_needed = (x - st.index) / gap;
                int index = ((ll) gaps_needed * st.next) % sz(st.nums);
                int ans = st.nums[index];
                if (ans == 0) ans = n;
                cout << ans << '\n';
            } else {
                cout << "-1\n";
            }
        }
    }

    return 0;
}

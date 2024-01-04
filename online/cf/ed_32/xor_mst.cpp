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

constexpr int L = 30;

struct trie {
    struct node {
        array<int, 2> child;
        node() { child.fill(-1); }
    };

    int root;

    trie() {
        root = new_node();
    }

    void add(int x) {
        auto cur = root;
        for (int i = L - 1; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (buf[cur].child[b] == -1) {
                buf[cur].child[b] = new_node();
            }
            cur = buf[cur].child[b];
        }
    }

    // assumes trie is not empty
    int get_same(int x) {
        int ans = 0;
        auto cur = root;
        for (int i = L - 1; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (buf[cur].child[b] != -1) {
                cur = buf[cur].child[b];
            } else {
                ans ^= 1 << i;
                cur = buf[cur].child[b ^ 1];
            }
        }
        return ans;
    }

    vector<node> buf;
    template<typename ...Args>
    int new_node(Args ...args) {
        buf.emplace_back(args...);
        return buf.size() - 1;
    }

    void reset() {
        buf = {};
        buf.shrink_to_fit();
        root = new_node();
    }
};

trie t;

ll solve(vector<int> &&nums, int b) {
    if (nums.size() <= 1) return 0;

    vector<int> zero, one;
    for (auto x : nums) {
        if (((x >> b) & 1) == 0) {
            zero.push_back(x);
        } else {
            one.push_back(x);
        }
    }

    // clear memory
    nums = {};
    nums.shrink_to_fit();

    ll ans = 0;

    if (!one.empty() && !zero.empty()) {
        auto &smaller = zero;
        auto &bigger = one;
        if (smaller.size() > bigger.size()) swap(smaller, bigger);

        for (auto x : smaller) {
            t.add(x);
        }

        int bridge = INF;
        for (auto x : bigger) {
            bridge = min(bridge, t.get_same(x));
        }

        t.reset();
        ans += bridge;
    }

    ans += solve(std::move(zero), b - 1);
    ans += solve(std::move(one), b - 1);
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    cout << solve(std::move(nums), L - 1) << '\n';

    return 0;
}

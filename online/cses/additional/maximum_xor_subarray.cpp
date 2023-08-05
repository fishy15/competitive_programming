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
    struct node {
        array<int, 2> nxt;
        node() { nxt.fill(-1); }
    };

    vector<node> buf;
    template<typename ...Args>
    int new_node(Args ...args) {
        buf.emplace_back(args...);
        return buf.size() - 1;
    }

    int root;
    trie() { root = new_node(); }

    void add(int x) {
        int cur = root;
        for (int i = 31; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (buf[cur].nxt[b] == -1) {
                buf[cur].nxt[b] = new_node();
            }
            cur = buf[cur].nxt[b];
        }
    }

    int find_diff(int x) {
        int cur = root;
        int num = 0;
        for (int i = 31; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (buf[cur].nxt[b ^ 1] != -1) {
                num += 1 << i;
                cur = buf[cur].nxt[b ^ 1];
            } else {
                cur = buf[cur].nxt[b];
            }
        }
        return num;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    vector<int> psum(n + 1);
    inclusive_scan(nums.begin(), nums.end(), psum.begin() + 1, bit_xor{}, 0);

    trie t;
    int ans = 0;
    for (auto x : psum) {
        t.add(x);
        ans = max(ans, t.find_diff(x));
    }

    cout << ans << '\n';

    return 0;
}

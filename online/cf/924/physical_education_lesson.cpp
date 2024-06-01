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
set<int> count_divs_st(int n, F cond) {
    set<int> ans;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (cond(i)) ans.insert(i);
            if (i * i != n && cond(n/i)) {
                ans.insert(n/i);
            }
        }
    }
    return ans;
}

void solve() {
    int n, x;
    cin >> n >> x;

    auto cond = [&](int val) {
        return val % 2 == 0 && val >= 2;
    };

    auto test = [&](int val) {
        int k = (val + 2) / 2;
        int moves = (n - 1) % val;
        int loc;
        if (moves < k-1) {
            loc = moves+1;
        } else {
            loc = k - (moves-(k-1));
        }

        return loc == x;
    };

    // try before
    set<int> poss;
    for (auto x : count_divs_st(n - (x - 1) - 1, cond)) poss.insert(x);
    for (auto x : count_divs_st(n + x - 2, cond)) poss.insert(x);

    int tot = 0;
    for (auto x : poss) {
        if (test(x)) {
            tot++;
        }
    }

    cout << tot << '\n';
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

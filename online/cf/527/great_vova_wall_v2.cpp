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
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j,0,sz(jmp[k]))
                jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b); // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    map<int, vector<int>> pos;
    rep(i, 0, n) {
        pos[nums[i]].push_back(i);
    }

    RMQ rmq(nums);

    auto solve = [&](auto &&self, int l, int r, bool check) -> bool {
        if (check && (r - l + 1) % 2 != 0) {
            return false;
        }

        auto mx = rmq.query(l, r+1);
        const auto &locs = pos[mx];
        auto start_it = lower_bound(all(locs), l);
        auto end_it = upper_bound(all(locs), r);

        bool works = true;
        if (l < *start_it) {
            works = works && self(self, l, *start_it - 1, true);
        }

        if (*prev(end_it) < r) {
            works = works && self(self, *prev(end_it) + 1, r, true);
        }

        // everything in the middle
        for (auto it = start_it; next(it) != end_it; it++) {
            int a = *it;
            int b = *next(it);
            if (a+1 != b) {
                works = works && self(self, a+1, b-1, true);
            }
        }
        
        return works;
    };

    bool works = solve(solve, 0, n-1, false);
    if (works) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}

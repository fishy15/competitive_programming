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

bool can_go(int x, int val, const vector<int> &best, const vector<bool> &ok) {
    return best[x + 1] < val || (best[x + 1] == 0 && !ok[x + 1]);
}

void solve() {
    int n; cin >> n;
    vector<array<int, 2>> nums(n);

    for (int i = 0; i < n; i++) {
        // intentionally reversing input
        cin >> nums[i][1] >> nums[i][0];
        nums[i][0] = min(i, nums[i][0]);
        nums[i][1] = min(n - i - 1, nums[i][1]);
    }

    vector<int> best(n + 1);
    vector<bool> ok(n + 1);

    best[0] = INF;
    ok[0] = true;

    // store in descending order
    set<int, greater<>> front;
    
    for (auto [low, high] : nums) {
        set<int, greater<>> nxt;

        for (int x : front) {
            if (x <= low && best[x] > 0) {
                int v = min(high, best[x] - 1);
                if (can_go(x, v, best, ok)) {
                    best[x + 1] = v;
                    ok[x + 1] = true;
                    if (x + 1 < n) nxt.insert(x + 1);
                }
            } else if (x > low) {
                nxt.insert(x);
            }
        }

        if (can_go(0, high, best, ok)) {
            ok[1] = true;
            best[1] = high;
            nxt.insert(1);
        }

        front.swap(nxt);
    }

    for (int i = n; i >= 0; i--) {
        if (ok[i]) {
            cout << i << '\n';
            return;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

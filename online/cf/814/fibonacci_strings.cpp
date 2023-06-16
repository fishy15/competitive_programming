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

int sz;
int fib[100];

void precalc() {
    fib[0] = 1;
    fib[1] = 1;

    for (int i = 2; i < 100; i++) {
        fib[i] = fib[i - 2] + fib[i - 1];
        if (fib[i] >= 1e9) {
            sz = i;
            break;
        }
    }
}

vector<int> repr(int x) {
    vector<int> res;

    while (x > 0) {
        auto it = prev(upper_bound(fib, fib + sz, x));
        res.push_back(it - fib);
        x -= *it;
    }

    return res;
}

void solve() {
    int k;
    cin >> k;

    vector<int> nums(k);
    for (int i = 0; i < k; i++) {
        cin >> nums[i];
    }

    bool ans = false;

    for (int i = 0; i < k; i++) {
        nums[i]--;

        bool cur_bad = false;
        set<int> used = {0};

        for (int j = 0; j < k; j++) {
            int x = nums[j];

            auto idx = repr(x);

            for (int v : idx) {
                if (v == 1 && i == j) {
                    cur_bad = true;
                    break;
                }

                if (used.count(v)) {
                    cur_bad = true;
                    break;
                }

                used.insert(v);
            }

            if (cur_bad) {
                break;
            }
        }

        if (!cur_bad) {
            int p = -1;
            for (int x : used) {
                if (x != p + 1) {
                    cur_bad = true;
                    break;
                }

                p = x;
            }
        }

        if (!cur_bad) {
            ans = true;
            break;
        }

        nums[i]++;
    }

    if (ans) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    precalc();

    while (t--) {
        solve();
    }

    return 0;
}

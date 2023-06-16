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

ll gcd(ll x, ll y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}

void solve() {
    int n; cin >> n;
    vector<int> nums(n);
    vector<int> nxt(n);
    vector<int> ans;
    set<int> deleted;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        if (i == n - 1) {
            nxt[i] = 0;
        } else {
            nxt[i] = i + 1;
        }
    }

    vector<int> to_check(n);
    iota(to_check.begin(), to_check.end(), 0);

    while (!to_check.empty()) {
        vector<int> nxt_check;
        for (int i : to_check) {
            if (deleted.count(i)) continue;
            if (gcd(nums[i], nums[nxt[i]]) == 1) {
                ans.push_back(nxt[i] + 1);
                deleted.insert(nxt[i]);
                if (i == nxt[i]) goto done;
                nxt[i] = nxt[nxt[i]];
                nxt_check.push_back(i);
            }
        }
        to_check.swap(nxt_check);
    }

    done:
    cout << ans.size() << ' ';
    for (int i : ans) cout << i << ' ';
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

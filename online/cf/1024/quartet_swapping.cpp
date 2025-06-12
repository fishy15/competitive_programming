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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

bool odd(const vector<int> &orig, vector<int> perm) {
    int n = sz(perm);

    rep(i, 0, n) {
        perm[i] = lower_bound(all(orig), perm[i]) - begin(orig);
    }

    // now compute parity of perm
    vector<bool> vis(n);
    int parity = 0;
    rep(i, 0, n) {
        if (!vis[i]) {
            int cur = i;
            int length = 0;
            while (!vis[cur]) {
                vis[cur] = true;
                cur = perm[cur];
                length++;
            }
            parity ^= (length - 1) % 2;
        }
    }
    return parity == 1;
}

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);
    vector<int> odds, evens;
    rep(i, 0, n) {
        cin >> nums[i];
        if (i % 2 == 0) {
            evens.push_back(nums[i]);
        } else {
            odds.push_back(nums[i]);
        }
    }

    // we will swap back in the end
    if (n % 2 == 1) {
        swap(odds, evens);
    }

    auto old_evens = evens;
    auto old_odds = odds;
    sort(all(odds));
    sort(all(evens));

    auto parity1 = odd(evens, old_evens);
    auto parity2 = odd(odds, old_odds);
    if (parity1 != parity2) {
        swap(end(odds)[-2], end(odds)[-1]);
    }

    if (n % 2 == 1) {
        swap(odds, evens);
    }

    rep(i, 0, n) {
        if (i % 2 == 0) {
            cout << evens[i/2] << ' ';
        } else {
            cout << odds[i/2] << ' ';
        }
    }
    cout << '\n';
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

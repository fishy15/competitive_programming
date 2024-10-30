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

// n is even
vector<int> calc(int n) {
    vector<int> odd;
    vector<int> even;

    vector<bool> used(n + 1);

    int p = 0;
    while ((1 << p) <= n) p++;
    int goal = (1 << p) - 2;

    used[1] = true;
    used[3] = true;
    rep(best, 1, n+1) {
        if (!used[best]) {
            used[best] = true;
            int diff = goal - best;
            for (int p = 0; p < 20; p++) {
                if (((diff >> p) & 1) == 0) {
                    int evenn = diff;
                    int oddn = diff ^ (1 << p);
                    if (evenn <= n && oddn <= n && !used[evenn] && !used[oddn]) {
                        even.push_back(best);
                        even.push_back(evenn);
                        odd.push_back(oddn);
                        used[evenn] = true;
                        used[oddn] = true;
                        used[best] = true;
                        /*cout << "found: " << evenn << ' ' << oddn << ' ' << best << '\n';*/
                        goto exit;
                    }
                }
            }
            used[best] = false;
        }
    }

exit:
    odd.push_back(3);
    even.push_back(1);

    rep(i, 1, n+1) {
        if (!used[i]) {
            if (sz(odd) < n / 2) {
                odd.push_back(i);
            } else {
                even.push_back(i);
            }
        }
    }

    reverse(all(even));
    reverse(all(odd));

    // intercalate
    vector<int> res;
    rep(i, 0, n/2) {
        res.push_back(odd[i]);
        res.push_back(even[i]);
    }

    return res;
}

void solve() {
    int n;
    cin >> n;

    if (n == 5) {
        cout << "5\n";
        cout << "2 1 3 4 5\n";
        return;
    }

    auto perm = calc(n / 2 * 2);
    if (n % 2 == 1) {
        perm.push_back(n);
    }

    int k = 0;
    rep(i, 0, n) {
        auto x = perm[i];
        if (i % 2 == 1) {
            k |= x;
        } else {
            k &= x;
        }
        /*cout << x << ' ' << k << endl;*/
    }

    cout << k << '\n';
    for (auto x : perm) {
        cout << x << ' ';
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

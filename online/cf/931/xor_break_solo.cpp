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

#define ll unsigned long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    ll n, m;
    cin >> n >> m;

    ll in_m_not_n = m & (~n);
    ll in_n_not_m = n & (~m);


    vector<ll> ops;
    bool fst = true;
    for (int i = 62; i >= 0; i--) {
        if (in_n_not_m & (1LL << i)) {
            if (fst) {
                ops.push_back((1LL << i) | in_m_not_n);
                fst = false;
            } else {
                ops.push_back(1LL << i);
            }
        }
    }

    for (auto x : ops) {
        if (x > n) {
            cout << "-1\n";
            return;
        }
    }

    auto cur = n;

    cout << ops.size() << '\n';
    cout << cur << ' ';
    for (auto x : ops) {
        cur ^= x;
        cout << cur << ' ';
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

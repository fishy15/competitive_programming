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

void solve() {
    int n, m;
    cin >> n >> m;

    multiset<int> a;
    vector<int> b(m);
    rep(i, 0, n) {
        int x;
        cin >> x;
        a.insert(x);
    }
    rep(i, 0, m) {
        cin >> b[i];
    }

    auto try_to_make = [&](auto &&self, int v) -> bool {
        auto it = a.find(v);
        if (it != end(a)) {
            a.erase(it);
            return true;
        } else if (v > 1) {
            int x = v / 2;
            int y = v - x;
            return self(self, x) && self(self, y);
        } else {
            return false; 
        }
    };

    bool works = true;
    for (auto x : b) {
        if (!try_to_make(try_to_make, x)) {
            works = false;
            break;
        }
    }

    if (works && a.empty()) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
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

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

set<int> get_ops(string &s) {
    int n = s.size();

    set<int> res;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            res.insert(i + 1);
            for (int j = i; j < n; j += i + 1) {
                s[j] = '0' + '1' - s[j];
            }
        }
    }

    return res;
}

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    auto ops = get_ops(s);

    int q;
    cin >> q;

    ll ans = 0;
    while (q--) {
        int x;
        cin >> x;

        if (ops.count(x)) {
            ops.erase(x);
        } else {
            ops.insert(x);
        }

        // ans = ops.size();
        ans += ops.size();
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

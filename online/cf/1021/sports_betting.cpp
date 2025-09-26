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
    int n;
    cin >> n;

    vector<int> a(n);
    map<int, int> cnt;
    rep(i, 0, n) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    bool know_cur = false;
    for (auto [x, c] : cnt) {
        if (c >= 4 || (cnt.count(x-1) && know_cur && c >= 2)) {
            cout << "Yes\n";
            return;
        }

        if (!cnt.count(x-1)) {
            know_cur = false;
        }
        if (c >= 2 || know_cur) {
            know_cur = true;
        }
    }
    cout << "No\n";
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

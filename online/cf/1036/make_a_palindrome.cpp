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
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }

    auto ord = a;
    sort(all(ord));

    // we can delete everything above it, and we should
    auto limit = ord[k - 1];

    vector<int> b;
    for (auto x : a) {
        if (x <= limit) {
            b.push_back(x);
        }
    }

    // now try to build palindrome, assuming we can delete limit only
    int l = 0;
    int r = sz(b) - 1;
    vector<int> front_half, back_half;
    while (l <= r) {
        if (l == r) {
            front_half.push_back(b[l]);
            break;
        } else if (b[l] == b[r]) {
            front_half.push_back(b[l]);
            back_half.push_back(b[r]);
            l++;
            r--;
        } else if (b[l] == limit) {
            l++;
        } else if (b[r] == limit) {
            r--;
        } else {
            cout << "NO\n";
            return;
        }
    }

    reverse(all(back_half));
    for (auto x : back_half) {
        front_half.push_back(x);
    }

    if (sz(front_half) < k - 1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
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

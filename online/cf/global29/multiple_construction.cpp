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

// 4 3 2 1 4 1 2 3

void solve() {
    int n;
    cin >> n;

    vector<int> ans;
    ans.push_back(n);
    for (int i = n-1; i >= 1; i--) {
        ans.push_back(i);
    }
    ans.push_back(n);
    for (int i = 1; i < n; i++) {
        ans.push_back(i);
    }

    for (auto x : ans) cout << x << ' ';
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

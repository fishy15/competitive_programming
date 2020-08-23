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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n, a, b, c; cin >> n >> a >> b >> c;
    if (a + b - c > n) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    if (n != 1 && a == 1 && b == 1 && c == 1) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    if (a < c || b < c) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    vector<int> ans(n);
    int pos = 0;
    for (int i = 0; i < a - c; i++) {
        ans[i] = n - (a - c) + i;
    }
    pos = a - c;
    if (c == 1 && a != c) {
        for (int i = 0; i < n - a - b + c; i++) {
            ans[pos++] = 1;
        }
    }
    ans[pos++] = n;
    if (c > 1) {
        for (int i = 0; i < n - a - b + c; i++) {
            ans[pos++] = 1;
        }
    }
    for (int i = 0; i < c - 1; i++) {
        ans[pos++] = n;
    }
    if (c == 1 && a == c) {
        for (int i = 0; i < n - a - b + c; i++) {
            ans[pos++] = 1;
        }
    }
    for (int i = 0; i < b - c; i++) {
        ans[pos++] = n - i - 1;
    }

    for (int i : ans) {
        cout << i << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

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
    ll n; cin >> n;

    if (n < 9) {
        cout << n + 1 << '\n';
        return;
    }

    string s = to_string(n);
    int sz = s.size();
    string below(sz, s[0]);
    string above;
    if (s[0] == '9') {
        above = string(sz + 1, '1');
    } else {
        above = string(sz, s[0] + 1);
    }
    if (stoll(below) <= n) {
        cout << above << '\n';
    } else {
        cout << below << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

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
    int x, y; cin >> x >> y;
    int dx = 0; 
    int dy = 0;
    string s; cin >> s;
    for (char c : s) {
        if (c == 'U') {
            if (y > 0) dy++;
        } else if (c == 'D') {
            if (y < 0) dy++;
        } else if (c == 'R') {
            if (x > 0) dx++;
        } else {
            if (x < 0) dx++;
        }
    }

    if (dx >= abs(x) && dy >= abs(y)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

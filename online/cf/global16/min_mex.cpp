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
    string s; cin >> s;
    string s2;

    int cnt[2] = {0, 0};
    for (char c : s) {
        if (s2.empty() || s2.back() != c) {
            s2 += c;
            cnt[c - '0']++;
        }
    }

    if (cnt[0] == 0) {
        cout << 0 << '\n';
    } else if (cnt[1] == 0) {
        cout << 1 << '\n';
    } else {
        cout << min(2, cnt[0]) << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

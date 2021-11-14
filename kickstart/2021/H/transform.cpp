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

void solve() {
    string s, f; cin >> s >> f;
    int dist[26];

    for (int i = 0; i < 26; i++) {
        int d = INF;
        for (char c : f) {
            int x = c - 'a';
            d = min({d, abs(x - i), 26 - abs(x - i)});
        }
        dist[i] = d;
    }

    int ans = 0;
    for (char c : s) {
        ans += dist[c - 'a'];
    }

    cout << ans << '\n';
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

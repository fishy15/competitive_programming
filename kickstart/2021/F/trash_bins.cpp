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
    int n; cin >> n;
    string s; cin >> s;
    vector<int> trash;

    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            trash.push_back(i);
        }
    }

    int ptr = 0;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (ptr + 1 < (int) trash.size() && trash[ptr] == i) ptr++;
        ll dist = INFLL;
        if (ptr > 0) dist = min<ll>(dist, abs(i - trash[ptr - 1]));
        dist = min<ll>(dist, abs(trash[ptr] - i));
        ans += dist;
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

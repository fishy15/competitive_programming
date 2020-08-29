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
    int n;
    map<int, int> cnt;
    map<int, int> cnt2;
    int ans = -1;
    int sz = 0;

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x]++;
    }

    for (auto p : cnt) {
        cnt2[p.second]++;
    }

    for (auto p : cnt2) {
        if (p.second > sz) {
            sz = p.second;
            ans = p.first;
        } else if (p.second == sz) {
            ans = min(ans, p.first);
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

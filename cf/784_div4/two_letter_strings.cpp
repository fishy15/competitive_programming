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
    int n; cin >> n;

    map<string, ll> cnt;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        cnt[s]++;
    }

    ll ans = 0;
    for (char a = 'a'; a <= 'z'; a++) {
        for (char b = a + 1; b <= 'z'; b++) {
            for (char c = 'a'; c <= 'z'; c++) {
                string cmp1, cmp2;
                cmp1 += a;
                cmp1 += c;
                cmp2 += b;
                cmp2 += c;

                ans += cnt[cmp1] * cnt[cmp2];

                cmp1 = "";
                cmp2 = "";
                cmp1 += c;
                cmp1 += a;
                cmp2 += c;
                cmp2 += b;

                ans += cnt[cmp1] * cnt[cmp2];
            }
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

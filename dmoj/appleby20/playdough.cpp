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
#define MAXN 100010

using namespace std;

int n, q;
ll cnt[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x]++;
    }

    while (q--) {
        int t, x; cin >> t >> x;
        if (t == 1) {
            ll v = cnt[x];
            cnt[x] = 0;
            cnt[x / 2] += v;
            cnt[x - (x / 2)] += v;
        } else {
            cout << cnt[x] << '\n';
        }
    }

    return 0;
}

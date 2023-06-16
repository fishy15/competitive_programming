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
#define MAXN 1000010

using namespace std;

int n, k;
int vol[MAXN];
ll maxsz;
ll sum;

bool check(ll v) {
    int l = 0;
    int cnt = 0;
    while (l < n) {
        ll cur = 0;
        ll r = l;
        while (r < n && cur + vol[r] <= v) {
            cur += vol[r];
            r++;
        }
        l = r;
        cnt++;
    }

    return cnt <= k;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> vol[i];
        sum += vol[i];
        maxsz = max<ll>(maxsz, vol[i]);
    }

    ll l = maxsz;
    ll r = sum;
    ll ans = -1;

    while (l <= r) {
        ll m = l + (r - l) / 2;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    cout << ans << '\n';

    return 0;
}

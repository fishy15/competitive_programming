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

ll n;
ll sum;
ll ans[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        sum += x;
    }

    ll init = n * (n + 1) / 2;
    ll rem = sum - init;

    for (int i = 0; i < n; i++) {
        ans[i] = i + 1 + rem / n;
    }

    rem %= n;
    for (int i = 0; i < rem; i++) {
        ans[i]++;
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
    return 0;
}

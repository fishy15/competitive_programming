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
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

int n;
int nxt[MAXN];
int vis[MAXN];
int cnt;

void dfs(int x) {
    vis[x] = 1;
    if (vis[nxt[x]] == 1) {
        cnt++;
    } else if (vis[nxt[x]] == 0) {
        dfs(nxt[x]);
    }
    vis[x] = 2;
}

ll modpow(ll x, ll e) {
    ll res = 1;
    while (e) {
        if (e & 1) res = res * x % MOD;
        x = x * x % MOD;
        e >>= 1;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nxt[i];;
        nxt[i]--;
    }

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }

    ll ans = modpow(2, cnt);
    ans--;
    if (ans < 0) ans += MOD;

    cout << ans << '\n';


    return 0;
}

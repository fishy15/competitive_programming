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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100000

using namespace std;

int n;
ll a[MAXN + 1];
ll par[MAXN + 1];
vector<ll> child[MAXN + 1];
map<ll, ll> color[2];

bool dfs(int v) {
    bool res = false;
    for (int e : child[v]) {
        res = !dfs(e);
    }
    if (color[res].count(a[v])) color[res][a[v]]++;
    else color[res][a[v]] = 1;
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 2; i <= n; i++) {
        cin >> par[i];
        child[par[i]].push_back(i);
    }

    dfs(1);
    ll val = 0;
    for (pair<ll, ll> p : color[0]) {
        if (p.second % 2) val ^= p.first;
    }

    if (val == 0) {
        ll ans = 0;
        ll sz1 = 0;
        ll sz2 = 0;
        for (auto p : color[0]) sz1 += p.second;
        for (auto p : color[1]) sz2 += p.second;
        ans += sz1 * (sz1 - 1) / 2;
        ans += sz2 * (sz2 - 1) / 2;
        for (pair<ll, ll> p : color[0]) {
            ans += p.second * color[1][p.first];
        }
        cout << ans << '\n';
    } else {
        ll ans = 0;
        for (pair<ll, ll> p : color[0]) {
            ll rem = val ^ p.first; 
            ans += p.second * color[1][rem];
        }
        cout << ans << '\n';
    }

    return 0;
}

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

bool btw(ll n, ll l, ll r) {
    return (l <= n && n <= r) || (r <= n && n <= l);
}

void solve() {
    int n; cin >> n;
    vector<pair<ll, ll>> com;

    for (int i = 0; i < n; i++) {
        ll t, x; cin >> t >> x;
        com.push_back({t, x});
    }

    com.push_back({INFLL, INFLL});

    ll cur_pos = 0;
    ll time_end = com[0].first;
    ll dst = 0;
    ll ans = 0;
    ll dir = 0;

    for (int i = 0; i < n; i++) {
        if (com[i].first >= time_end) {
            if (com[i].second < cur_pos) {
                dir = -1; 
            } else if (com[i].second > cur_pos) {
                dir = 1;
            } else {
                dir = 0;
            }
            time_end = abs(com[i].second - cur_pos) + com[i].first;
            dst = com[i].second;
        }

        if (btw(com[i].second, cur_pos, cur_pos + dir * (min(time_end, com[i + 1].first) - com[i].first))) {
            ans++;
        }

        if (com[i + 1].first - com[i].first >= abs(cur_pos - dst)) {
            cur_pos = dst;
        } else {
            cur_pos += dir * (com[i + 1].first - com[i].first);
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

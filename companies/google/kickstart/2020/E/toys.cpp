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

struct cmp {
    bool operator()(const pair<ll, ll> &p1, const pair<ll, ll> &p2) const {
        return p1.first + p1.second < p2.first + p2.second;
    }
};

void solve() {
    int n; cin >> n;
    vector<pair<ll, ll>> toys;
    ll tot = 0;

    for (int i = 0; i < n; i++) {
        ll x, y; cin >> x >> y;
        toys.push_back({x, y});
        tot += x;
    }

    ll cursum = 0;
    pair<ll, ll> ans = {tot, 0};
    ll remtot = 0;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, cmp> init;
    for (int i = 0; i < n; i++) {
        /* cout << tot << ' ' << cursum << ' ' << remtot << '\n'; */
        init.push(toys[i]);
        cursum += toys[i].first;
        if (toys[i].first + toys[i].second <= tot) {
            ans = max(ans, {tot + cursum, remtot});
        }
        while (!init.empty()) {
            auto pp = init.top();
            if (pp.first + pp.second > tot) {
                remtot++;
                tot -= pp.first;
                cursum -= pp.first;
                init.pop();
            } else {
                break;
            }
        }
        ans = max(ans, {tot + cursum, remtot});
    }

    if (!init.empty()) {
        cout << remtot << ' ' << "INDEFINITELY\n";
    } else {
        cout << ans.second << ' ' << ans.first << '\n';
    }
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

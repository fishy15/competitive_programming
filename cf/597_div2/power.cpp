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
#define MAXN 2000

using namespace std;

ll n;
pair<ll, ll> c[MAXN];
ll cc[MAXN];
ll k[MAXN];
vector<pair<ll, ll>> loc;
priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<array<ll, 3>>> pq;

ll dsu[MAXN];
ll sz[MAXN];
bool vis[MAXN];
ll ans = 0;

ll get(ll x) {
    if (x == dsu[x]) return x;
    return dsu[x] = get(dsu[x]);
}

void join(ll a, ll b) {
    if ((a = get(a)) != (b = get(b))) {
        if (sz[b] > sz[a]) swap(a, b);
        sz[a] += sz[b];
        dsu[b] = dsu[a];
        c[a] = min(c[a], c[b]);
        cc[a] += cc[b];
    }
}

ll dist(pair<ll, ll> a, pair<ll, ll> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (ll i = 0; i < n; i++) {
        ll a, b; cin >> a >> b;
        loc.push_back({a, b});
    }

    for (ll i = 0; i < n; i++) {
        cin >> c[i].first;
        c[i].second = i;
    }

    for (ll i = 0; i < n; i++) {
        cin >> k[i];
    }

    for (ll i = 0; i < n; i++) {
        dsu[i] = i;
        sz[i] = 1;
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = i + 1; j < n; j++) {
            ll cost = dist(loc[i], loc[j]) * (k[i] + k[j]);
            pq.push({cost, i, j});
        }
    }

    vector<pair<ll, ll>> eeee;
    while (!pq.empty()) {
        auto t = pq.top();
        pq.pop();
        ll pos1 = get(t[1]);
        ll pos2 = get(t[2]);
        if (pos1 == pos2) continue;
        ll c1 = c[pos1].first + cc[pos1];
        ll c2 = c[pos2].first + cc[pos2];
        ll mm = min(c[pos1].first, c[pos2].first);
        ll nn = mm + cc[pos1] + cc[pos2] + t[0];
        if (nn < c1 + c2) {
            join(pos1, pos2);
            cc[get(t[1])] += t[0];
            eeee.push_back({t[1], t[2]});
        }
    }

    vector<ll> aa;
    for (ll i = 0; i < n; i++) {
        ll p = get(i);
        if (!vis[p]) {
            vis[p] = true;
            aa.push_back(c[p].second);
            ans += c[p].first + cc[p];
        }
    }

    cout << ans << '\n';
    cout << aa.size() << '\n';
    for (ll i : aa) {
        cout << i + 1 << ' ';
    } cout << '\n';
    cout << eeee.size() << '\n';
    for (auto x : eeee) {
        cout << x.first + 1 << ' ' << x.second + 1 << '\n';
    } 

    return 0;
}

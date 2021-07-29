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

int n;
ll s;
vector<vector<array<ll, 3>>> adj;
vector<pair<ll, ll>> one;
vector<pair<ll, ll>> two;
vector<ll> oneb;
vector<ll> twob;

int dfs(int v, int p) {
    int cnt = 0;
    int q = 0;
    for (auto e : adj[v]) {
        if (e[0] != p) {
            q++;
            int cc = dfs(e[0], v);
            if (e[2] == 1) {
                one.push_back({cc, e[1]});
            } else {
                two.push_back({cc, e[1]});
            }
            cnt += cc;
        }
    }
    if (q == 0) return 1;
    return cnt;
}

struct cmp {
    bool operator()(const pair<ll, ll> &p1, const pair<ll, ll> &p2) const {
        return p1.first * ((p1.second + 1 / 2)) < p2.first * ((p2.second + 1) / 2);
    }
};

void calc(vector<pair<ll, ll>> &one, vector<ll> &oneb) {
    ll sum = 0;
    for (auto p : one) {
        sum += p.first * p.second;
    }
    oneb.push_back(sum);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, cmp> pq;
    for (auto p : one) {
        pq.push(p);
    }
    while (sum > 0) {
        auto t = pq.top();
        /* cout << t.first << ' ' << t.second << '\n'; */
        pq.pop();
        sum -= t.first * t.second;
        t.second /= 2;
        sum += t.first * t.second;
        pq.push(t);
        oneb.push_back(sum);
    }
}

void solve() {
    cin >> n >> s; 
    adj = vector<vector<array<ll, 3>>>(n);
    one = {};
    two = {};
    oneb = {};
    twob = {};

    for (int i = 0; i < n - 1; i++) {
        ll a, b, c, d; cin >> a >> b >> c >> d;
        a--; b--;
        adj[a].push_back({b, c, d});
        adj[b].push_back({a, c, d});
    }

    dfs(0, 0);
    calc(one, oneb);
    calc(two, twob);

    for (auto i : oneb) {
        cout << i  << ' ';
    }
    cout << '\n';

    for (auto i : twob) {
        cout << i << ' ';
    }
    cout << '\n';

    ll tot = oneb[0] + twob[0];
    ll ans = INFLL;
    for (ll i = 0; i < (int)(oneb.size()); i++) {
        int l = 0;
        int r = (int)(twob.size()) - 1;
        int a = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            /* cout << oneb[i] << ' ' << twob[m] << '\n'; */
            if (oneb[i] + twob[m] <= s) {
                r = m - 1;
                a = m;
            } else {
                l = m + 1;
            }
        }
        /* cout << i << ' ' << a << '\n'; */
        if (a != -1) ans = min(ans, i + 2 * a);
    }
    cout << ans << '\n';
}

int main() {
    /* cin.tie(0)->sync_with_stdio(0); */

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

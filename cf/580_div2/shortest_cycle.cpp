// :pray: :arrayman:
// :pray: :summit:
// :pray: :pusheen:
// :pray: :prodakcin:
// :pray: :spacewalker:
// :pray: :duk:
// :pray: :gustav:
// :pray: :tmw:
// :pray: :eed:
// :pray: :chicubed:
// :pray: :arceus:
// :pray: :gamegame:
// :pray: :sinx:
// :pray: :eyg:
// :pray: :evan:
// :pray: :cj:
// :pray: :steph:
// :pray: :fatant:
// :pray: :mathbot:
// :pray: :dolphin:
// :pray: :stef:
// :pray: :geothermal:
// :pray: :mikey:
// :pray: :horse:
// :pray: :snek:
// :pray: :wayne:
// :pray: :wu:
// :pray: :vmaddur:
// :pray: :dorijanko:
// :pray: :gaming:
// :pray: :kassuno:
// :pray: :hyacllh:
// :pray: :chilli:
// :pray: :dhruv:
// :pray: :philip:
// :pray: :paiman:
// :pray: :camel:
// :pray: :tree:
// :pray: :tux:
// :pray: :jony:
// :pray: :kage:
// :pray: :ghost:
// :pray: :aha:
// :pray: :coolguy:
// :pray: :imax:
// :pray: :howlet:
// :pray: :darren:
// :pray: :arie: 
// :pray: :blastman: 
// :pray: :zephyr: 
// :pray: :bigc:

#include <iostream>
#include <fstream>
#include <vector>
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
#define MAXN 1000000

using namespace std;

vector<ll> nums;
vector<ll> pow_count[60];

ll ans = INF;
ll dist[100000];
bool visited[100000];
ll cur = 1;
vector<vector<ll>> adj;

void dfs(ll i, ll p) {
    dist[i] = cur;
    visited[i] = true;
    for (ll x : adj[i]) {
        if (x == p) continue;
        if (visited[x]) {
            if (dist[i] > dist[x]) {
                ans = min(ans, abs(dist[i] - dist[x]) + 1);
            }
        } else {
            cur++;
            dfs(x, i);
            cur--;
        }
    }
    dist[i] = 0;
    visited[i] = false;
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    ll n; cin >> n;
    for (ll i = 0; i < n; i++) {
        ll num; cin >> num;
        nums.push_back(num);
        for (ll p = 0; p < 60; p++) {
            if (num & (1LL << p)) {
                pow_count[p].push_back(i);
            }
        }
    }

    for (ll i = 0; i < 60; i++) {
        if (pow_count[i].size() >= 3) {
            cout << "3\n";
            return 0;
        }
    }

    adj = vector<vector<ll>>(n);

    for (ll i = 0; i < 60; i++) {
        if (pow_count[i].size() == 2) {
            ll x = pow_count[i][0];
            ll y = pow_count[i][1];
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
    }

    for (ll i = 0; i < n; i++) {
        if (!visited[i]) {
            cur = 1;
            dfs(i, i);
        }
    }

    if (ans == INF) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}

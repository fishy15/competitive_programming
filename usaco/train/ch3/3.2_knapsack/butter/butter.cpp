/*
ID: aaryan.1
TASK: butter
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <queue>

#define inf 1000000000
#define ll long long 

using namespace std;

struct pasture {
    vector<ll> connect;
    vector<pair<ll, ll>> paths;
    ll cows;
};

ll n, p, c;
int main() {
    ifstream fin("butter.in");
    ofstream fout("butter.out");

    fin >> p >> n >> c;
    vector<pasture> field(n);
    for (ll i = 0; i < n; i++) {
        field[i].connect = vector<ll>(n, inf);
        field[i].cows = 0;
        field[i].connect[i] = 0;
    }

    for (ll i = 0; i < p; i++) {
        ll x; fin >> x;
        field[x-1].cows++;
    }

    for (ll i = 0; i < c; i++) {
        ll a, b, w; fin >> a >> b >> w;
        field[a-1].paths.push_back({b-1, w});
        field[b-1].paths.push_back({a-1, w});
    }

    for (ll i = 0; i < n; i++) {
        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
        vector<bool> visited = vector<bool>(n, false);

        ll tot = 0;
        pq.push({0, i});

        while (tot < n) {
            ll dist = pq.top().first;
            ll num = pq.top().second;
            pq.pop();

            if (visited[num]) {
                continue;
            }

            tot++;
            visited[num] = true;
            field[i].connect[num] = dist;

            for (auto p : field[num].paths) {
                if (!visited[p.first]) {
                    pq.push({dist + p.second, p.first});
                }
            }
        }
    }

    ll ans = 2000000000;
    for (ll k = 0; k < n; k++) {
        ll totalSum = 0;
        for (pasture p : field) {
            totalSum += p.connect[k] * p.cows;
        }

        ans = totalSum < ans ? totalSum : ans;
    }

    fout << ans << '\n';
    return 0;
}

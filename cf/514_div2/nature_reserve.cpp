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
// :pray: :hyacinth:
// :pray: :chilli:
// :pray: :dhruv:
// :pray: :philip:
// :pray: :paiman:
// :pray: :camel:
// :pray: :tree:
// :pray: :tux:

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
#define MOD 10000007

using namespace std;

ll n;
vector<pair<ll, ll>> pts;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n;

    bool pos = false;
    bool neg = false;
    for (ll i = 0; i < n; i++) {
        ll x, y; cin >> x >> y;
        if (y > 0) pos = true;
        else neg = true; 

        pts.push_back({x, y});
    }

    if (pos && neg) {
        cout << "-1\n";
        return 0;
    }

    ll max_height = 0;
    ll l = 0;
    ll r = 0;

    for (pair<ll, ll> p : pts) {
        if (neg) p.second *= -1;
        
        if (p.second > max_height) {
            max_height = p.second;
            l = p.first;
            r = p.first;
        } else if (p.second == max_height) {
            l = min(l, p.first);
            r = max(r, p.second);
        }
    }

    double ans = 0.0;
    ans = (double)max_height / 2;
    if (l != r) {
         double ans1 = (double)(r - l);
         ans1 = ans1 * ans1;
         ans1 /= 8;
         ans += ans1;
    }

    cout << ans << '\n';

    return 0;
}

// TODO: CHANGE TO BINARY SEARCH

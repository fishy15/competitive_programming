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

ll used[] = {0, -1, -1, -1, -1, -1, -1, -1, -1, -1};
ll used2[] = {0, -1, -1, -1, -1, -1, -1, -1, -1, -1};

/*
 * 1
 * 1 1 
 * 1 1 1
 * 2 
 * 2 1
 * 3
 */

void play(vector<ll> v) {
    ll sum = 0;
    for (ll& i : v) sum += i;
    //cout << sum << '\n';

    for (ll i = 0; i < 10; i++) {
        if (used[i] >= 0) {
            ll next = (i + v.size()) % 10;
            ll dmg = sum;
            if (next < i) {
                dmg += v[0];
            }
            
            used2[next] = max(max(used2[next], used[next]), used[i] + dmg);
        }
    }
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    ll m; cin >> m;
    while (m--) {
        ll c; cin >> c;
        vector<ll> one;
        vector<ll> two;
        vector<ll> three;

        for (ll i = 0; i < c; i++) {
            ll x, y; cin >> x >> y;
            if (x == 1) one.push_back(y);
            else if (x == 2) two.push_back(y);
            else three.push_back(y);
        }

        sort(one.rbegin(), one.rend());
        sort(two.rbegin(), two.rend());
        sort(three.rbegin(), three.rend());

        vector<vector<ll>> combos;

        // 1
        if (one.size() > 0) {
            combos.push_back({one[0]});
        }

        // 1 1
        if (one.size() > 1) {
            combos.push_back({one[0], one[1]});
            //cout << one[0] << ' ' << one[1] << '\n';
        }

        // 1 1 1 
        if (one.size() > 2) {
            combos.push_back({one[0], one[1], one[2]});
        }

        // 2
        if (two.size() > 0) {
            combos.push_back({two[0]});
        }

        // 2 1
        if (two.size() > 0 && one.size() > 0) {
            combos.push_back({two[0], one[0]});
        }

        // 3
        if (three.size() > 0) {
            combos.push_back({three[0]});
        }

        for (vector<ll>& v : combos) {
            sort(v.rbegin(), v.rend());
            play(v);
        }

        for (ll i = 0; i < 10; i++) {
            used[i] = used2[i];
        }
    }

    ll maxi = -1;
    for (ll i = 0; i < 10; i++) {
        maxi = max(maxi, used[i]);
    }

    cout << maxi << '\n';

    return 0;
}

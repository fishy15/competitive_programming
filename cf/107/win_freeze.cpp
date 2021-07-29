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

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    ll num; cin >> num;
    ll n = num;
    vector<pair<ll, int>> p;
    if (num % 2 == 0) {
        p.push_back({2, 0});
        while (num % 2 == 0) {
            p[0].second++; 
            num /= 2;
        }
    }
    for (ll i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) {
            p.push_back({i, 0});
            while (num % i == 0) {
                p[p.size() - 1].second++; 
                num /= i;
            }
        }
    }

    if (num > 2) {
        p.push_back({num, 1});
    }

    int cnt = 0;
    int ans = 0;
    for (int i = 0; i < p.size(); i++) {
        pair<ll, int> pp = p[i];
        cnt += pp.second;

        if (pp.second >= 2) {
            ans = pp.first* pp.first;
        }
    }

    if (cnt == 2) {
        cout << 2 << '\n';
    } else {
        cout << 1 << '\n';
        if (cnt > 1) {
            if (ans == 0) {
                cout << (p[0].first * p[1].first);
            } else {
                cout << ans;
            }
        } else {
            cout << 0;
        }
    }

    return 0;
}

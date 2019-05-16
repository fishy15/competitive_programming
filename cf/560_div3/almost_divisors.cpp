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
#define INF 0x3f3f3f3f

using namespace std;

vector<ll> get_factors(ll n) {
    vector<ll> ans;
	for (ll i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) {
			if (n / i == i) {
                ans.push_back(i);
            } else {
                ans.push_back(i);
                ans.push_back(n / i);
            }	
		}
	}

    sort(ans.begin(), ans.end());
    return ans;
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    
    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        ll mini = INF; ll maxi = 0;
        vector<ll> div;

        for (ll i = 0; i < n; i++) {
            ll x; cin >> x;
            mini = min(mini, x);
            maxi = max(maxi, x);
            div.push_back(x);
        }

        sort(div.begin(), div.end());
        vector<ll> v2 = get_factors(mini * maxi);

        if (div == v2) {
            cout << mini * maxi << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}

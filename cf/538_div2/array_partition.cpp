// :pray: :arrayman:
// :pray: :summitosity:
// :pray: :pusheenosity:
// :pray: :prodakcin:
// :pray: :spacewalker:
// :pray: :duk-duk-go:
// :pray: :gustav:
// :pray: :tmw:
// :pray: :eediosity:
// :pray: :chicubed:
// :pray: :arceus:
// :pray: :gamegame:
// :pray: :sinxiosity
// :pray: :eggyosity:
// :pray: :squares-are-fine:
// :pray: :see-jay:
// :pray: :stephiosity:
// :pray: :fatant:
// :pray: :mathbot:
// :pray: :dolphin:
// :pray: :stef:
// :pray: :geothermal:
// :pray: :mikey:
// :pray: :horse:
// :pray: :snek:

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

#define ll long long

using namespace std;

int main() {
    ll n, m, k; cin >> n >> m >> k;
    vector<pair<ll, ll>> nums;
    
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        nums.push_back({x, i});   
    }
    
    sort(nums.rbegin(), nums.rend());
    vector<ll> pos;
    
    ll sum = 0;
    for (int i = 0; i < m * k; i++) {
        pos.push_back(nums[i].second);
        sum += nums[i].first;
    }
    
    sort(pos.begin(), pos.end());
    
    /*
    for (int i : pos) {
        cout << i << " sdf\n";
    }
    */
    
    cout << sum << '\n';
    
    if (m * k >= n) {
        for (ll i = 1; i < n; i += m) {
            cout << i << ' ';
        }
    } else {
        for (int i = m; i < m * k; i += m) {
            cout << pos[i] << ' ';
        }
    }
    
    cout << '\n';
    return 0;
}
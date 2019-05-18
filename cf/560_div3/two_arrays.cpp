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
#define MOD 998244353 

#define MAXN 200000

using namespace std;

ll n; 
ll arr1[MAXN];
ll arr2[MAXN];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n;
    for (ll i = 0; i < n; i++) {
        cin >> arr1[i];
        arr1[i] *= (i + 1);
        arr1[i] *= (n - i);
    }

    for (ll j = 0; j < n; j++) {
        cin >> arr2[j];
    }

    sort(arr1, arr1 + n);
    sort(arr2, arr2 + n);

    ll ans = 0;

    for (ll i = 0; i < n; i++) {
        ll mid = (arr1[i] % MOD) * arr2[n - i - 1];
        ans += mid % MOD;
        ans %= MOD;
    }

    cout << ans << '\n';
    return 0;
}

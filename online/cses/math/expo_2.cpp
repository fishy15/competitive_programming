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
#define MOD 1000000007

using namespace std;

ll modPow(ll num, ll exp, ll mod) {
    if (exp == 0) {
        return 1;
    }

    if (exp == 1) {
        return num;
    }

    ll val = 0;
    if (exp % 2 == 0) {
        val = modPow(num, exp / 2, mod);
        val *= val;
    } else {
        val = modPow(num, exp - 1, mod) * num;
    }

    val %= mod;
    return val;
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        ll a, b, c; cin >> a >> b >> c;
        cout << modPow(a, modPow(b, c, MOD - 1), MOD) << '\n';
    }

    return 0;
}

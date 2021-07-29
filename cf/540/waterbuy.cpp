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
// :pray: :wayne:
// :pray: :wu:

#include <iostream>
#include <algorithm>

#define ll long long

using namespace std;

int main() {
    ll m; cin >> m;
    for (ll i = 0; i < m; i++) {
        ll n, a, b; cin >> n >> a >> b;
        if (2 * a < b) {
            cout << n * a << '\n';
        } else {
            if (n % 2 == 0) {
                cout << n / 2 * b << '\n';
            } else {
                cout << n / 2 * b + a << '\n';
            }
        }
    }
    
    return 0;
}
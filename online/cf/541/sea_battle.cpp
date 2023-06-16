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
#include <cmath>

#define ll long long

using namespace std;

int main() {
    ll h1, w1, h2, w2;
    cin >> w1 >> h1 >> w2 >> h2;
    ll ans = 2 * h1 + 2 * h2 + w1 + w2 + max(w1, w2) - min(w1, w2) + 4;
    //cout << 2 * h1 + 2 * h2 << endl;
    //cout << w1 + w2 << endl;
    //cout << max(w1, w2) - min(w1, w2) + 4 << endl;
    cout << ans << '\n'; 
}
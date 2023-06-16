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

using namespace std;

int n, pos, neg;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x > 0) pos++;
        else if (x < 0) neg++;
    }

    // cerr << "P:" << pos << endl;
    // cerr << "n:" << neg << endl;

    if (2 * pos >= n) {
        cout << "1\n";
    } else if (2 * neg >= n) {
        cout << "-1\n";
    } else {
        cout << "0\n";
    }

    return 0;
}
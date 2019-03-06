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

using namespace std;

int main() {
    int x, y, z, a, b, c;
    cin >> x >> y >> z >> a >> b >> c;
    
    if (a >= x) {
         a -= x;
        if (a + b >= y) {
            if (a + b + c - y >= z) {
                cout << "YES\n";
                return 0;
            }
        }
    }
    
    cout << "NO\n";
    return 0;
}
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

bool works(int a, int b, int c, int d) {
    if (c > 0 && (a == 0 || d == 0)) {
        return false;
    } 
    
    if (a != d) {
        return false;
    }
    
    return true;
}

int main() {
    int a, b, c, d; cin >> a >> b >> c >> d;
    cout << works(a, b, c, d) << '\n';
    return 0;
}
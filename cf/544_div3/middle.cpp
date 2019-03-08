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
#include <string>

using namespace std;

int main() {
    string s, e; cin >> s >> e;
    int first = 60 * stoi(s.substr(0, 2)) + stoi(s.substr(3, 2));
    int second = 60 * stoi(e.substr(0, 2)) + stoi(e.substr(3, 2));
    
    int mid = (first + second) / 2;
    string h = to_string(mid / 60);
    string m = to_string(mid % 60);
    
    if (h.size() == 1) {
        cout << "0" << h;
    } else {
        cout << h;
    }
    
    cout << ":";
    
    if (m.size() == 1) {
        cout << "0" << m;
    } else {
        cout << m;
    }
}
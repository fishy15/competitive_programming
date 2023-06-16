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

using namespace std;

bool is_leap(int yr) {
    if (yr % 400 == 0) return true;
    if (yr % 100 == 0) return false;
    if (yr % 4 == 0) return true;
    return false;
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    
    int yr; cin >> yr;
    int diff = 0;
    int check = yr + 1;
    
    while (true) {
        diff += is_leap(check) ? 2 : 1;
        diff %= 7;
        if (diff == 0 && is_leap(yr) == is_leap(check)) break;
        check++;
    }
    
    cout << check << '\n';
    
    return 0;
}

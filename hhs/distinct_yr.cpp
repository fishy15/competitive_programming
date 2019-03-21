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
// :pray: :vmaddur:
// :pray: :dorijanko:

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 10000007

using namespace std;

bool distinct(int y) {
    int th = y / 1000;
    int h = y / 100 % 10;
    int t = y / 10 % 10;
    int o = y % 10;
    set<int> s = {th, h, t, o};
    //cerr << th << ' ' << h << ' ' << t << ' ' << o << endl;
    return s.size() == 4;
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int y; cin >> y;
        y++;
        while (!distinct(y)) {
            y++;
        }

        cout << y << '\n';
    }

    return 0;
}
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
#define MOD 10000007
#define INF 0x3f3f3f3f

using namespace std;

int n;
vector<pair<int, int>> vals;
int diff;
int min_1 = INF;
int max_2 = -INF;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        vals.push_back({x, y});
    }

    for (int i = 0; i < n; i++) {
        if (vals[i].second == 1) {
            min_1 = min(min_1, diff);
        } else {
            max_2 = max(max_2, diff);
        }

        diff += vals[i].first;
    }

    if (min_1 <= max_2) {
        cout << "Impossible\n";
    } else if (max_2 == -INF) {
        cout << "Infinity\n";
    } else {
        //cout << min_1 << ' ' << max_2 << ' ' << diff << '\n';
        cout << 1899 - max_2 + diff << '\n';
    }

    return 0;
}

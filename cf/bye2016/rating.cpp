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

int max_two;
int min_one = INF;
bool two;
bool one;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n;
    int diff = 0;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        diff += x;

        vals.push_back({x, diff});

        if (y == 2) {
            max_two = max(max_two, diff);
            two = true;
        } else {
            min_one = min(min_one, diff);
            one = true;
        }
    }

    if (!two) {
        cout << "Infinity\n";
        return 0;
    }

    if (min_one >= max_two) {
        cout << "Impossible\n";
        return 0;
    }

    cout << 

    return 0;
}

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

int n, c;
vector<int> coins;
ll combo[1000001];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> c;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        coins.push_back(x);
    }

    combo[0] = 0;

    for (int i = 1; i <= c; i++) {
        combo[i] = INF;
        //cout << i << '\n';
        for (int& x : coins) {
            if (i - x >= 0) {
                //cout << '\t' << combo[i - x] << '\n';
                combo[i] = min(combo[i], combo[i - x] + 1);
            }
        }
    }

    if (combo[c] == INF) {
        cout << "-1\n";
    } else {
        cout << combo[c] << '\n';
    }

    return 0;
}

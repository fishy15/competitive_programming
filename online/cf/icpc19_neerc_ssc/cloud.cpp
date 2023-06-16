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

struct tariff {
    int l;
    int r;
    int c;
    int p;

    bool operator<(const tarrif &t2) const {
        if (l == t2.l) return r < t2.r;
        return l < t2.l;
    }
};

int n, k, m;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> k >> m;

    vector<tariff> tariffs;

    for (int i = 0; i < m; i++) {
        tariff t;
        cin >> t.l >> t.r >> t.c >> t.p;
        tariffs.push_back(t);
    }

    sort(tariffs.begin(), tariffs.end());

    set<tariff> cur;

    return 0;
}

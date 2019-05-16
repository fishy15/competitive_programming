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

#define MAXN 500000

using namespace std;

int n, m;
int dsu[MAXN + 1];
int size[MAXN + 1];

int find(int x) {
    if (dsu[x] == x) return x;
    return find(dsu[x]);
}

void join(int x, int y) {
    if ((x = find(x)) != (y = find(y))) {
        if (size[x] < size[y]) {
            dsu[x] = y;
            size[y] += size[x];
        } else {
            dsu[y] = x;
            size[x] += size[y];
        }
    }
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        dsu[i] = i;
        size[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int k; cin >> k;
        vector<int> group;

        for (int j = 0; j < k; j++) {
            int q; cin >> q;
            group.push_back(q);
        }

        for (int j = 0; j < k - 1; j++) {
            join(group[j], group[j + 1]);
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << size[find(i)] << ' ';
    }
    cout << '\n';

    return 0;
}

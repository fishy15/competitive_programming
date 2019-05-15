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

#define MAXN 100000

using namespace std;

int t, n;
int dsu[MAXN + 1];
int size[MAXN + 1];

int find(int a) {
    if (dsu[a] == a) return a;
    return dsu[a] = find(dsu[a]);
}

void join(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (size[a] < size[b]) {
            dsu[a] = b;
            size[b] += size[a];
        } else {
            dsu[b] = a;
            size[a] += size[b];
        }
    }
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= MAXN; i++) {
            dsu[i] = i;
            size[i] = 1;
        }

        vector<pair<int, int>> connect;
        for (int i = 0; i < n; i++) {
            int a, b; cin >> a >> b;
            connect.push_back({a, b});
            join(a, b);
        }

        bool works = 0;
        for (int i = 1; i < n; i++) {
            if (find(connect[i].first) != find(connect[0].first)) {
                works = true;
            }
        }

        if (!works) {
            cout << "-1\n";
        } else {
            for (int i = 0; i < n; i++) {
                if (find(connect[i].first) != find(connect[0].first)) {
                    cout << "1 ";
                } else {
                    cout << "2 ";
                }
            }

            cout << '\n';
        }
    }

    return 0;
}

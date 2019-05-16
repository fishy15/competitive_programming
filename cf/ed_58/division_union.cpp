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

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    
    cin >> t;
    while (t--) {
        cin >> n;

        vector<pair<int, int>> connect;
        vector<pair<int, int>> original;
        for (int i = 0; i < n; i++) {
            int x, y; cin >> x >> y;
            connect.push_back({x, y});
            original.push_back({x, y});
        }

        sort(connect.begin(), connect.end());

        int end = connect[0].first;
        int pos = 0;
        for (; pos < n; pos++) {
            if (connect[pos].first > end) break;
            end = max(end, connect[pos].second);
        }

        if (pos == n) {
            cout << "-1\n";
        } else {
            for (int i = 0; i < n; i++) {
                if (original[i].second <= end) cout << "2 ";
                else cout << "1 ";
            }

            cout << '\n';
        }
    }

    return 0;
}

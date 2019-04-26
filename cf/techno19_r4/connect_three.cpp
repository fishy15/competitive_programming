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

pair<int, int> pts[3];
vector<int> x;
vector<int> y;
vector<pair<int, int>> ans;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
 
    for (int i = 0; i < 3; i++) {
        int x1, y1; cin >> x1 >> y1;
        pts[i] = {x1, y1};
        x.push_back(x1);
        y.push_back(y1);
    }
    
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    
    int midX = x[1];
    int midY = y[1];
    
    for (int i = x[0]; i <= x[2]; i++) {
        ans.push_back({i, midY});
    }
    
    for (int i = 0; i < 3; i++) {
        if (pts[i].second < midY) {
            for (int j = midY - 1; j >= pts[i].second; j--) {
                ans.push_back({pts[i].first, j});
            }
        } else if (pts[i].second > midY) {
            for (int j = midY + 1; j <= pts[i].second; j++) {
                ans.push_back({pts[i].first, j});
            }
        }
    }
    
    cout << ans.size() << '\n';
    for (pair<int, int> p : ans) {
        cout << p.first << ' ' << p.second << '\n';
    }
    
    return 0;
}

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

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <cmath>

#define ll long long

using namespace std;

int n; 
vector<pair<int, int>> s = {{0, 0}};
set<pair<int, int>> s2 = {{0, 0}};

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        if (!s2.count({x, y})) {
            s.push_back({x, y});
            s2.insert({x, y});
        }
    }

    ll ans = 0;
    for (int i = 1; i < s.size(); i++) {
        int l = max(s[i - 1].first, s[i - 1].second);
        int r = min(s[i].first, s[i].second);
        int diff = r - l + 1;
        if (diff > 0) {
            //cout << "DD" << i << ' ' << diff << '\n';
            ans += diff;
        }
    }

    for (int i = 1; i < s.size() - 1; i++) {
        if (s[i].first == s[i].second) ans--;
    }

    cout << (ans ? ans : 1) << '\n';
    return 0;
}
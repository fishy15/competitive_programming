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
#include <utility>
#include <cmath>

using namespace std;

int n; 
vector<pair<int, int>> s = {{0, 0}};

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        if (make_pair(x, y) != s[i - 1]) {
            s.push_back({x, y});
        }
    }

    int ans = 0;

    for (int i = 0; i < s.size() - 1; i++) {
        //int diff1 = s[i + 1].first - s[i].first;
        //int diff2 = s[i + 1].second - s[i].second;
        //cout << min(s[i + 1].first, s[i + 1].second) << endl;
        int diff = min(s[i + 1].first, s[i + 1].second) - max(s[i].first, s[i].second) + 1;
        ans += diff;
    }

    int last = (int)(s.size()) - 1;
    if (last == 0) {
        if (s[0].first == s[0].second) {
            ans++;
        }
    } else {
        if (s[last].first == s[last].second && s[last - 1].first != s[last].first) {
            ans++;
        }
    }

    cout << ans << '\n';
}
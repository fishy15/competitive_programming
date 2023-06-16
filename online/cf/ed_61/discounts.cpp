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
#include <algorithm>

#define ll long long
#define MAXN 300000

using namespace std;

int n, m;
ll sum;
ll bars[MAXN + 1];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> bars[i];
        sum += bars[i];
    }
    
    sort(bars, bars + n, [](const int &a, const int &b) {
        return a > b;
    });
    
    cin >> m;
    for (int i = 0; i < m; i++) {
        ll c; cin >> c;
        cout << sum - bars[c - 1] << '\n';
    }
    
    return 0;
}
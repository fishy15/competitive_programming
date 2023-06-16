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
#include <utility>
#include <set>
#include <vector>

#define ll long long

using namespace std;

int n;
string num;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    
    cin >> n >> num;
    ll ans;
    for (int i = 0; i < n; i++) {
        if ((num[i] - '0') % 2 == 0) {
            ans += i + 1;
        }
    }
    
    cout << ans << '\n';
}

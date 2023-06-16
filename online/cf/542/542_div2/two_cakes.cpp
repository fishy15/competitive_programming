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
#include <cmath>
#include <utility>

#define ll long long

using namespace std;

int n;
ll a[100001];
ll b[100001];

int main() {
    cin >> n;

    memset(a, -1, 100001);
    memset(b, -1, 100001);

    for (int i = 0; i < 2 * n; i++) {
        int x; cin >> x;
        if (a[x] == -1) {
            a[x] = i;
        } else {
            b[x] = i;
        }
    }

    ll dist = 0;
    for (int i = 0; i < n - 1; i++) {
        ll dist1 = abs(a[i + 1] - a[i]) + abs(b[i + 1] - b[i]);
        ll dist2 = abs(a[i + 1] - b[i]) + abs(b[i + 1] - a[i]);

        dist += dist1 < dist2 ? dist1 : dist2;
    }

    cout << dist << '\n';
    return 0;
}
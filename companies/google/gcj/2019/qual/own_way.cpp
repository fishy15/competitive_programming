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
// :pray: :vmaddur:
// :pray: :dorijanko:

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 10000007

using namespace std;

int T;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> T;
    for (int i = 0; i < T; i++) {
        int len; cin >> len;
        string path; cin >> path;

        cout << "Case #" << (i + 1) << ": ";

        for (int i = 0; i < 2 * len - 2; i++) {
            if (path[i] == 'S') {
                cout << 'E';
            } else {
                cout << 'S';
            }
        }
        cout << '\n';
    }

    return 0;
}
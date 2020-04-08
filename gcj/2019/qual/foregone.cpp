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
string n;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> n;
        string a = "";
        string b = "";

        for (int i = 0; i < n.size(); i++) {
            if (n[i] == '4') {
                a += '1';
                b += '3';
            } else {
                a += n[i];
                b += '0';
            }
        }

        cout << "Case #" << (i + 1) << ": " << stoi(a) << ' ' << stoi(b) << '\n';
    }

    return 0;
}
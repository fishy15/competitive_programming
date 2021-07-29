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
// :pray: :aha:

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

ll n;
ll two;
ll three;
ll five;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int q; cin >> q;
    while (q--) {
        cin >> n;
        two = 0;
        three = 0;
        five = 0;

        while (n % 2 == 0) {
            n /= 2;
            two++;
        }

        while (n % 3 == 0) {
            n /= 3;
            three++;
            two++;
        }

        while (n % 5 == 0) {
            n /= 5;
            five++;
            two += 2;
        }

        if (n != 1) {
            cout << "-1\n";
        } else {
            cout << (two + three + five) << '\n';
        }
    }
    return 0;
}

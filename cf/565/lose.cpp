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

#define MAXN 500000

using namespace std;

int n;
int arr[MAXN];

int one;
int two;
int three;
int four;
int five;
int done;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (int i = 0; i < n; i++) {
        if (arr[i] == 4) {
            one++;
        } else if (arr[i] == 8) {
            if (one > 0) {
                one--;
                two++;
            }
        } else if (arr[i] == 15) {
            if (two > 0) {
                two--;
                three++;
            }
        } else if (arr[i] == 16) {
            if (three > 0) {
                three--;
                four++;
            }
        } else if (arr[i] == 23) {
            if (four > 0) {
                four--;
                five++;
            }
        } else if (arr[i] == 42) {
            if (five > 0) {
                five--;
                done++;
            }
        }
    }

    cout << n - (done * 6) << '\n';
    return 0;
}

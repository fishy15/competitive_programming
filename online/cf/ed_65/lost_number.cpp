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

int gcd (int a, int b) {
    return b ? gcd (b, a % b) : a;
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int arr[4];

    for (int i = 0; i < 4; i++) {
        cout << "? 1 " << i + 2 << '\n';
        cout.flush();

        cin >> arr[i];
    }

    int g = gcd(gcd(gcd(arr[0], arr[1]), arr[2]), arr[3]);
    if (g == 30 || g == 46) g /= 2;

    vector<int> key = {4, 8, 15, 16, 23, 42};
    vector<int> ans = {0, 0, 0, 0, 0, 0};

    ans[0] = g;
    for (int i = 0; i < 4; i++) {
        ans[i + 1] = arr[i] / g;
    }

    for (int i : key) {
        if (count(ans.begin(), ans.end(), i) == 0) {
            ans[5] = i;
            break;
        }
    }

    cout << "! ";
    for (int i : ans) {
        cout << i << ' ';
    }
    cout << '\n';
    return 0;
}

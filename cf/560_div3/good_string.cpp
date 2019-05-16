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

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n; string s;
    cin >> n >> s;

    int front = 0;
    int ans = 0;

    string anss = "";

    while (front < n - 1) {
        int check = front + 1;
        while (check < n && s[check] == s[front]) {
            check++;
            ans++;
        }

        anss += s[front];
        anss += s[check];
        front = check + 1;
    }

    if ((n - ans) % 2 == 1) {
        ans++;
    }

    cout << ans << '\n';
    cout << anss.substr(0, (n - ans) / 2 * 2) << '\n';

    return 0;
}

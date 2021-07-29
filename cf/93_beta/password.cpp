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
// :pray: :coolguy:
// :pray: :imax:
// :pray: :xyzyzl:
// :pray: :darren:
// :pray: :arie: 
// :pray: :blastman: 
// :pray: :zephyr: 
// :pray: :bigc:
// :pray: :aeren: 
// :pray: :proactiveman:
// :pray: :jkiplo:
// :pray: :suneet:
// :pray: :teh:
// :pray: :numb:
// :pray: :sriraamaster:
// :pray: :hwl:
// :pray: :dajeff:
// :pray: :uwunoob:
// :pray: :rythm:

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
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int z[MAXN];
int cnt[MAXN];
int n;
string s;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> s;
    n = (int)(s.size());

    int l = 0;
    int r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }

        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
            z[i]++;
        }

        if (i + z[i]  - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    for (int i = 1; i < n; i++) {
        cnt[z[i]]++;
    }

    int cur = 0;
    for (int i = n - 1; i >= 1; i--) {
        cur += cnt[i];
        //cout << cur << '\n';
        if (cur >= 2 && z[n - i] == i) {
            cout << s.substr(0, i) << '\n';
            return 0;
        }
    }

    cout << "Just a legend\n";

    return 0;
}

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
// :pray: :howlet:
// :pray: :darren:
 
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
 
int n;
string s;
int need[26];
 
int main() {
    cin.tie(0); ios::sync_with_stdio(0);
 
    cin >> n >> s;
 
    int q; cin >> q;
    while (q--) {
        string s2; cin >> s2;
        for (int i = 0; i < 26; i++) {
            need[i] = 0;
        }
 
        for (char c : s2) {
            need[c - 'a']++;
        }

        int tot = (int)(s2.size());
        for (int i = 0; i < n; i++) {
            if (need[s[i] - 'a'] > 0) {
                need[s[i] - 'a']--;
                tot--;
                if (tot == 0) {
                    cout << i + 1 << '\n';
                    break;
                }
            }
        }
    }
 
    return 0;
}

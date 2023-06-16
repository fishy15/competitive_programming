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
// :pray: :arie: 
// :pray: :blastman: 
// :pray: :zephyr: 
// :pray: :bigc:

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
int cnt[3];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> s;
    n = (int)(s.size());

    for (int i = 0; i < n; i++) {
        cnt[s[i] - 'a']++;
    }

    int l = 0;
    int r = n - 1;
    string ans = "";

    while (l <= r) {
        if (l == r) {
            ans += s[l];
            /* cout << ans << '\n'; */
            int sz = (int)(ans.size());
            for (int i = sz - 2; i >= 0; i--) {
                ans += ans[i];
            }

            if (ans.size() < n / 2) {
                cout << "IMPOSSIBLE\n";
            } else {
                cout << ans << '\n';
            }
            return 0;
        }

        if (s[l] == s[r]) {
            ans += s[l];
            l++;
            r--;
        } else if (cnt[s[l] - 'a'] > cnt[s[r] - 'a']) {
            r--;
        } else {
            l++;
        }
    }

    int sz = (int)(ans.size());
    for (int i = sz - 1; i >= 0; i--) {
        ans += ans[i];
    }

    if (ans.size() < n / 2) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}

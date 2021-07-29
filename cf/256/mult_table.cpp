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

ll n, m, k;
bool found;

ll check(ll num) {
    ll equal = 0;
    ll below = 0;
    ll above = 0;

    for (int i = 1; i <= n; i++) {
        if (num / i <= m && num % i == 0) {
            equal++;
        }

        below += min(m, num / i);
        above += min(m, (i * m - num));
        
        if (num <= i * m && num % i == 0) {
            below--;
        }
    }
    
    above = n * m - below - equal;

    //cout << "num: " << num << ' ' << below << ' ' << above << '\n';

    if (below < k && (n * m - k) >= above) {
        if (equal != 0) {
            return 0;
        }
        return 2;
    } else if (k <= below) {
        return -1;
    }

    return 1;
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> m >> k;

    ll l = 1;
    ll r = n * m;
    
    while (l <= r) {
        //cout << l << ' ' << r << '\n';
        ll mid = (l + r) / 2;
        ll res = check(mid);

        if (res == 0) {
            cout << mid << '\n';
            return 0;
        } else if (res == 2) {
            int res1 = check(mid - 1);
            if (res1 == 0) cout << mid - 1 << '\n';
            else cout << mid + 1 << '\n';
            return 0;
        } else if (res == 1) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return 0;
}

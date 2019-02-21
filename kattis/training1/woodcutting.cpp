#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long 

using namespace std;

int main() {
    ll t; cin >> t;
    for (ll i = 0; i < t; i++) {
        ll c; cin >> c;
        vector<ll> custs;
        for (ll j = 0; j < c; j++) {
            ll num; cin >> num;
            ll sum = 0;
            for (ll k = 0; k < num; k++) {
                ll y; cin >> y;
                sum += y;
            }

            custs.push_back(sum);
        }

        sort(custs.begin(), custs.end());

        ll time = 0;
        ll total = 0;
        for (ll j = 0; j < c; j++) {
            time += custs[j];
            total += time;
        }

        cout << total * 1.0 / c << '\n';
    }

    return 0;
}


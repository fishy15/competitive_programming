#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <algorithm>

#define ll long long

using namespace std;

ll calcDist(const pair<ll, ll> &p, ll t) {
    return p.second * t + p.first;
}

int main() {
    ifstream fin("cowjog.in");
    ofstream fout("cowjog.out");

    ll n, t; fin >> n >> t;
    vector<pair<ll, ll>> cows;

    for (ll i = 0; i < n; i++) {
        ll p, s; fin >> p >> s;
        cows.push_back({p, s});
    }

    sort(cows.rbegin(), cows.rend(), [&](const pair<ll, ll> &p1, const pair<ll, ll> &p2) {
        ll val1 = calcDist(p1, t);
        ll val2 = calcDist(p2, t);

        if (val1 == val2) {
            return p1.second < p2.second;
        }

        return val1 < val2;
    });

    /*
    for (auto p : cows) {
        cout << p.first << ' ' << p.second << endl;
    }
    */

    ll count = 1;
    ll cur = 0;
    for (ll i = 1; i < n; i++) {
        if (cows[i].first > cows[cur].first && cows[i].second < cows[cur].second) {
            continue;
        }

        cur = i;
        count++;
    }

    fout << count << '\n';
    return 0;
}
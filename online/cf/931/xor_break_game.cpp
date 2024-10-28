#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

// do you win if the number has b bits
// you = person who is breaking
bool win[64];

void precalc() {
    win[1] = false;
    for (int i = 2; i < 64; i++) {
        for (int j = 1; j < i; j++) {
            int k = i - j;
            win[i] |= !win[j] && !win[k];
        }
    }
}

int popcnt(ll x) {
    return __builtin_popcountll(x);
}

void solve() {
    ll n;
    cin >> n;

    bool my_turn;
    if (win[popcnt(n)]) {
        cout << "first" << endl;
        my_turn = true;
    } else {
        cout << "second" << endl;
        my_turn = false;
    }

    ll p = n;

    while (true) {
        if (my_turn) {
            // i need to split
            ll mask = 0;
            vector<pair<ll, ll>> ops;
            for (int i = 0; i < 64; i++) {
                mask ^= 1LL << i;

                auto res1 = p & mask;
                auto res2 = p & (~mask);
                int pc1 = popcnt(res1);
                int pc2 = popcnt(res2);

                if (res1 > 0 && res2 > 0 && !win[pc1] && !win[pc2]) {
                    ops.push_back({res1, res2});
                }
            }

            sort(ops.begin(), ops.end(), 
                 [](auto a, auto b) { return a.second - a.first < b.second - b.first; });

            if (ops.empty()) {
                cout << "0 0" << endl;
                return;
            }

            ll p1 = ops[0].first;
            ll p2 = ops[0].second;

            cout << p1 << ' ' << p2 << endl;
        } else {
            ll p1, p2;
            cin >> p1 >> p2;

            if (p1 == 0 && p2 == 0) {
                return;
            } else if (p1 == -1 || p2 == -1) {
                exit(0);
            }

            if (win[popcnt(p1)]) {
                p = p1;
            } else {
                p = p2;
            }
        }

        my_turn = !my_turn;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

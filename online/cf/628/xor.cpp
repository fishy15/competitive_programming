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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll u, v; cin >> u >> v;
    ll diff = v - u;

    if (diff < 0 || diff % 2 == 1) {
        cout << "-1\n";
    } else {
        vector<ll> ans;

        for (int l = 0; l < 61; l++) {
            ll x = 1LL << l;
            if (v & x) {
                if (u & x) {
                    ans.push_back(x);
                    u ^= x;
                    v -= x;
                } else {
                    ans.push_back(x / 2);
                    ans.push_back(x / 2);
                    v -= x;
                }
            }
        }

        cout << (int)(ans.size()) << '\n';
        for (int i : ans) {
            cout << i << ' ';
        } cout << '\n';
    }

    return 0;
}

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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

ll n, m, k;
map<ll, int> a, b;

vector<ll> opt_a, opt_b;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        ll x, y; cin >> x >> y;
        a[x]++;
        b[y]++;
    }

    for (auto [x, cnt] : a) {
        if (cnt % 2 == 1) {
            opt_a.push_back(x);
        }
    }

    for (auto [y, cnt] : b) {
        if (cnt % 2 == 1) {
            opt_b.push_back(y);
        }
    }

    while (opt_a.size() < opt_b.size()) opt_a.push_back(1);
    while (opt_b.size() < opt_a.size()) opt_b.push_back(1);

    int sz = opt_a.size();
    cout << sz << '\n';
    for (int i = 0; i < sz; i++) {
        cout << opt_a[i] << ' ' << opt_b[i] << '\n';
    }

    return 0;
}

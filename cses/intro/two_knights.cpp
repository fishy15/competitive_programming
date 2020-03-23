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

    int n; cin >> n;

    for (ll i = 1; i <= n; i++) {
        ll bad = 4 * (i - 2) * (i - 1);
        ll cur = i * i * (i * i - 1) / 2;
        cur -= bad;
        cout << cur << '\n';
    }

    return 0;
}

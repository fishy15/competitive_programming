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

void solve() {
    int x;
    cin >> x;

    vector<int> moves;
    moves.push_back(x);
    int lsb;
    while ((lsb = (x & -x)) != x) {
        x -= lsb;
        moves.push_back(x);
    }

    while (x > 1) {
        x /= 2;
        moves.push_back(x);
    }

    cout << moves.size() << '\n';
    for (auto res : moves) {
        cout << res << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

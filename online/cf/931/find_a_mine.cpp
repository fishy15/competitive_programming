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

int ask(int x, int y) {
    cout << "? " << x << ' ' << y << endl;
    int d;
    cin >> d;
    return d;
}

void answer(int x, int y) {
    cout << "! " << x << ' ' << y << endl;
}

void solve() {
    int n, m;
    cin >> n >> m;

    int d11 = ask(1, 1);

    pair<int, int> qry2 = {1, d11 + 1};
    if (qry2.second > m) {
        qry2 = {d11 - (m - 1) + 1, m};
    }

    pair<int, int> qry3 = {d11 + 1, 1};
    if (qry3.first > n) {
        qry3 = {n, d11 - (n - 1) + 1};
    }

    int d2 = ask(qry2.first, qry2.second);
    int d3 = ask(qry3.first, qry3.second);

    pair<int, int> qry4 = {qry2.first + d2 / 2, qry2.second - d2 / 2};
    if (ask(qry4.first, qry4.second) != 0) {
        qry4 = {qry3.first - d3 / 2, qry3.second + d3 / 2};
    }
    answer(qry4.first, qry4.second);
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

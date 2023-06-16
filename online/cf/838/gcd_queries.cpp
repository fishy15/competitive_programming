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
#include <random>
#include <chrono>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int qry(int i, int j) {
    cout << "? " << i + 1 << ' ' << j + 1 << endl;

    int x;
    cin >> x;

    if (x == -1) exit(0);
    return x;
}

void ans(int x, int y) {
    cout << "! " << x + 1 << ' ' << y + 1 << endl;

    int r;
    cin >> r;

    if (r == -1) exit(0);
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    int n;
    cin >> n;

    int a = 0;
    int b = 1;

    for (int c = 2; c < n; c++) {
        int q1 = qry(a, c);
        int q2 = qry(b, c);

        if (q1 < q2) {
            a = c;
        } else if (q1 > q2) {
            b = c;
        }
    }

    ans(a, b);
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

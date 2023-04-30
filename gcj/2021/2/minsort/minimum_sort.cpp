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

int t, n;

bool solve() {
    for (int i = 1; i < n; i++) {
        cout << "M " << i << ' ' << n << endl;
        int m; cin >> m;
        if (m == -1) return false;
        if (m == i) continue;

        cout << "S " << i << ' ' << m << endl;
        cin >> m;
        if (m == -1) return false;
    }

    cout << "D" << endl;
    int res; cin >> res;
    return res == 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> t >> n;
    while (t-- && solve());

    return 0;
}

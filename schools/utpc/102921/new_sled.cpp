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

ll x, y;
int n;
string dir;
array<int, 2> loc[MAXN];

ll get_div(ll a, ll b) {
    if (b == 0) {
        if (a == 0) return -2;
        else return -1;
    } else if (a % b == 0) {
        if (a / b < 0) return -1;
        return a / b;
    } else {
        return -1;
    }
}

bool ok(ll a, ll b) {
    return a == -2 || b == -2 || a == b;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> x >> y;
    cin >> dir;
    n = dir.size();

    int cx = 0;
    int cy = 0;
    for (int i = 0; i < n; i++) {
        if (dir[i] == 'U') {
            cy++;
        } else if (dir[i] == 'D') {
            cy--;
        } else if (dir[i] == 'L') {
            cx--;
        } else if (dir[i] == 'R') {
            cx++;
        }

        loc[i][0] = cx;
        loc[i][1] = cy;
    }

    ll dx = loc[n - 1][0];
    ll dy = loc[n - 1][1];

    for (int i = 0; i <= n; i++) {
        ll diffx = x - loc[i][0];
        ll diffy = y - loc[i][1];

        ll divx = get_div(diffx, dx);
        ll divy = get_div(diffy, dy);

        if (divx != -1 && divy != -1 && ok(divx, divy)) {
            cout << "Yes\n";
            return 0;
        }
    }

    cout << "No\n";

    return 0;
}

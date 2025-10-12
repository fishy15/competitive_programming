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
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int r, g, b;
    cin >> r >> g >> b;

    int cr, cg, cb;
    cin >> cr >> cg >> cb;

    int crg, cgb;
    cin >> crg >> cgb;

    auto r_need = max(0, r - cr);
    auto g_need = max(0, g - cg);
    auto b_need = max(0, b - cb);

    auto needed = r_need + g_need + b_need;

    // check if it is possible
    crg -= r_need;
    if (crg < 0) {
        cout << "-1\n";
        return 0;
    }

    cgb -= b_need;
    if (cgb < 0) {
        cout << "-1\n";
        return 0;
    }

    if (crg + cgb >= g_need) {
        cout << needed << '\n';
    } else {
        cout << "-1\n";
    }

    return 0;
}

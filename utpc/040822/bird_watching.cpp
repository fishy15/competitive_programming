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

ll bit[MAXN];

void add(int x, ll v) {
    while (x < MAXN) {
        bit[x] += v;
        x += x & -x;
    }
}

ll qry(int x) {
    ll ans = 0;
    while (x > 0) {
        ans += qry(x);
        x -= x & -x;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    return 0;
}
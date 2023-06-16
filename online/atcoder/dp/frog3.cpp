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

int n;
ll c;
ll h[MAXN];

struct f {
    ll x, k;
    ll isect(const f &f2) {
        return ((k - f2.k) / (x - f2.x) + x + f2.x) / 2;
    }
    ll eval(ll y) {
        return (x - y) * (x - y) + k;
    }
};

int l, r;
f st[MAXN];

void upd(const f &f2) {
    while (r - l >= 2 && st[r - 2].isect(st[r - 1]) >= st[r - 1].isect(f2)) r--;
    st[r++] = f2;
}

ll qry(ll x) {
    while (r - l >= 2 && st[l].eval(x) >= st[l + 1].eval(x)) l++;
    return st[l].eval(x);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> c;

    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    upd({h[0], c});
    for (int i = 1; i < n; i++) {
        ll x = qry(h[i]);
        upd({h[i], x + c});
    }

    cout << qry(h[n - 1]) << '\n';

    return 0;
}

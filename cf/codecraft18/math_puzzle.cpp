// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
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
#define MAXN 500001

using namespace std;

int n;
ll a[MAXN];
ll t[4 * MAXN + 1];

ll gcd(ll a, ll b) {
    if (a > b) {
        return gcd(b, a);
    } else if (a == 0) {
        return b;
    }

    return gcd(b % a, a);
}

ll build(int v, int l, int r) {
    if (l == r) {
        return t[v] = a[l];
    }

    ll min_l = build(2 * v, l, l + (r - l) / 2);
    ll min_r = build(2 * v + 1, r - (r - 1) / 2, r);

    return t[v] = gcd(min_l, min_r);
}

void update(int v, int n, int d, int l, int r) {
    if (l == r) {
        a[n] = d;
        t[v] = d;
    } else {
        if (l <= n && n <= l + (r - l) / 2) {
            update(2 * v, n, d, l, l + (r - l) / 2);
        } else {
            update(2 * v + 1, n, d, r - (r - 1) / 2, r);
        }

        t[v] = gcd(t[2 * v], t[2 * v + 1]);
    }
}

ll query(int v, int x, int y, int l, int r) {
    if (l <= x && y <= r) {
        return t[v];
    }

    if (r < x || l > y) {
        return 1;
    }

    ll left = query(2 * v, x, y, l, l + (r - l) / 2);
    ll right = query(2 * v + 1, x, y, r - (r - l) / 2, r);
    return gcd(left, right);
}

int check(int l, int r, int x) {
    int count = 0;
    ll g = query(0, 1, n, l, r);
    if (g % x == 0) {
        return 0;
    } else {
        int mid = l + (r - l) / 2;
        count += check(l, mid, x);
        if (count >= 2) {
            return count;
        }
        count += check(mid + 1, r, x);
    }
    
    return count;
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    build(0, 1, n);

    int q; cin >> q;
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int l, r, x; cin >> l >> r >> x;
            int val = check(l, r, x);
            if (val < 2) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        } else {

        }
    }

    return 0;
}

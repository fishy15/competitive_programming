#include <iostream>
#include <fstream>
#include <vector>
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
#define MAXN 100000

using namespace std;

int n;
int a[MAXN];
int t[4 * MAXN + 1];

int build(int v, int l, int r) {
    if (l == r) {
        return t[v] = a[l];
    }

    int min_l = build(2 * v, l, l + (r - l) / 2);
    int min_r = build(2 * v + 1, r - (r - 1) / 2, r);

    return t[v] = min(min_l, min_r);
}

void update(int v, int n, int d, int l, int r) {
    if (l == r) {
        a[n] += d;
        t[v] += d;
    } else {
        if (l <= n && n <= l + (r - l) / 2) {
            update(2 * v, n, d, l, l + (r - l) / 2);
        } else {
            update(2 * v + 1, n, d, r - (r - 1) / 2, r);
        }

        t[v] = min(t[2 * v], t[2 * v + 1]);
    }
}

int query(int v, int x, int y, int l, int r) {
    if (l <= x && y <= r) {
        return t[v];
    }

    if (r < x || l > y) {
        return INF;
    }

    int left = query(2 * v, x, y, l, l + (r - l) / 2);
    int right = query(2 * v + 1, x, y, r - (r - l) / 2, r);
    return min(left, right);
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    return 0;
}

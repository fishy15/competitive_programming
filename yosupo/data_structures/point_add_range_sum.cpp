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

template<typename T>
struct BIT {
    int n;
    vector<T> bit;

    BIT(int n) : n(n), bit(n + 1) {}

    void upd(int x, int v) {
        x++;
        while (x <= n) {
            bit[x] += v;
            x += x & -x;
        }
    }

    T qry(int r) {
        T res{};
        while (r > 0) {
            res += bit[r];
            r -= r & -r;
        }
        return res;
    }

    T qry(int l, int r) {
        return qry(r) - qry(l);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    BIT<ll> bit(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        bit.upd(i, x);
    }

    while (q--) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 0) {
            bit.upd(x, y);
        } else {
            cout << bit.qry(x, y) << '\n';
        }
    }

    return 0;
}

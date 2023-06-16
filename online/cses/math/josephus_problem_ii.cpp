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

    int lower_bound(T val) {
        T sum{};
        int pos = 0;

        for (int i = 20; i >= 0; i--) {
            int nxt = pos + (1 << i);
            if (nxt <= n && sum + bit[nxt] < val) {
                sum += bit[nxt];
                pos = nxt;
            }
        }

        return pos;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    BIT<int> ppl(n);
    for (int i = 0; i < n; i++) {
        ppl.upd(i, 1);
    }

    int cur = 0;
    int sz = n;

    while (sz > 0) {
        cur = (cur + k) % sz;
        int idx = ppl.lower_bound(cur + 1);
        cout << idx + 1 << ' ';

        ppl.upd(idx, -1);
        sz--;
    }

    cout << '\n';

    return 0;
}

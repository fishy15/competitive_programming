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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

int n, q;
int nums[MAXN];
ll bit[MAXN];

void add(int x, ll v) {
    while (x < MAXN) {
        bit[x] += v;
        x += x & -x;
    }
}

ll query(int x) {
    ll res = 0;
    while (x) {
        res += bit[x];
        x -= x & -x;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        add(i, nums[i]);
    }

    for (int i = 0; i < q; i++) {
        int t, a, b; cin >> t >> a >> b;
        if (t == 1) {
            add(a, -nums[a]);
            nums[a] = b;
            add(a, b);
        } else {
            cout << query(b) - query(a - 1) << '\n';
        }
    }

    return 0;
}

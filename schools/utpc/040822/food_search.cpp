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
#define MAXN 100010

using namespace std;

int n, q, r;
int nums[MAXN];
int ans[MAXN];

int bit[MAXN];

void upd(int x, int v) {
    while (x < MAXN) {
        bit[x] += v;
        x += x & -x;
    }
}

int qry(int x) {
    int res = 0;
    while (x > 0) {
        res += bit[x];
        x -= x & -x;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q >> r;

    vector<array<int, 4>> qq;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        qq.push_back({nums[i], 1, i, -1});
    }
    
    for (int i = 0; i < q; i++) {
        int l, k; cin >> l >> k;
        l--;
        qq.push_back({k, 0, l, i});
    }

    sort(qq.begin(), qq.end(), greater<>());

    for (auto [v, t, a, b] : qq) {
        if (t == 1) {
            upd(a + 1, 1);
        } else {
            int end = min(a + r, n);
            ans[b] = qry(end) - qry(a);
        }
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}

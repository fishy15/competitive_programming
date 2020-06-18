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
int bit[MAXN];
int ans[MAXN];
vector<array<int, 3>> qq;
map<int, vector<int>> ord;
map<int, int> idx;

void upd(int x, int v) {
    while (x < MAXN) {
        bit[x] += v;
        x += x & -x;
    }
}

int qry(int x) {
    int res = 0;
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
        ord[nums[i]].push_back(i);
    }

    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        qq.push_back({a, b, i});
    }

    sort(qq.begin(), qq.end(), [](const array<int, 3> &a, const array<int, 3> &b) {
        if (a[1] == b[1]) return a < b;
        return a[1] < b[1];
    });

    int pos = 0;
    for (int i = 1; i <= n; i++) {
        upd(i, 1);
        if (idx[nums[i]] > 0) {
            upd(ord[nums[i]][idx[nums[i]] - 1], -1);
        }
        while (pos < q && qq[pos][1] == i) {
            ans[qq[pos][2]] = qry(qq[pos][1]) - qry(qq[pos][0] - 1);
            pos++;
        }
        idx[nums[i]]++;
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
